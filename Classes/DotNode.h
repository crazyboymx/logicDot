/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: DotNode.h
 * $Id: DotNode.h v 1.0 2015-01-27 09:43:20 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-02 11:29:15 $
 * @brief
 *
 ******************************************************************/

#ifndef _DOTNODE_H_
#define _DOTNODE_H_

#include "LogicDot.h"
#include "Util.h"
#include <cocos2d.h>
#include <map>

USING_NS_CC;

class DotNode : public CCNode {
public:
    CREATE_FUNC(DotNode);
    virtual bool init();
    void init(const ColorSpace& cs, float width, float height, Status status);

    void setStatus(Status status, int flag);
private:
    void update();
    void createNodeMap(const ColorSpace& cs, float width, float height);
    CCNode* createStatusNode(const ColorSpace& cs, float width, float height, float dotRadius, Status status);

    void showStatusChangeAnimation();
    Status mStatus;
    Status mPrevStatus;
    int mFlag;
    std::map<int, CCNode*> mNodeMap;
};

#endif // _DOTNODE_H_
