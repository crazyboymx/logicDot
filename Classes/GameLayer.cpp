/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.cpp
 * $Id: GameLayer.cpp v 1.0 2015-01-27 07:59:49 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-03 11:05:51 $
 * @brief
 *
 ******************************************************************/

#include "GameLayer.h"

USING_NS_CC;

GameLayer::~GameLayer() {
    if (mPuzzle != NULL) {
        delete mPuzzle;
    }
    if (mDotNodeList != NULL) {
        delete[] mDotNodeList;
    }
}

bool GameLayer::init() {
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }
    this->setTouchEnabled(true);
    mPuzzle = NULL;
    mDotNodeList = NULL;
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
    CCSize gridSize = CCSize(winSize.width - 40, winSize.width - 40);
    float gridLength = gridSize.width / size.width;
    float dotNodeLength = gridLength - 10;
    CCNode* boardBg = createRoundRectNode(gridSize.width, gridSize.height, MiddleRadius, mCs.normal);
    boardBg->setAnchorPoint(ccp(0.5, 0));
    boardBg->setPosition(winSize.width / 2, 120);
    this->addChild(boardBg);
    mDotNodeList = new DotNode*[mPuzzle->cells.size()];
    for (int row = 0; row < mPuzzle->size.height; row++) {
        for (int col = 0; col < mPuzzle->size.width; col++) {
            int idx = index(row, col);
            mDotNodeList[idx] = DotNode::create();
            mDotNodeList[idx]->init(mCs, dotNodeLength, dotNodeLength, mPuzzle->cells[row][col].hint);
            mDotNodeList[idx]->setAnchorPoint(ccp(0.5, 0.5));
            mDotNodeList[idx]->setPosition(ccp(gridLength * col + gridLength / 2, gridSize.height - gridLength * row - gridLength / 2));
            boardBg->addChild(mDotNodeList[idx]);
        }
    }
}

bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    return true;
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    this->removeFromParent();
}

void GameLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kTouchPriorityLayer, true);
}
