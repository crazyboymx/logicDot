/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: LogicDot.cpp
 * $Id: LogicDot.cpp v 1.0 2015-01-20 20:10:39 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-03-09 23:00:42 $
 * @brief
 *
 ******************************************************************/

#include "LogicDot.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <set>
#include <cocos2d.h>

int myrandom(int i) {
    return rand() % i;
}

int random(int min, int max) {
    if (min >= max) {
        return min;
    }
    return min + rand() % (max - min);
};

char getStatusChar(Status status) {
    switch (status) {
    case UNKNOWN: return 'u'; break;
    case EMPTY: return 'e';
    case DOT: return 'd'; break;
    case HINT_EMPTY: return '.'; break;
    case HINT_DOT: return 'h'; break;
    default: return 'z'; break;
    }
}

bool Puzzle::isWin() const {
    for (int i = 0; i < shapes.size(); ++ i) {
        if (shapes[i] != solution.shapes[i]) {
            return false;
        }
    }
    for (int i = 0; i < row.size(); ++ i) {
        if (this->row[i] != 0) {
            return false;
        }
    }
    for (int i = 0; i < column.size(); ++ i) {
        if (this->column[i] != 0) {
            return false;
        }
    }
    return true;
}

Puzzle* Puzzle::generate(int width, int height) {
    Puzzle* p = new Puzzle(width, height);
    int max = width * height - 1;
    std::vector<int> candidate;
    for (int i = 0; i < max; i++) {
        candidate.push_back(i);
    }
    while(!p->valid()) {
        int squar = width * height;
        p->solution.dots = random(squar / 4 - width / 4, squar / 4 + width);
        std::random_shuffle(candidate.begin(), candidate.end(), myrandom);
        int i = 0;
        int dots = p->solution.dots;
        while (dots > 0 && i < max) {
            int idx = candidate[i];
            int row = idx / width;
            int col = idx % width;
            if (p->putDotToHint(row, col)) {
                dots --;
                p->solution.row[row] ++;
                p->solution.column[col] ++;
            }
            i++;
        }
        if (dots > 0) {
            std::cout << "remain dots: " << dots << std::endl;
        }
        p->fillHint();
        p->solution.shapes = p->calcShapes(true);
        if (p->valid() == false) {
            std::cout << "not valid" << std::endl;
            p->clear();
            CCLOG("try again!!!!!!!!!!!!!!!");
        }
    }

    return p;
}

bool Puzzle::valid() const {
    int dots = 0;
    for (int i = 0; i < row.size(); i++) {
        dots += row[i];
    }
    if (dots != solution.dots || solution.dots == 0) {
        return false;
    }
    if (solution.shapes[size.width] > 0) {
        return false;
    }
    return true;
}

void Puzzle::clear() {
    solution.dots = 0;
    for (int i = 0; i < solution.shapes.size(); i++) {
        solution.shapes[i] = 0;
        solution.row[i] = 0;
        solution.column[i] = 0;
    }
    for (int i = 0; i < size.height; i ++) {
        for (int j = 0; j < size.width; j ++) {
            cells[i][j].reset();
        }
    }
    for (int i = 0; i < row.size(); i++) {
        row[i] = 0;
    }
    for (int i = 0; i < column.size(); i++) {
        column[i] = 0;
    }
}

void Puzzle::setStatus(int row, int col, Status status) {
    Status oldStatus = cells[row][col].status;
    if (oldStatus == status) {
        return;
    }
    if (status == DOT && canPutDot(row, col) == false) {
        return;
    }
    cells[row][col].status = status;
    if (isDot(oldStatus) && !isDot(status)) {
        this->row[row]++;
        this->column[col]++;
    }
    else if (!isDot(oldStatus) && isDot(status)) {
        this->row[row]--;
        this->column[col]--;
    }
    updateFlag(row, col);
    shapes = calcShapes();
}

