/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: StageLayer.h
 * $Id: StageLayer.h v 1.0 2015-01-27 07:59:20 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-27 11:12:30 $
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
};

class StageLayer : public CCLayerColor {
public:
    CREATE_FUNC(StageLayer);
    ~StageLayer();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

    void initWithConfig(const StageConfig& config);

    void menuMenuCallback(CCObject* pSender);
private:
    void initLevel();

    StageConfig mConfig;
    LevelNode** mLevelNodeList;
};

#endif // _STAGELAYER_H_
