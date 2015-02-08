/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.cpp
 * $Id: GameLayer.cpp v 1.0 2015-01-27 07:59:49 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-08 18:05:04 $
 * @brief
 *
 ******************************************************************/

#include "GameLayer.h"
#include "Util.h"

USING_NS_CC;

GameLayer::~GameLayer() {
    if (mPuzzle != NULL) {
        delete mPuzzle;
    }
}

bool GameLayer::init() {
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }
    this->setTouchEnabled(true);
    mPuzzle = NULL;
    mBoard = NULL;
    mStatusInDrag = UNKNOWN;
    mLastTouchTime = 0;
    mLastTouchIndex = -1;
    return true;
}

void GameLayer::onEnter() {
    CCLayerColor::onEnter();
}

void GameLayer::onExit() {
    CCLayerColor::onExit();
}

void GameLayer::initWithConfig(const GameConfig& config, const ColorSpace& cs) {
    Puzzle* puzzle = Puzzle::load(config.puzzle);
    initWithPuzzle(puzzle, cs);
}

void GameLayer::initWithPuzzle(Puzzle* puzzle, const ColorSpace& cs) {
    mPuzzle = puzzle;
    mCs = cs;
    initDotNodes();
}

void GameLayer::initDotNodes() {
    if (mPuzzle == NULL) {
        return;
    }
    Size size = mPuzzle->size;
    CCSize winSize = screenSize();
    float gridBoarder = 10;
    float labelSize = 60;
    CCSize gridSize = CCSize(winSize.width - labelSize * 2, winSize.width - labelSize * 2);
    float gridLength = (gridSize.width - gridBoarder * 2) / size.width;
    float dotNodeLength = gridLength - GRID_GAP;
    mBoard = createRoundRectNode(gridSize.width, gridSize.height, MiddleRadius, mCs.normal);
    mBoard->setAnchorPoint(ccp(0.5, 0));
    mBoard->setPosition(winSize.width / 2, 120);
    this->addChild(mBoard);
    CCLabelTTF* lt = CCLabelTTF::create("0", fontName, 32);
    this->addChild(lt);
    for (int row = 0; row < mPuzzle->row.size(); row++) {
        CCLabelTTF* label = CCLabelTTF::create(number2string(mPuzzle->row[row]).c_str(), fontName, 32);
        label->setAnchorPoint(ccp(0.5, 0.5));
        label->setPosition(ccp(- labelSize / 2, gridSize.height - gridLength * row - gridLength / 2 - gridBoarder));
        label->setFontFillColor(mCs.fontColor);
        mBoard->addChild(label);
        mRowLabelList[row] = label;
    }
    for (int col = 0; col < mPuzzle->size.width; col++) {
        CCLabelTTF* label = CCLabelTTF::create(number2string(mPuzzle->column[col]).c_str(), fontName, 32);
        label->setAnchorPoint(ccp(0.5, 0.5));
        label->setPosition(ccp(gridLength * col + gridLength / 2 + gridBoarder, gridSize.height + labelSize / 2));
        label->setFontFillColor(mCs.fontColor);
        mBoard->addChild(label);
        mColLabelList[col] = label;
    }
    for (int row = 0; row < mPuzzle->size.height; row++) {
        for (int col = 0; col < mPuzzle->size.width; col++) {
            int idx = index(row, col);
            mDotNodeList.push_back(DotNode::create());
            mDotNodeList[idx]->init(mCs, dotNodeLength, dotNodeLength, mPuzzle->cells[row][col].status);
            mDotNodeList[idx]->setAnchorPoint(ccp(0.5, 0.5));
            mDotNodeList[idx]->setPosition(ccp(gridLength * col + gridLength / 2 + gridBoarder, gridSize.height - gridLength * row - gridLength / 2 - gridBoarder));
            mBoard->addChild(mDotNodeList[idx]);
        }
    }
}

void GameLayer::updateLabels() {
    for (int i = 0; i < mPuzzle->row.size(); i++) {
        mRowLabelList[i]->setString(number2string(mPuzzle->row[i]).c_str());
    }
    for (int i = 0; i < mPuzzle->column.size(); i++) {
        mColLabelList[i]->setString(number2string(mPuzzle->column[i]).c_str());
    }
}

void GameLayer::touchOnBoard(int row, int col) {
    Status status = mPuzzle->cells[row][col].status;
    if (status == UNKNOWN) {
        mPuzzle->setStatus(row, col, EMPTY);
        mDotNodeList[index(row, col)]->setStatus(EMPTY, mPuzzle->cells[row][col].flag);
    }
    else {
        mPuzzle->setStatus(row, col, UNKNOWN);
        mDotNodeList[index(row, col)]->setStatus(UNKNOWN, mPuzzle->cells[row][col].flag);
    }
    updateLabels();
}

void GameLayer::doubleTouchOnBoard(int row, int col) {
    mPuzzle->setStatus(row, col, DOT);
    mDotNodeList[index(row, col)]->setStatus(DOT, mPuzzle->cells[row][col].flag);
    updateLabels();
}

bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    if (pointInNode(mBoard, location) == false) {
        return false;
    }
    for (int row = 0; row < mPuzzle->size.height; row++) {
        for (int col = 0; col < mPuzzle->size.width; col++) {
            int idx = index(row, col);
            if (pointInNode(mDotNodeList[idx], location) == false) {
                continue;
            }
            if (isHint(mPuzzle->cells[row][col].status)) {
                return false;
            }
            long touchTime = currentTime();
            if ((touchTime - mLastTouchTime) < DOUBLE_CLICK_THRESHOLD) {
                doubleTouchOnBoard(row, col);
                mLastTouchTime = 0;
                mStatusInDrag = DOT;
            }
            else {
                mLastTouchTime = touchTime;
                touchOnBoard(row, col);
                mStatusInDrag = mPuzzle->cells[row][col].status;
            }
            return true;
        }
    }

    return false;
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    if (pointInNode(mBoard, location) == false) {
        return;
    }
    for (int row = 0; row < mPuzzle->size.height; row++) {
        for (int col = 0; col < mPuzzle->size.width; col++) {
            int idx = index(row, col);
            if (pointInNode(mDotNodeList[idx], location) == false) {
                continue;
            }
            if (isHint(mPuzzle->cells[row][col].status)) {
                return;
            }
            if (mLastTouchIndex != idx) {
                mLastTouchIndex = idx;
                mPuzzle->setStatus(row, col, mStatusInDrag);
                mDotNodeList[idx]->setStatus(mStatusInDrag, mPuzzle->cells[row][col].flag);
                updateLabels();
            }
            return;
        }
    }
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    //this->removeFromParent();
}

void GameLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kTouchPriorityLayer, true);
}