void Puzzle::updateFlag(int row, int col) {
    Cell& c = cells[row][col];
    c.flag = 0;
    // left
    if (col - 1 >= 0) {
        if (isHint(c.status)) {
            c.flag |= (isDot(c.status) && isDot(cells[row][col - 1].hint) ? HINT_LEFT : 0x0);
        }
        else {
            c.flag |= (isDot(c.status) && isDot(cells[row][col - 1].status) ? LEFT : 0x0);
        }
        if ((c.flag & LEFT) && !isHint(cells[row][col - 1].status)) {
            cells[row][col - 1].flag |= RIGHT;
        }
        if (!(c.flag & LEFT || c.flag & HINT_LEFT) && !isHint(cells[row][col - 1].status) && isDot(cells[row][col - 1].status)) {
            cells[row][col - 1].flag &= ~RIGHT;
        }
    }
    // up
    if (row + 1 < this->row.size()) {
        if (isHint(c.status)) {
            c.flag |= (isDot(c.status) && isDot(cells[row + 1][col].hint) ? HINT_UP : 0x0);
        }
        else {
            c.flag |= (isDot(c.status) && isDot(cells[row + 1][col].status) ? UP : 0x0);
        }
        if ((c.flag & UP) && !isHint(cells[row + 1][col].status)) {
            cells[row + 1][col].flag |= DOWN;
        }
        if (!(c.flag & UP || c.flag & HINT_UP) && !isHint(cells[row + 1][col].status) && isDot(cells[row + 1][col].status)) {
            cells[row + 1][col].flag &= ~DOWN;
        }
    }
    // right
    if (col + 1 < this->column.size()) {
        if (isHint(c.status)) {
            c.flag |= (isDot(c.status) && isDot(cells[row][col + 1].hint) ? HINT_RIGHT : 0x0);
        }
        else {
            c.flag |= (isDot(c.status) && isDot(cells[row][col + 1].status) ? RIGHT : 0x0);
        }
        if ((c.flag & RIGHT) && !isHint(cells[row][col + 1].status)) {
            cells[row][col + 1].flag |= LEFT;
        }
        if (!(c.flag & RIGHT || c.flag & HINT_RIGHT) && !isHint(cells[row][col + 1].status) && isDot(cells[row][col + 1].status)) {
            cells[row][col + 1].flag &= ~LEFT;
        }
    }
    // down
    if (row - 1 >= 0) {
        if (isHint(c.status)) {
            c.flag |= (isDot(c.status) && isDot(cells[row - 1][col].hint) ? HINT_DOWN : 0x0);
        }
        else {
            c.flag |= (isDot(c.status) && isDot(cells[row - 1][col].status) ? DOWN : 0x0);
        }
        if ((c.flag & DOWN) && !isHint(cells[row - 1][col].status)) {
            cells[row - 1][col].flag |= UP;
        }
        if (!(c.flag & DOWN || c.flag & HINT_DOWN) && !isHint(cells[row - 1][col].status) && isDot(cells[row - 1][col].status)) {
            cells[row - 1][col].flag &= ~UP;
        }
    }
}

void Puzzle::useHint(int count) {
    std::vector<int> unknownList;
    std::vector<int> knownList;
    int rowSize = row.size();
    int colSize = column.size();
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (cells[i][j].status == UNKNOWN) {
                unknownList.push_back(i * colSize + j);
            }
            else if (isHint(cells[i][j].status) == false) {
                knownList.push_back(i * colSize + j);
            }
        }
    }
    std::random_shuffle(unknownList.begin(), unknownList.end(), myrandom);
    for (int i = 0; i < unknownList.size(); i++) {
        setStatus(unknownList[i] / colSize, unknownList[i] % colSize, cells[unknownList[i] / colSize][unknownList[i] % colSize].hint);
        count --;
        if (count <= 0) {
            return;
        }
    }
    std::random_shuffle(knownList.begin(), knownList.end(), myrandom);
    for (int i = 0; i < knownList.size(); i++) {
        setStatus(knownList[i] / colSize, knownList[i] % colSize, cells[knownList[i] / colSize][knownList[i] % colSize].hint);
        count --;
        if (count <= 0) {
            return;
        }
    }
}

bool Puzzle::canPutDot(int row, int col, bool hint) const {
    int grid[3][3];
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = (row - 1 + i < 0 || col - 1 + j < 0 || row -1 + i >= size.height || col - 1 + j >= size.width) ? UNKNOWN : hint ? cells[row - 1 + i][col - 1 + j].hint : cells[row - 1 + i][col - 1 + j].status;
        }
    }
    if (isDot((Status)grid[1][1]) || isDot((Status)grid[0][0]) || isDot((Status)grid[0][2]) || isDot((Status)grid[2][0]) || isDot((Status)grid[2][2])) {
        return false;
    }
    return true;
}

