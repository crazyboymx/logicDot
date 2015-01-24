/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: LogicDot.cpp
 * $Id: LogicDot.cpp v 1.0 2015-01-20 20:10:39 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-22 11:43:08 $
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
    case HINT_EMPTY: return ' '; break;
    case HINT_DOT_ALONE: return '.'; break;
    case HINT_DOT_UP: return '^'; break;
    case HINT_DOT_LEFT: return '<'; break;
    case HINT_DOT_RIGHT: return '>'; break;
    case HINT_DOT_DOWN: return 'v'; break;
    case HINT_DOT_UP_DOWN: return '|'; break;
    case HINT_DOT_LEFT_RIGHT: return '-'; break;
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
            if (putDotToCell(*p, row, col)) {
                dots --;
            }
            i++;
        }
        if (dots > 0) {
            std::cout << "remain dots: " << dots << std::endl;
        }
        fillHint(*p);
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
    fillHint(*p);
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

bool Puzzle::putDotToCell(Puzzle& p, int row, int col) {
    int grid[3][3];
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
    }
    p.cells[row][col].hint = DOT;
    p.row[row] ++;
    p.column[col] ++;
    return true;
}

void Puzzle::fillHint(Puzzle& p) {
    for (int row = 0; row < p.size.height; row ++) {
        for (int col = 0; col < p.size.width; col ++) {
            if (p.cells[row][col].hint == UNKNOWN || p.cells[row][col].hint == EMPTY) {
                p.cells[row][col].hint = HINT_EMPTY;
            }
            else if (p.cells[row][col].hint == DOT) {
                if (row + 1 >= p.size.height || p.cells[row+1][col].hint != DOT) {
                    if (col + 1 >= p.size.width || p.cells[row][col+1].hint != DOT) {
                        p.cells[row][col].hint = HINT_DOT_ALONE;
                        p.solution.shapes[1] ++;
                    }
                    else {
                        p.cells[row][col].hint = HINT_DOT_RIGHT;
                        int i = 1;
                        while (col + i < p.size.width && p.cells[row][col+i].hint == DOT) {
                            p.cells[row][col+i].hint = HINT_DOT_LEFT_RIGHT;
                            i++;
                        }
                        p.cells[row][col+i-1].hint = HINT_DOT_LEFT;
                        p.solution.shapes[i] ++;
                    }
                }
                else {
                    p.cells[row][col].hint = HINT_DOT_DOWN;
                    int i = 1;
                    while (row + i < p.size.height && p.cells[row+i][col].hint == DOT) {
                        p.cells[row+i][col].hint = HINT_DOT_UP_DOWN;
                        i++;
                    }
                    p.cells[row+i-1][col].hint = HINT_DOT_UP;
                    p.solution.shapes[i] ++;
                }
            }
        }
    }
}

