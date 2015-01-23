/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MenuLayer.cpp
 * $Id: MenuLayer.cpp v 1.0 2015-01-22 12:05:31 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-23 18:29:01 $
 * @brief
 *
 ******************************************************************/

#include <Util.h>
#include <MenuLayer.h>

USING_NS_CC;

bool MenuLayer::init() {
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCNode* m1 = createRoundRectNode(600, 100, 20, ccc4f(0.7, 0.7, 0.7, 1.0));
    CCNode* m1d = createRoundRectNode(600, 100, 20, ccc4f(0.3, 0.3, 0.3, 1.0));
    CCMenuItem* mi = CCMenuItemSprite::create(m1, m1d, NULL, this, menu_selector(MenuLayer::menuPlayCallback));
    CCMenu* pMenu = CCMenu::create(mi, NULL);
    pMenu->setPosition(ccp(visibleSize.width / 2, 600));
    this->addChild(pMenu);
    return true;
}

void MenuLayer::menuPlayCallback(CCObject* pSender) {
}
