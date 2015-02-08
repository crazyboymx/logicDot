/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: DotNode.cpp
 * $Id: DotNode.cpp v 1.0 2015-01-27 09:44:14 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-02-03 09:47:03 $
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
    CCNode* bg = createRoundRectNode(width, height, MiddleRadius, cs.dotBg);
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
        if (mNodeList[i] != NULL) {
            mNodeList[i]->setAnchorPoint(ccp(0.5, 0.5));
            mNodeList[i]->setPosition(ccp(width / 2, height / 2));
            this->addChild(mNodeList[i]);
        }
    }
}

CCNode* DotNode::createNode(const ColorSpace& cs, float width, float height, Status status) {
    CCNode* node = NULL;
    CCNode* child = NULL;
    float dotRadius = width / 4;
    switch (status) {
    case UNKNOWN:
        node = NULL;
        break;
    case EMPTY:
        node = NULL;
        break;
    case DOT:
        node = createCircleNode(dotRadius, cs.normal);
        break;
    case DOT_ALONE:
        node = createCircleNode(dotRadius, cs.normal);
        break;
    case DOT_LEFT:
        node = createCircleNode(dotRadius, cs.normal);
        child = createRectNode(width / 2, dotRadius*2, cs.light);
        child->setAnchorPoint(ccp(1, 0.5));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case DOT_UP:
        node = createCircleNode(dotRadius, cs.normal);
        child = createRectNode(dotRadius*2, height / 2, cs.light);
        child->setAnchorPoint(ccp(0.5, 0));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case DOT_RIGHT:
        node = createCircleNode(dotRadius, cs.normal);
        child = createRectNode(width / 2, dotRadius*2, cs.light);
        child->setAnchorPoint(ccp(0, 0.5));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case DOT_DOWN:
        node = createCircleNode(dotRadius, cs.normal);
        child = createRectNode(dotRadius*2, height / 2, cs.light);
        child->setAnchorPoint(ccp(0.5, 1));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case DOT_LEFT_RIGHT:
        node = createCircleNode(dotRadius, cs.normal);
        child = createRectNode(width, dotRadius*2, cs.light);
        child->setAnchorPoint(ccp(0.5, 0.5));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case DOT_UP_DOWN:
        node = createCircleNode(dotRadius, cs.normal);
        child = createRectNode(dotRadius*2, height, cs.light);
        child->setAnchorPoint(ccp(0.5, 0.5));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case HINT_EMPTY:
        node = createRoundRectNode(width, height, MiddleRadius, cs.hint);
        break;
    case HINT_DOT_ALONE:
        node = createCircleNode(dotRadius, cs.hint);
        break;
    case HINT_DOT_LEFT:
        node = createCircleNode(dotRadius, cs.hint);
        child = createRectNode(width / 2, dotRadius*2, cs.hintLight);
        child->setAnchorPoint(ccp(1, 0.5));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case HINT_DOT_UP:
        node = createCircleNode(dotRadius, cs.hint);
        child = createRectNode(dotRadius*2, height / 2, cs.hintLight);
        child->setAnchorPoint(ccp(0.5, 0));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case HINT_DOT_RIGHT:
        node = createCircleNode(dotRadius, cs.hint);
        child = createRectNode(width / 2, dotRadius*2, cs.hintLight);
        child->setAnchorPoint(ccp(0, 0.5));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case HINT_DOT_DOWN:
        node = createCircleNode(dotRadius, cs.hint);
        child = createRectNode(dotRadius*2, height / 2, cs.hintLight);
        child->setAnchorPoint(ccp(0.5, 1));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case HINT_DOT_LEFT_RIGHT:
        node = createCircleNode(dotRadius, cs.hint);
        child = createRectNode(width, dotRadius*2, cs.hintLight);
        child->setAnchorPoint(ccp(0.5, 0.5));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    case HINT_DOT_UP_DOWN:
        node = createCircleNode(dotRadius, cs.hint);
        child = createRectNode(dotRadius*2, height, cs.hintLight);
        child->setAnchorPoint(ccp(0.5, 0.5));
        child->setPosition(ccp(dotRadius, dotRadius));
        node->addChild(child);
        break;
    default:
        node = NULL;
        break;
    }
    if (node != NULL) {
        node->setVisible(false);
    }
    return node;
}
