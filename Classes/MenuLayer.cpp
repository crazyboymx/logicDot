/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MenuLayer.cpp
 * $Id: MenuLayer.cpp v 1.0 2015-01-22 12:05:31 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-23 21:31:56 $
 * @brief
 *
 ******************************************************************/

#include <Util.h>
#include <MenuLayer.h>

USING_NS_CC;

ccColor4F playNormColor = ccc4f(0.5, 0.5, 0.5, 1.0);
ccColor4F playSelectedColor = ccc4f(0.3, 0.3, 0.3, 1.0);
ccColor4F menuNormColor = ccc4f(0.7, 0.7, 0.7, 1.0);
ccColor4F menuSelectedColor = ccc4f(0.55, 0.55, 0.55, 1.0);

bool MenuLayer::init() {
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCNode* playNorm = createRoundRectNode(600, 100, 20, playNormColor);
    CCNode* playSel = createRoundRectNode(600, 100, 20, playSelectedColor);
    CCMenuItem* play = CCMenuItemSprite::create(playNorm, playSel, NULL, this, menu_selector(MenuLayer::menuPlayCallback));
    play->setPosition(ccp(0, 420));

    CCNode* settingNorm = createRoundRectNode(600, 70, 20, menuNormColor);
    CCNode* settingSel = createRoundRectNode(600, 70, 20, menuSelectedColor);
    CCMenuItem* setting = CCMenuItemSprite::create(settingNorm, settingSel, NULL, this, menu_selector(MenuLayer::menuSettingCallback));
    //setting->setAnchorPoint(ccp(0, 0));
    setting->setPosition(ccp(0, 280));

    CCNode* highScoreNorm = createRoundRectNode(600, 70, 20, menuNormColor);
    CCNode* highScoreSel = createRoundRectNode(600, 70, 20, menuSelectedColor);
    CCMenuItem* highScore = CCMenuItemSprite::create(highScoreNorm, highScoreSel, NULL, this, menu_selector(MenuLayer::menuHighScoreCallback));
    //highScore->setAnchorPoint(ccp(0, 0));
    highScore->setPosition(ccp(0, 140));

    CCNode* rateNorm = createRoundRectNode(600, 70, 20, menuNormColor);
    CCNode* rateSel = createRoundRectNode(600, 70, 20, menuSelectedColor);
    CCMenuItem* rate = CCMenuItemSprite::create(rateNorm, rateSel, NULL, this, menu_selector(MenuLayer::menuRateCallback));
    //rate->setAnchorPoint(ccp(0, 0));
    rate->setPosition(ccp(0, 0));

    CCMenu* pMenu = CCMenu::create(play, setting, highScore, rate, NULL);
    pMenu->setPosition(ccp(visibleSize.width / 2, 140));
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

