/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MenuLayer.cpp
 * $Id: MenuLayer.cpp v 1.0 2015-01-22 12:05:31 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-04-16 00:31:19 $
 * @brief
 *
 ******************************************************************/

#include "Util.h"
#include "MenuLayer.h"
#include "StageLayer.h"
#include "Data.h"

extern "C" {
void rate();
}

USING_NS_CC;

CCSize playSize;
ccColor4F playNormColor = ccc4f(0.5, 0.5, 0.5, 1.0);
ccColor4F playSelectedColor = ccc4f(0.3, 0.3, 0.3, 1.0);
ccColor3B playNormTextColor = ccc3(180, 180, 180);
ccColor3B playSelectedTextColor = ccc3(255, 255, 255);

CCSize menuSize;

bool MenuLayer::init() {
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }

    CCSize winSize = screenSize();
    playSize = CCSize(winSize.width - 40, 100);
    menuSize = CCSize(winSize.width - 140, 70);

    CCNode* playNorm = createRoundRectNode(playSize.width, playSize.height, LargeRadius, playNormColor);
    CCNode* playSel = createRoundRectNode(playSize.width, playSize.height, LargeRadius, playSelectedColor);
    CCLabelTTF* playNormLabel = CCLabelTTF::create("Play", fontName, 64, playNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    playNormLabel->setAnchorPoint(ccp(0, 0));
    playNormLabel->setFontFillColor(playNormTextColor);
    playNorm->addChild(playNormLabel);
    CCLabelTTF* playSelLabel = CCLabelTTF::create("Play", fontName, 64, playSel->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    playSelLabel->setAnchorPoint(ccp(0, 0));
    playSelLabel->setFontFillColor(playSelectedTextColor);
    playSel->addChild(playSelLabel);
    mPlay = CCMenuItemSprite::create(playNorm, playSel, NULL, this, menu_selector(MenuLayer::menuPlayCallback));
    mPlay->setAnchorPoint(ccp(0.5, 0));
    mPlay->setPosition(ccp(0, 300));

    CCNode* settingNorm = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuNormColor);
    CCNode* settingSel = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuSelectedColor);
    CCLabelTTF* settingNormLabel = CCLabelTTF::create("Setting", fontName, 48, settingNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    settingNormLabel->setAnchorPoint(ccp(0, 0));
    settingNormLabel->setFontFillColor(menuNormTextColor);
    settingNorm->addChild(settingNormLabel);
    CCLabelTTF* settingSelLabel = CCLabelTTF::create("Setting", fontName, 48, settingSel->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    settingSelLabel->setAnchorPoint(ccp(0, 0));
    settingSelLabel->setFontFillColor(menuSelectedTextColor);
    settingSel->addChild(settingSelLabel);
    mSetting = CCMenuItemSprite::create(settingNorm, settingSel, NULL, this, menu_selector(MenuLayer::menuSettingCallback));
    mSetting->setAnchorPoint(ccp(0.5, 0));
    mSetting->setPosition(ccp(0, 200));

    CCNode* highScoreNorm = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuNormColor);
    CCNode* highScoreSel = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuSelectedColor);
    CCLabelTTF* highScoreNormLabel = CCLabelTTF::create("High Score", fontName, 52, highScoreNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    highScoreNormLabel->setAnchorPoint(ccp(0, 0));
    highScoreNormLabel->setFontFillColor(menuNormTextColor);
    highScoreNorm->addChild(highScoreNormLabel);
    CCLabelTTF* highScoreSelLabel = CCLabelTTF::create("High Score", fontName, 52, highScoreSel->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    highScoreSelLabel->setAnchorPoint(ccp(0, 0));
    highScoreSelLabel->setFontFillColor(menuSelectedTextColor);
    highScoreSel->addChild(highScoreSelLabel);
    mHighScore = CCMenuItemSprite::create(highScoreNorm, highScoreSel, NULL, this, menu_selector(MenuLayer::menuHighScoreCallback));
    mHighScore->setAnchorPoint(ccp(0.5, 0));
    mHighScore->setPosition(ccp(0, 100));

    CCNode* rateNorm = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuNormColor);
    CCNode* rateSel = createRoundRectNode(menuSize.width, menuSize.height, LargeRadius, menuSelectedColor);
    CCLabelTTF* rateNormLabel = CCLabelTTF::create("Rate Me", fontName, 48, rateNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    rateNormLabel->setAnchorPoint(ccp(0, 0));
    rateNormLabel->setFontFillColor(menuNormTextColor);
    rateNorm->addChild(rateNormLabel);
    CCLabelTTF* rateSelLabel = CCLabelTTF::create("Rate Me", fontName, 48, rateSel->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    rateSelLabel->setAnchorPoint(ccp(0, 0));
    rateSelLabel->setFontFillColor(menuSelectedTextColor);
    rateSel->addChild(rateSelLabel);
    mRate = CCMenuItemSprite::create(rateNorm, rateSel, NULL, this, menu_selector(MenuLayer::menuRateCallback));
    mRate->setAnchorPoint(ccp(0.5, 0));
    mRate->setPosition(ccp(0, 0));

    CCMenu* pMenu = CCMenu::create(mPlay, mSetting, mHighScore, mRate, NULL);
    pMenu->setPosition(ccp(winSize.width / 2, 260));
    this->addChild(pMenu);
    return true;
}

void MenuLayer::onEnter() {
    CCLayerColor::onEnter();
    CCLOG("onEnter");
}

void MenuLayer::onExit() {
    CCLayerColor::onExit();
    CCLOG("onExit");
}

void MenuLayer::menuPlayCallback(CCObject* pSender) {
    CCLOG("menuPlayCallback");
    CCDirector::sharedDirector()->replaceScene(createStageScene());
}

void MenuLayer::menuSettingCallback(CCObject* pSender) {
    CCLOG("menuSettingCallback");
}

void MenuLayer::menuHighScoreCallback(CCObject* pSender) {
    CCLOG("menuHighScoreCallback");
}

void MenuLayer::menuRateCallback(CCObject* pSender) {
    CCLOG("menuRateCallback");
    rate();
}

CCScene* createMenuScene() {
    CCScene *pScene = CCScene::create();
    MenuLayer* layer = MenuLayer::create();
    pScene->addChild(layer);
    return pScene;
}