std::string Puzzle::toString() {
    std::stringstream ss;
    ss << size.width << ',';
    ss << size.height << ',';
    for (int i = 0; i < size.height; i++) {
        for (int j = 0; j < size.width; j++) {
            ss << (cells[i][j].hint == HINT_EMPTY ? '0' : '1');
        }
    }
    return ss.str();
}

Puzzle* Puzzle::load(const std::string &str) {
    int width, height;
    sscanf(str.c_str(), "%d,%d", &width, &height);
    Puzzle* p = new Puzzle(width, height);
    size_t pos = str.rfind(',');
    pos ++;
    p->solution.dots = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (str[pos++] == '0') {
                p->cells[i][j].hint = EMPTY;
            }
            else {
                p->cells[i][j].hint = DOT;
                p->row[i] ++;
                p->column[j] ++;
                p->solution.dots++;
                p->solution.row[i]++;
                p->solution.column[j]++;
            }
        }
    }
    p->fillHint();
    p->solution.shapes = p->calcShapes(true);
    return p;
}

void Puzzle::print() const {
    int width = size.width;
    int height = size.height;
    for (int i = 0; i < width + 1; i++) {
        std::cout << "--------";
    }
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = 0; i < width; i++) {
        std::cout << column[i] << "\t";
    }
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = 0; i < width; i++) {
        std::cout << "--------";
    }
    std::cout << std::endl;

    for (int row = 0; row < height; row++) {
        std::cout << this->row[row] << "\t";
        for (int col = 0; col < width; col++) {
            std::cout << getStatusChar(cells[row][col].hint) << "\t";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 1; i++) {
        std::cout << "========";
    }
    std::cout << std::endl;
    for (int i = 0; i < solution.shapes.size(); i++) {
        if (solution.shapes[i] > 0) {
            std::cout << "shape " << i << ": " << solution.shapes[i] << std::endl;
        }
    }
    std::cout << "dot count: " << solution.dots << std::endl;
}

void Puzzle::init() {
    cells.clear();
    for (int j = 0; j < size.height; j++) {
        cells.push_back(std::vector<Cell>());
        for (int i = 0; i < size.width; i++) {
            cells[j].push_back(Cell(i,j));
        }
    }

    shapes.clear();
    for (int i = 0; i < size.height; i ++) {
        shapes.push_back(0);
    }

    row.clear();
    for (int i = 0; i < size.height; i++) {
        row.push_back(0);
    }
    column.clear();
    for (int i = 0; i < size.width; i++) {
        column.push_back(0);
    }
}

bool Puzzle::putDotToHint(int row, int col) {
    if (canPutDot(row, col, true) == false) {
        return false;
    }
    cells[row][col].hint = DOT;
    this->row[row] ++;
    column[col] ++;
    return true;
}

void Puzzle::fillHint() {
    for (int row = 0; row < size.height; row ++) {
        for (int col = 0; col < size.width; col ++) {
            if (cells[row][col].hint == UNKNOWN || cells[row][col].hint == EMPTY) {
                cells[row][col].hint = HINT_EMPTY;
            }
            else if (cells[row][col].hint == DOT) {
                cells[row][col].hint = HINT_DOT;
            }
        }
    }
}

std::vector<int> Puzzle::calcShapes(bool hint) const {
    std::set<int> processed;
    std::vector<int> sp(size.width+1, 0);
    for (int row = 0; row < this->row.size(); row++) {
        for (int col = 0; col < this->column.size(); col++) {
            int idx = row * this->column.size() + col;
            bool dot = isDot(hint ? cells[row][col].hint : cells[row][col].status);
            if (!dot || processed.find(idx) != processed.end()) {
                continue;
            }
            int count = 1;
            processed.insert(idx);
            int r = row + 1;
            while (r < this->row.size() && isDot(hint ? cells[r][col].hint : cells[r][col].status)) {
                count++;
                processed.insert(r * this->column.size() + col);
                r++;
            }
            int c = col + 1;
            while (c < this->column.size() && isDot(hint ? cells[row][c].hint : cells[row][c].status)) {
                count++;
                processed.insert(row * this->column.size() + c);
                c++;
            }
            sp[count]++;
        }
    }
    return sp;
}
