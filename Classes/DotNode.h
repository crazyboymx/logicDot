/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: DotNode.h
 * $Id: DotNode.h v 1.0 2015-01-27 09:43:20 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-27 10:00:39 $
 * @brief
 *
 ******************************************************************/

#ifndef _DOTNODE_H_
#define _DOTNODE_H_

#include "LogicDot.h"
#include "Util.h"
#include <cocos2d.h>

USING_NS_CC;

class DotNode : public CCNode {
public:
    CREATE_FUNC(DotNode);
    virtual bool init();
    void init(const ColorSpace& cs, float width, float height, Status status);

    void setStatus(Status status);
private:
    void update();
    void createNodeList(const ColorSpace& cs, float width, float height);
    CCNode* createNode(const ColorSpace& cs, float width, float height, Status status);

    Status mStatus;
    Status mPrevStatus;
    CCNode** mNodeList;
};

#endif // _DOTNODE_H_
