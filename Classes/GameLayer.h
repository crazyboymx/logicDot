/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.h
 * $Id: GameLayer.h v 1.0 2015-01-27 07:59:45 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-27 07:59:45 $
 * @brief
 *
 ******************************************************************/

#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include <cocos2d.h>
#include <string>
#include "LogicDot.h"
#include "Util.h"

struct GameConfig {
    std::string puzzle;
};

class GameLayer : public CCLayerColor {
public:
    CREATE_FUNC(GameLayer);
    ~GameLayer();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    void initWithConfig(const GameConfig& config);
private:
    GameConfig mConfig;
    Puzzle* mPuzzle;
};

#endif // _GAMELAYER_H_