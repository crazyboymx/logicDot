/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Util.cpp
 * $Id: Util.cpp v 1.0 2015-01-23 18:05:25 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-12 16:20:32 $
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

const float SmallRadius = 5;
const float MiddleRadius = 15;
const float LargeRadius = 20;

ColorSpace Red = {
    ccc4f(1.0, 1.0, 1.0, 1.0),
    ccc4f(0.7, 0.0, 0.0, 0.5),
    ccc4f(0.7 ,0.0, 0.0, 1.0),
    ccc4f(1.0, 0.0, 0.0, 1.0),
    ccc4f(0.6, 0.6, 0.6, 0.5),
    ccc4f(0.8, 0.8, 0.8, 1.0),
    ccc3(255, 0, 0),
    ccc4f(1.0, 1.0, 1.0, 1.0),
    ccc4f(1.0, 1.0, 1.0, 0.5),
    ccc4f(0.5, 0.0, 0.0, 0.5),
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

    int segments = 10;
    //算出1/4圆
    const float coef    = 0.5f * (float)M_PI / segments;
    CCPoint* vertices    = new CCPoint[segments + 1];
    CCPoint* thisVertices = vertices;
    for(unsigned int i = 0; i <= segments; ++i, ++thisVertices) {
        float rads = (segments - i) * coef;
        thisVertices->x = radius * sinf(rads);
        thisVertices->y = radius * cosf(rads);
    }

    CCPoint tagCenter;
    float minX = 0;
    float maxX = width;
    float minY = 0;
    float maxY = height;

    unsigned int dwPolygonPtMax = (segments + 1) * 4;
    CCPoint* pPolygonPtArr = new CCPoint[dwPolygonPtMax];
    CCPoint* thisPolygonPt = pPolygonPtArr;
    int aa = 0;
    //左上角
    tagCenter.x = minX + radius;
    tagCenter.y = maxY - radius;
    thisVertices = vertices;
    for(unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, ++thisVertices) {
        thisPolygonPt->x = tagCenter.x - thisVertices->x;
        thisPolygonPt->y = tagCenter.y + thisVertices->y;
        ++aa;
    }
    //右上角
    tagCenter.x = maxX - radius;
    tagCenter.y = maxY - radius;
    thisVertices = vertices + segments;
    for(unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, --thisVertices) {
        thisPolygonPt->x = tagCenter.x + thisVertices->x;
        thisPolygonPt->y = tagCenter.y + thisVertices->y;
        ++aa;
    }
    //右下角
    tagCenter.x = maxX - radius;
    tagCenter.y = minY + radius;
    thisVertices = vertices;
    for(unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, ++thisVertices) {
        thisPolygonPt->x    = tagCenter.x + thisVertices->x;
        thisPolygonPt->y    = tagCenter.y - thisVertices->y;
        ++aa;
    }
    //左下角
    tagCenter.x = minX + radius;
    tagCenter.y = minY + radius;
    thisVertices = vertices + segments;
    for(unsigned int i = 0; i <= segments; ++i, ++thisPolygonPt, --thisVertices) {
        thisPolygonPt->x    = tagCenter.x - thisVertices->x;
        thisPolygonPt->y    = tagCenter.y - thisVertices->y;
        ++aa;
    }

    node->drawPolygon(pPolygonPtArr, dwPolygonPtMax, fillColor, 0, fillColor);
    node->setContentSize(CCSize(width, height));

    CC_SAFE_DELETE_ARRAY(vertices);
    CC_SAFE_DELETE_ARRAY(pPolygonPtArr);
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
