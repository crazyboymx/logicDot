/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MenuLayer.cpp
 * $Id: MenuLayer.cpp v 1.0 2015-01-22 12:05:31 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-23 21:31:56 $
 * @brief
 *
 ******************************************************************/

#include "Util.h"
#include "MenuLayer.h"

USING_NS_CC;

float roundRadius = 20;
CCSize playSize = CCSize(600, 100);
ccColor4F playNormColor = ccc4f(0.5, 0.5, 0.5, 1.0);
ccColor4F playSelectedColor = ccc4f(0.3, 0.3, 0.3, 1.0);
ccColor3B playNormTextColor = ccc3(200, 200, 200);
ccColor3B playSelectedTextColor = ccc3(255, 255, 255);

CCSize menuSize = CCSize(500, 70);
ccColor4F menuNormColor = ccc4f(0.7, 0.7, 0.7, 1.0);
ccColor4F menuSelectedColor = ccc4f(0.55, 0.55, 0.55, 1.0);
ccColor3B menuNormTextColor = ccc3(200, 200, 200);
ccColor3B menuSelectedTextColor = ccc3(255, 255, 255);

bool MenuLayer::init() {
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLOG("origin:%0.2f, %0.2f, visibleSize: %0.2f, %0.2f", origin.x, origin.y, visibleSize.width, visibleSize.height);

    CCNode* playNorm = createRoundRectNode(playSize.width, playSize.height, roundRadius, playNormColor);
    CCNode* playSel = createRoundRectNode(playSize.width, playSize.height, roundRadius, playSelectedColor);    CCLabelTTF* playNormLabel = CCLabelTTF::create("Play", "Helvetica", 64, playNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    playNormLabel->setAnchorPoint(ccp(0, 0));
    playNormLabel->setFontFillColor(playNormTextColor);
    playNorm->addChild(playNormLabel);
    CCLabelTTF* playSelLabel = CCLabelTTF::create("Play", "Helvetica", 64, playSel->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    playSelLabel->setAnchorPoint(ccp(0, 0));
    playSelLabel->setFontFillColor(playSelectedTextColor);
    playSel->addChild(playSelLabel);
    mPlay = CCMenuItemSprite::create(playNorm, playSel, NULL, this, menu_selector(MenuLayer::menuPlayCallback));
    mPlay->setAnchorPoint(ccp(0.5, 0));
    mPlay->setPosition(ccp(0, 300));

    CCNode* settingNorm = createRoundRectNode(menuSize.width, menuSize.height, roundRadius, menuNormColor);
    CCNode* settingSel = createRoundRectNode(menuSize.width, menuSize.height, roundRadius, menuSelectedColor);
    CCLabelTTF* settingNormLabel = CCLabelTTF::create("Setting", "Helvetica", 48, settingNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    settingNormLabel->setAnchorPoint(ccp(0, 0));
    settingNormLabel->setFontFillColor(menuNormTextColor);
    settingNorm->addChild(settingNormLabel);
    CCLabelTTF* settingSelLabel = CCLabelTTF::create("Setting", "Helvetica", 48, settingSel->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    settingSelLabel->setAnchorPoint(ccp(0, 0));
    settingSelLabel->setFontFillColor(menuSelectedTextColor);
    settingSel->addChild(settingSelLabel);
    mSetting = CCMenuItemSprite::create(settingNorm, settingSel, NULL, this, menu_selector(MenuLayer::menuSettingCallback));
    mSetting->setAnchorPoint(ccp(0.5, 0));
    mSetting->setPosition(ccp(0, 200));

    CCNode* highScoreNorm = createRoundRectNode(menuSize.width, menuSize.height, roundRadius, menuNormColor);
    CCNode* highScoreSel = createRoundRectNode(menuSize.width, menuSize.height, roundRadius, menuSelectedColor);
    CCLabelTTF* highScoreNormLabel = CCLabelTTF::create("High Score", "Helvetica", 52, highScoreNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    highScoreNormLabel->setAnchorPoint(ccp(0, 0));
    highScoreNormLabel->setFontFillColor(menuNormTextColor);
    highScoreNorm->addChild(highScoreNormLabel);
    CCLabelTTF* highScoreSelLabel = CCLabelTTF::create("High Score", "Helvetica", 52, highScoreSel->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    highScoreSelLabel->setAnchorPoint(ccp(0, 0));
    highScoreSelLabel->setFontFillColor(menuSelectedTextColor);
    highScoreSel->addChild(highScoreSelLabel);
    mHighScore = CCMenuItemSprite::create(highScoreNorm, highScoreSel, NULL, this, menu_selector(MenuLayer::menuHighScoreCallback));
    mHighScore->setAnchorPoint(ccp(0.5, 0));
    mHighScore->setPosition(ccp(0, 100));

    CCNode* rateNorm = createRoundRectNode(menuSize.width, menuSize.height, roundRadius, menuNormColor);
    CCNode* rateSel = createRoundRectNode(menuSize.width, menuSize.height, roundRadius, menuSelectedColor);
    CCLabelTTF* rateNormLabel = CCLabelTTF::create("Rate Me", "Helvetica", 48, rateNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    rateNormLabel->setAnchorPoint(ccp(0, 0));
    rateNormLabel->setFontFillColor(menuNormTextColor);
    rateNorm->addChild(rateNormLabel);
    CCLabelTTF* rateSelLabel = CCLabelTTF::create("Rate Me", "Helvetica", 48, rateSel->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    rateSelLabel->setAnchorPoint(ccp(0, 0));
    rateSelLabel->setFontFillColor(menuSelectedTextColor);
    rateSel->addChild(rateSelLabel);
    mRate = CCMenuItemSprite::create(rateNorm, rateSel, NULL, this, menu_selector(MenuLayer::menuRateCallback));
    mRate->setAnchorPoint(ccp(0.5, 0));
    mRate->setPosition(ccp(0, 0));

    CCMenu* pMenu = CCMenu::create(mPlay, mSetting, mHighScore, mRate, NULL);
    pMenu->setPosition(ccp(visibleSize.width / 2, 260));
    this->addChild(pMenu);
    return true;
}

void MenuLayer::onEnter() {
    CCLOG("onEnter");
}

void MenuLayer::onExit() {
    CCLOG("onExit");
}

void MenuLayer::menuPlayCallback(CCObject* pSender) {
    CCLOG("menuPlayCallback");
}

void MenuLayer::menuSettingCallback(CCObject* pSender) {
    CCLOG("menuSettingCallback");
}

void MenuLayer::menuHighScoreCallback(CCObject* pSender) {
    CCLOG("menuHighScoreCallback");
}

void MenuLayer::menuRateCallback(CCObject* pSender) {
    CCLOG("menuRateCallback");
}

