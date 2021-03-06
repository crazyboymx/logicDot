/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.h
 * $Id: GameLayer.h v 1.0 2015-01-27 07:59:45 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-04-16 00:13:12 $
 * @brief
 *
 ******************************************************************/

#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include <cocos2d.h>
#include <string>
#include <vector>
#include "LogicDot.h"
#include "DotNode.h"
#include "Util.h"

struct GameConfig {
    std::string puzzle;
};

class GameLayer : public CCLayerColor {
public:
    CREATE_FUNC(GameLayer);
    ~GameLayer();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

    void touchOnBoard(int row, int col);
    void doubleTouchOnBoard(int row, int col);
    void updateStatus();
    void updateLabels();
    void updateShapes();

    void initWithConfig(const GameConfig& config, const ColorSpace& cs);
    void initWithPuzzle(Puzzle* puzzle, const ColorSpace& cs);
    void registerWithTouchDispatcher();

    void menuPushCallback(CCObject* pSender);
    void menuPopCallback(CCObject* pSender);
    void menuRankCallback(CCObject* pSender);
    void menuHintCallback(CCObject* pSender);
    void menuRestartCallback(CCObject* pSender);
    void menuPauseCallback(CCObject* pSender);
private:
    void initTitle();
    void initShapes();
    void initDotNodes();
    void initMenus();
    CCNode* createShape(int dotCount, float dotSize, ccColor4F dark, ccColor4F light);

    void winGame();

    int inline index(int row, int col) {
        if (mPuzzle == NULL) {
            return 0;
        }
        return row * mPuzzle->size.height + col;
    }
    bool setDotStatus(int row, int col, Status status);
    void updateDotStatus(int row, int col);
    void updateDotStatus();

    ColorSpace mCs;
    Puzzle* mPuzzle;
    CCNode* mBoard;
    std::vector<DotNode*> mDotNodeList;
    CCLabelTTF* mRowLabelList[20];
    CCLabelTTF* mColLabelList[20];
    CCLabelTTF* mScoreLabel;
    CCNode* mTitleBg;
    CCNode* mShapesBg;
    std::map<int, CCNode*> mShapesList;
    std::map<int, CCNode*> mMatchedShapesList;

    CCMenuItem* mPush;
    CCMenuItem* mPop;
    CCMenuItem* mRank;
    CCMenuItem* mHint;
    CCMenuItem* mRestart;
    CCMenuItem* mPause;

    Status mStatusInDrag;
    double mLastTouchTime;
    int mLastTouchIndex;
};

CCScene* createGameScene(Puzzle* puzzle, const ColorSpace& cs);
#endif // _GAMELAYER_H_
