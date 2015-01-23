/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: MenuLayer.h
 * $Id: MenuLayer.h v 1.0 2015-01-22 12:02:34 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-23 21:30:50 $
 * @brief
 *
 ******************************************************************/
#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class MenuLayer : public CCLayerColor {
public:
    CREATE_FUNC(MenuLayer);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

    void menuPlayCallback(CCObject* pSender);
    void menuSettingCallback(CCObject* pSender);
    void menuHighScoreCallback(CCObject* pSender);
    void menuRateCallback(CCObject* pSender);
};

#endif // _MENULAYER_H_
