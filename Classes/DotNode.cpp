/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: DotNode.cpp
 * $Id: DotNode.cpp v 1.0 2015-01-27 09:44:14 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-01 18:12:25 $
 * @brief
 *
 ******************************************************************/

#include <sstream>
#include <string>
#include "DotNode.h"
#include "Util.h"

bool DotNode::init() {
    mNodeList = new CCNode*[MAX_STATUS];
    for (int i = UNKNOWN; i < MAX_STATUS; i++) {
        mNodeList[i] = NULL;
    }
    return CCNode::init();
}

void DotNode::init(const ColorSpace& cs, float width, float height, Status status) {
    this->setContentSize(CCSize(width, height));
    CCNode* bg = createRoundRectNode(width, height, 15, cs.dotBg);
    this->addChild(bg);

    createNodeList(cs, width, height);
    update();
}

void DotNode::update() {
    CCNode* prevNode = mNodeList[mPrevStatus];
    CCNode* curNode = mNodeList[mStatus];
    if (prevNode != NULL) {
        prevNode->setVisible(false);
    }
    if (curNode != NULL) {
        curNode->setVisible(true);
    }
}

void DotNode::setStatus(Status status) {
    mPrevStatus = mStatus;
    mStatus = status;
    update();
}

void DotNode::createNodeList(const ColorSpace& cs, float width, float height) {
    for (int i = UNKNOWN; i < MAX_STATUS; i++) {
        mNodeList[i] = createNode(cs, width, height, (Status)i);
        this->addChild(mNodeList[i]);
    }
}

CCNode* DotNode::createNode(const ColorSpace& cs, float width, float height, Status status) {
    CCNode* node = NULL;
    switch (status) {
    case UNKNOWN:
        break;
    case EMPTY:
        break;
    case DOT:
        break;
    case DOT_ALONE:
        break;
    case DOT_LEFT:
        break;
    case DOT_UP:
        break;
    case DOT_RIGHT:
        break;
    case DOT_DOWN:
        break;
    case DOT_LEFT_RIGHT:
        break;
    case DOT_UP_DOWN:
        break;
    case HINT_EMPTY:
        break;
    case HINT_DOT_ALONE:
        break;
    case HINT_DOT_LEFT:
        break;
    case HINT_DOT_UP:
        break;
    case HINT_DOT_RIGHT:
        break;
    case HINT_DOT_DOWN:
        break;
    case HINT_DOT_LEFT_RIGHT:
        break;
    case HINT_DOT_UP_DOWN:
        break;
    default:
        node = NULL;
        break;
    }
    return node;
}
