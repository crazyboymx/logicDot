/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Data.h
 * $Id: Data.h v 1.0 2015-03-09 17:40:50 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-03-09 18:21:02 $
 * @brief
 *
 ******************************************************************/

#ifndef _DATA_H_
#define _DATA_H_

#include <string>

struct StageData {
    int stage;
    int puzzleSize;
    int count;
    int dotCount;
    std::string* puzzles;
};

struct LevelData {
    int count;
    int dotCount;
    StageData* stages;
};

extern LevelData levelData;

#endif // _DATA_H_
