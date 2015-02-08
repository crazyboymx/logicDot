/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Util.h
 * $Id: Util.h v 1.0 2015-01-23 17:54:27 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-03 10:55:03 $
 * @brief
 *
 ******************************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

#include <cocos2d.h>
#include <string>
#include <sstream>

USING_NS_CC;

struct ColorSpace {
    ccColor4F light;        // main color: light
    ccColor4F normal;       // main color: normal
    ccColor4F dark;         // main color: dark
    ccColor4F dotBg;        // dot background color
    ccColor4F hint;         // hint status color
    ccColor4F hintLight;    // hint status color
    ccColor3B fontColor;    // font color
};

extern const int kTouchPriorityLayer;

extern const char* fontName;

extern const int SmallRadius;
extern const int MiddleRadius;
extern const int LargeRadius;

extern ccColor3B fontColor;
extern ColorSpace Red;
extern ColorSpace Yellow;
extern ColorSpace Gray;
extern ColorSpace Orange;
extern ColorSpace Orange1;
extern ColorSpace Green;
extern ColorSpace Blue;

CCNode* createRectNode(float width, float height, ccColor4F fillColor);
CCNode* createRoundRectNode(float width, float height, float radius, ccColor4F fillColor);
CCNode* createCircleNode(float radius, ccColor4F fillColor);

bool pointInNode(CCNode* node, const CCPoint& worldPoint);

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
}

#endif // _UTIL_H_
