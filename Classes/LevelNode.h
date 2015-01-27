/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: LevelNode.h
 * $Id: LevelNode.h v 1.0 2015-01-27 09:43:20 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-27 10:00:39 $
 * @brief
 *
 ******************************************************************/

#ifndef _LEVELNODE_H_
#define _LEVELNODE_H_

#include <cocos2d.h>

USING_NS_CC;

class LevelNode : public CCNode {
public:
    CREATE_FUNC(LevelNode);
    virtual bool init();

    void init(int level, CCNode* normal, CCNode* pressed, CCSize size);
    void press();
    void unpress();

private:
    void updateState();

    int mLevel;
    CCNode* mNormalNode;
    CCNode* mPressedNode;
    bool mPressed;
};

#endif // _LEVELNODE_H_
