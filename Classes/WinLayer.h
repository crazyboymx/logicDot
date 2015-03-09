/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: WinLayer.h
 * $Id: WinLayer.h v 1.0 2015-03-09 12:00:15 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-03-09 12:12:46 $
 * @brief
 *
 ******************************************************************/

#ifndef _WINLAYER_H_
#define _WINLAYER_H_

#include <cocos2d.h>

USING_NS_CC;

class WinLayer : public CCLayerColor {
public:
    CREATE_FUNC(WinLayer);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

    void init(int score, int size, int level);

    void menuNextLevelCallback(CCObject* pSender);
    void menuBackToMenuLayerCallback(CCObject* pSender);

private:
    CCLabelTTF* mScore;
};

#endif // _WinLayer_H_
