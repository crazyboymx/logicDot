/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: Util.h
 * $Id: Util.h v 1.0 2015-01-23 17:54:27 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-23 18:23:32 $
 * @brief
 *
 ******************************************************************/

#include <cocos2d.h>

USING_NS_CC;

CCNode* createRectNode(float width, float height, ccColor4F fillColor);
CCNode* createRoundRectNode(float width, float height, float radius, ccColor4F fillColor);
CCNode* createCircleNode(float radius, ccColor4F fillColor);
