/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Util.h
 * $Id: Util.h v 1.0 2015-01-23 17:54:27 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-04-16 00:16:56 $
 * @brief
 *
 ******************************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

#include "Data.h"
#include <cocos2d.h>
#include <string>
#include <sstream>
#include <time.h>

USING_NS_CC;

// 双击时间间隔，单位秒
#define DOUBLE_CLICK_THRESHOLD 0.5
// 两个grid之间的间隔
#define GRID_GAP    5

struct ColorSpace {
    ccColor4F bg;           // back ground color
    ccColor4F light;        // main color: light
    ccColor4F normal;       // main color: normal
    ccColor4F dark;         // main color: dark
    ccColor4F hint;         // hint status color
    ccColor4F hintLight;    // hint status color
    ccColor3B fontColor;    // font color
    ccColor4F shapeDark;    // shape dot color: dark
    ccColor4F shapeLight;   // shape dot color: light
    ccColor4F shapeBg;      // shape back ground color
};

extern const int kTouchPriorityLayer;

extern const char* fontName;

extern const float SmallRadius;
extern const float MiddleRadius;
extern const float LargeRadius;

extern ccColor3B fontColor;
extern ColorSpace Red;
extern ColorSpace Yellow;
extern ColorSpace Gray;
extern ColorSpace Orange;
extern ColorSpace Orange1;
extern ColorSpace Green;
extern ColorSpace Blue;

extern ccColor4F menuNormColor;
extern ccColor4F menuSelectedColor;
extern ccColor3B menuNormTextColor;
extern ccColor3B menuSelectedTextColor;

CCNode* createRectNode(float width, float height, ccColor4F fillColor);
CCNode* createRoundRectNode(float width, float height, float radius, ccColor4F fillColor);
CCNode* createCircleNode(float radius, ccColor4F fillColor);

bool pointInNode(CCNode* node, const CCPoint& worldPoint);
float dist(const CCPoint& a, const CCPoint& b);
bool moved(const CCPoint& start, const CCPoint& end);

template<class type>
std::string number2string(type n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}

inline CCSize screenSize() {
    return CCDirector::sharedDirector()->getWinSize();
}

inline CCPoint center() {
    return ccp(screenSize().width / 2, screenSize().height / 2);
}

inline double currentTime() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    CCLOG("tc_sec: %ld, usec: %ld", tv.tv_sec, tv.tv_usec);
    return tv.tv_sec * 1.0 + tv.tv_usec * 1.0 / 1000000;
}

#endif // _UTIL_H_
