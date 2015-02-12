/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: LogicDot.h
 * $Id: LogicDot.h v 1.0 2015-01-22 11:34:29 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-12 17:11:14 $
 * @brief
 *
 ******************************************************************/
#ifndef  _LOGICDOT_H_
#define  _LOGICDOT_H_

#include <string>
#include <vector>

#define LEFT        0X00010000
#define UP          0X00020000
#define RIGHT       0X00040000
#define DOWN        0X00080000
#define HINT_LEFT   0X00100000
#define HINT_UP     0X00200000
#define HINT_RIGHT  0X00400000
#define HINT_DOWN   0X00800000

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
    HINT_EMPTY,
    HINT_DOT,
};

inline bool isDot(Status status) {
    return status == DOT || status == HINT_DOT;
}

inline bool isHint(Status status) {
    return status == HINT_EMPTY || status == HINT_DOT;
}

struct Cell {
    Point pos;
    Status status;
    Status hint;
    int flag;
    Cell(int row, int column) {
        pos.x = row;
        pos.y = column;
        reset();
    }

    void reset() {
        status = UNKNOWN;
        hint = UNKNOWN;
        flag = 0;
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
    bool canPutDot(int row, int col, bool hint = false);
    void updateFlag(int row, int col);

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
    bool putDotToHint(int row, int col);
    void fillHint();
};

#endif // _LOGICDOT_H_
