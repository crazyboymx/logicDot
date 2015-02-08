/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: LogicDot.cpp
 * $Id: LogicDot.cpp v 1.0 2015-01-20 20:10:39 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-08 15:29:32 $
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

int myrandom(int i) {
    return rand() % i;
}

int random(int min, int max) {
    static int initRand = 0;
    if (initRand == 0) {
        srand((unsigned)time(NULL));
        initRand ++;
    }
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

Puzzle* Puzzle::generate(int width, int height) {
    Puzzle* p = new Puzzle(width, height);
    int max = width * height - 1;
    std::vector<int> candidate;
    for (int i = 0; i < max; i++) {
        candidate.push_back(i);
    }
    std::srand(unsigned(std::time(0)));
    while(!p->valid()) {
        p->solution.dots = random((width - 3)*(height-3), (width - 2)*(height-2));
        std::random_shuffle(candidate.begin(), candidate.end(), myrandom);
        int i = 0;
        int dots = p->solution.dots;
        while (dots > 0 && i < max) {
            int idx = candidate[i];
            int row = idx / width;
            int col = idx % width;
            if (p->putDotToHint(row, col)) {
                dots --;
            }
            i++;
        }
        if (dots > 0) {
            std::cout << "remain dots: " << dots << std::endl;
        }
        p->fillHint();
        if (p->valid() == false) {
            std::cout << "not valid" << std::endl;
            p->clear();
        }
    }

    return p;
}

bool Puzzle::valid() {
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
    cells[row][col].status = status;
    if (isDot(oldStatus) && !isDot(status)) {
        this->row[row]++;
        this->column[col]++;
    }
    else if (!isDot(oldStatus) && isDot(status)) {
        this->row[row]--;
        this->column[col]--;
    }
}

bool Puzzle::canPutDot(int row, int col) {
    int grid[3][3];
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = (row - 1 + i < 0 || col - 1 + j < 0 || row -1 + i >= size.height || col - 1 + j >= size.width) ? UNKNOWN : cells[row - 1 + i][col - 1 + j].hint;
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
            }
        }
    }
    p->fillHint();
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
    for (int j = 0; j < size.height; j++) {
        cells.push_back(std::vector<Cell>());
        for (int i = 0; i < size.width; i++) {
            cells[j].push_back(Cell(i,j));
        }
    }

    for (int i = 0; i < size.height; i++) {
        row.push_back(0);
    }
    for (int i = 0; i < size.width; i++) {
        column.push_back(0);
    }
}

bool Puzzle::putDotToHint(int row, int col) {
    /*int grid[3][3];
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = (row - 1 + i < 0 || col - 1 + j < 0 || row -1 + i >= p.size.height || col - 1 + j >= p.size.width) ? UNKNOWN : p.cells[row - 1 + i][col - 1 + j].hint;
        }
    }
    if (grid[1][1] == DOT || grid[0][0] == DOT || grid[0][2] == DOT || grid[2][0] == DOT || grid[2][2] == DOT) {
        return false;
    }
    if ((grid[0][1] == DOT && (grid[0][0] == DOT || grid[0][2] == DOT || grid[1][0] == DOT || grid[1][2] == DOT)) ||
        (grid[1][0] == DOT && (grid[0][0] == DOT || grid[2][0] == DOT || grid[0][1] == DOT || grid[2][1] == DOT)) ||
        (grid[2][1] == DOT && (grid[2][0] == DOT || grid[2][2] == DOT || grid[1][0] == DOT || grid[1][2] == DOT)) ||
        (grid[1][2] == DOT && (grid[0][2] == DOT || grid[2][2] == DOT || grid[0][1] == DOT || grid[2][1] == DOT))) {
        return false;
    }*/
    if (canPutDot(row, col) == false) {
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

