/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MenuLayer.cpp
 * $Id: MenuLayer.cpp v 1.0 2015-01-22 12:05:31 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-22 12:06:36 $
 * @brief
 *
 ******************************************************************/

#include <MenuLayer.h>

USING_NS_CC;

bool MenuLayer::init() {
    if (!CCLayer::init()) {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
}
