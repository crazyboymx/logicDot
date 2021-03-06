/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: StageLayer.h
 * $Id: StageLayer.h v 1.0 2015-01-27 07:59:20 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-04-16 01:23:33 $
 * @brief
 *
 ******************************************************************/

#ifndef _STAGELAYER_H_
#define _STAGELAYER_H_

#include <cocos2d.h>
#include <string>
#include "Util.h"
#include "LevelNode.h"

USING_NS_CC;

struct StageConfig {
    int levelCount;
    ColorSpace cs;
    std::string title;
    StageConfig& operator=(const StageConfig& conf) {
        this->levelCount = conf.levelCount;
        this->cs = conf.cs;
        this->title = conf.title;
        return *this;
    }
};

class StageLayer : public CCLayerColor {
public:
    CREATE_FUNC(StageLayer);
    ~StageLayer();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

    void initWithConfig(const StageConfig& config);

    void menuMenuCallback(CCObject* pSender);
    void registerWithTouchDispatcher();
private:
    void initLevel();

    StageConfig mConfig;
    LevelNode** mLevelNodeList;
    CCPoint mTouchBeginLoc;
};

class StageTouchLayer : public CCLayer {
public:
    CREATE_FUNC(StageTouchLayer);
    virtual ~StageTouchLayer() {};

    virtual bool init();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    void registerWithTouchDispatcher();

    void resetStageLayerPosition();
    void onMoveEndCallback();
public:
    StageLayer* left;
    StageLayer* middle;
    StageLayer* right;
private:
    CCPoint mTouchBeginLoc;
    CCPoint mTouchLastLoc;
    float mPosx;
};

StageLayer* createStageLayer(const StageData& sd);
CCScene* createStageScene();

#endif // _STAGELAYER_H_
