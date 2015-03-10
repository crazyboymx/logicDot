/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: WinLayer.cpp
 * $Id: WinLayer.cpp v 1.0 2015-03-09 12:00:21 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-03-10 23:55:11 $
 * @brief
 *
 ******************************************************************/

#include "WinLayer.h"
#include "Util.h"
#include "GameLayer.h"
#include "StageLayer.h"

USING_NS_CC;

bool WinLayer::init() {
    if (!CCLayerColor::initWithColor(ccc4(76, 76, 76, 230))) {
        return false;
    }

    CCSize winSize = screenSize();
    CCLabelTTF* labelCon = CCLabelTTF::create("Congratulations", fontName, 60, CCSize(winSize.width, 80), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    labelCon->setPosition(ccp(0, winSize.height * 0.75));
    labelCon->setAnchorPoint(ccp(0, 0));
    this->addChild(labelCon);

    CCLabelTTF* labelScore = CCLabelTTF::create("Find Dots: 0", fontName, 40, CCSize(winSize.width, 60), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    labelScore->setPosition(ccp(0, labelCon->getPositionY() - 80));
    labelScore->setAnchorPoint(ccp(0, 0));
    this->addChild(labelScore);

    CCSize menuSize = CCSize(winSize.width * 0.65, 70);
    CCNode* nextNorm = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuNormColor);
    CCNode* nextSel = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuSelectedColor);
    CCLabelTTF* nextNormLabel = CCLabelTTF::create("Next Level", fontName, 48, menuSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    nextNormLabel->setAnchorPoint(ccp(0, 0));
    nextNormLabel->setFontFillColor(menuNormTextColor);
    nextNorm->addChild(nextNormLabel);
    CCLabelTTF* nextSelLabel = CCLabelTTF::create("Next Level", fontName, 48, menuSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    nextSelLabel->setAnchorPoint(ccp(0, 0));
    nextSelLabel->setFontFillColor(menuSelectedTextColor);
    nextSel->addChild(nextSelLabel);
    CCMenuItem* next = CCMenuItemSprite::create(nextNorm, nextSel, NULL, this, menu_selector(WinLayer::menuNextLevelCallback));
    next->setAnchorPoint(ccp(0.5, 0));
    next->setPosition(ccp(0, -100));

    CCNode* menuNorm = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuNormColor);
    CCNode* menuSel = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuSelectedColor);
    CCLabelTTF* menuNormLabel = CCLabelTTF::create("Menu", fontName, 48, menuSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    menuNormLabel->setFontFillColor(menuNormTextColor);
    menuNormLabel->setAnchorPoint(ccp(0, 0));
    menuNorm->addChild(menuNormLabel);
    CCLabelTTF* menuSelLabel = CCLabelTTF::create("Menu", fontName, 48, menuSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    menuSelLabel->setFontFillColor(menuSelectedTextColor);
    menuSelLabel->setAnchorPoint(ccp(0, 0));
    menuSel->addChild(menuSelLabel);
    CCMenuItem* menuMenuItem = CCMenuItemSprite::create(menuNorm, menuSel, NULL, this, menu_selector(WinLayer::menuBackToMenuLayerCallback));
    menuMenuItem->setAnchorPoint(ccp(0.5, 0));
    menuMenuItem->setPosition(ccp(0, -250));

    CCMenu* pMenu = CCMenu::create(next, menuMenuItem, NULL);
    pMenu->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(pMenu);
    return true;
}

void WinLayer::onEnter() {
    CCLayerColor::onEnter();
}

void WinLayer::onExit() {
    CCLayerColor::onExit();
}

void WinLayer::init(int score, int size, int level) {
}

void WinLayer::menuNextLevelCallback(CCObject* pSender) {
    if (endStage() && endLevelOfStage()) {
    }
    else {
        nextLevel();
        CCScene *pScene = CCScene::create();
        GameLayer* gl = GameLayer::create();
        gl->initWithPuzzle(Puzzle::load(puzzleData.stages[playerData.currentStage].puzzles[playerData.currentLevel]), Red);
        pScene->addChild(gl);
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void WinLayer::menuBackToMenuLayerCallback(CCObject* pSender) {
    CCScene *pScene = CCScene::create();
    StageLayer* sl = StageLayer::create();
    StageConfig config = {30, Red, "5X5 Packer"};
    sl->initWithConfig(config);
    pScene->addChild(sl);
    CCDirector::sharedDirector()->replaceScene(pScene);
}
