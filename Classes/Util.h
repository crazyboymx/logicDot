/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Util.h
 * $Id: Util.h v 1.0 2015-01-23 17:54:27 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-27 08:54:39 $
 * @brief
 *
 ******************************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

#include <cocos2d.h>

USING_NS_CC;

struct ColorSpace {
    ccColor4F light;
    ccColor4F normal;
    ccColor4F dark;
};

extern const char* fontName;

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

#endif // _UTIL_H_
