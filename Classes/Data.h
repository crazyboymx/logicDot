/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Data.h
 * $Id: Data.h v 1.0 2015-03-09 17:40:50 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-03-10 23:02:38 $
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

struct PuzzleData {
    int count;
    int dotCount;
    StageData* stages;
};

extern PuzzleData puzzleData;

struct PlayerData {
    int currentStage;
    int currentLevel;
    int lastStage;
    int lastLevel;
    int score;
    bool hasPlayed;
};

extern PlayerData playerData;

void loadPlayerData();
void savePlayerData();

void nextLevel();
bool endLevelOfStage();
bool endStage();

#endif // _DATA_H_
