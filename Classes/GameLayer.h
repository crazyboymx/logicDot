/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.h
 * $Id: GameLayer.h v 1.0 2015-01-27 07:59:45 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-03 11:04:49 $
 * @brief
 *
 ******************************************************************/

#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include <cocos2d.h>
#include <string>
#include "LogicDot.h"
#include "DotNode.h"
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
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


    void initWithConfig(const GameConfig& config, const ColorSpace& cs);
    void initWithPuzzle(Puzzle* puzzle, const ColorSpace& cs);
    void registerWithTouchDispatcher();
private:
    void initDotNodes();
    int inline index(int row, int col) {
        if (mPuzzle == NULL) {
            return 0;
        }
        return row * mPuzzle->size.height + col;
    }

    ColorSpace mCs;
    Puzzle* mPuzzle;
    DotNode** mDotNodeList;
};

#endif // _GAMELAYER_H_
