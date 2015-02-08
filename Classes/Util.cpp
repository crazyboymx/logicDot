/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Util.cpp
 * $Id: Util.cpp v 1.0 2015-01-23 18:05:25 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-03 10:54:30 $
 * @brief
 *
 ******************************************************************/

#include "Util.h"
#include <string>
#include <sstream>

USING_NS_CC;

const int kTouchPriorityLayer = -256;

const char* fontName = "Helvetica";

ccColor3B fontColor = ccc3(255, 255, 255);

const int SmallRadius = 10;
const int MiddleRadius = 15;
const int LargeRadius = 20;

ColorSpace Red = {
    ccc4f(0.7, 0.0, 0.0, 0.5),
    ccc4f(0.7 ,0.0, 0.0, 1.0),
    ccc4f(1.0, 0.0, 0.0, 1.0),
    ccc4f(1.0, 1.0, 1.0, 1.0),
    ccc4f(0.6, 0.6, 0.6, 1.0),
    ccc4f(0.8, 0.8, 0.8, 1.0),
    ccc3(255, 0, 0),
};

CCNode* createRectNode(float width, float height, ccColor4F fillColor) {
    CCDrawNode* node = CCDrawNode::create();
    CCPoint plist[4] = {ccp(0, 0), ccp(0, height), ccp(width, height), ccp(width, 0)};
    node->drawPolygon(plist, 4, fillColor, 0, fillColor);
    node->setContentSize(CCSize(width, height));
    return node;
}

CCNode* createRoundRectNode(float width, float height, float radius, ccColor4F fillColor) {
    CCDrawNode* node = CCDrawNode::create();
    node->drawDot(ccp(radius, radius), radius, fillColor);
    node->drawDot(ccp(radius, height - radius), radius, fillColor);
    node->drawDot(ccp(width - radius, height - radius), radius, fillColor);
    node->drawDot(ccp(width - radius, radius), radius, fillColor);
    CCPoint plist1[4] = {ccp(radius, 0), ccp(radius, height), ccp(width - radius, height), ccp(width - radius, 0)};
    node->drawPolygon(plist1, 4, fillColor, 0, fillColor);
    CCPoint plist2[4] = {ccp(0, radius), ccp(0, height - radius), ccp(width, height - radius), ccp(width, radius)};
    node->drawPolygon(plist2, 4, fillColor, 0, fillColor);
    node->setContentSize(CCSize(width, height));
    return node;
}

CCNode* createCircleNode(float radius, ccColor4F fillColor) {
    CCDrawNode* node = CCDrawNode::create();
    node->drawDot(ccp(radius, radius), radius, fillColor);
    node->setContentSize(CCSize(radius*2, radius*2));
    return node;
}

bool pointInNode(CCNode* node, const CCPoint& worldPoint) {
    CCPoint p = worldPoint;
    if (node->getParent()) {
        p = node->getParent()->convertToNodeSpace(worldPoint);
    }
    return node->boundingBox().containsPoint(p);
}
