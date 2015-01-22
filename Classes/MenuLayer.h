/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MenuLayer.h
 * $Id: MenuLayer.h v 1.0 2015-01-22 12:02:34 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-22 12:04:54 $
 * @brief
 *
 ******************************************************************/
#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class MenuLayer : public CCLayer {
public:
    CREATE_FUN(MenuLayer);
    virtual bool init();
    void menuCloseCallback(CCObject* pSender);
};

#endif // _MENULAYER_H_
