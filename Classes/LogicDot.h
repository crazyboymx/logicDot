/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: LogicDot.h
 * $Id: LogicDot.h v 1.0 2015-01-22 11:34:29 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-22 11:41:50 $
 * @brief
 *
 ******************************************************************/
#ifndef  _LOGICDOT_H_
#define  _LOGICDOT_H_

#include <string>
#include <vector>

struct Point {
    int x;
    int y;
};

struct Size {
    int width;
    int height;
};

enum Status {
    UNKNOWN = 0,
    EMPTY,
    DOT,
    DOT_ALONE,
    DOT_LEFT,
    DOT_UP,
    DOT_RIGHT,
    DOT_DOWN,
    DOT_LEFT_RIGHT,
    DOT_UP_DOWN,
    HINT_EMPTY,
    HINT_DOT_ALONE,
    HINT_DOT_LEFT,
    HINT_DOT_UP,
    HINT_DOT_RIGHT,
    HINT_DOT_DOWN,
    HINT_DOT_LEFT_RIGHT,
    HINT_DOT_UP_DOWN,
    MAX_STATUS,
};

inline bool isDot(Status status) {
    return status != UNKNOWN && status != EMPTY && status != HINT_EMPTY && status != MAX_STATUS;
}

struct Cell {
    Point pos;
    Status status;
    Status hint;
    Cell(int row, int column) {
        pos.x = row;
        pos.y = column;
        reset();
    }

    void reset() {
        status = UNKNOWN;
        hint = UNKNOWN;
    }
};

enum Shapes {
    ZERO = 0,
    ONE,
    TWO,
    TREE,
    FORE,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    MAX_SHAPE,
};

struct Solution {
    std::vector<int> shapes;
    int dots;

    Solution() {
        for (int i = ZERO; i < MAX_SHAPE; i++) {
            shapes.push_back(0);
        }
        dots = 0;
    }
};

class Puzzle {
public:
    std::vector<std::vector<Cell> > cells;
    std::vector<int> row;
    std::vector<int> column;
    Size size;
    Solution solution;

    ~Puzzle() {}

    static Puzzle* generate(int width, int height);
    bool valid();
    void clear();
    void setStatus(int row, int col, Status status);
    bool canPutDot(int row, int col);

    std::string toString();
    static Puzzle* load(const std::string &str);

    void print() const;
protected:
    Puzzle(int width, int height) {
        size.width = width;
        size.height = height;
        init();
    }
    Puzzle(const Puzzle&);
    Puzzle& operator=(const Puzzle&);

    void init();
    static bool putDotToCell(Puzzle& p, int row, int col);
    static void fillHint(Puzzle& p);
};

#endif // _LOGICDOT_H_
