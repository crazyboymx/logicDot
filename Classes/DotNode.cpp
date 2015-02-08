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
    mPrevStatus = UNKNOWN;
    mStatus = UNKNOWN;
    mFlag = 0;
    return CCNode::init();
}

void DotNode::init(const ColorSpace& cs, float width, float height, Status status) {
    mStatus = status;
    this->setContentSize(CCSize(width, height));
    CCNode* bg = createRoundRectNode(width, height, MiddleRadius, cs.bg);
    this->addChild(bg);

    createNodeMap(cs, width, height);
    update();
}

void DotNode::update() {
    CCNode* prevNode = mNodeMap[mPrevStatus];
    CCNode* curNode = mNodeMap[mStatus];
    prevNode->setVisible(false);
    curNode->setVisible(true);
    mNodeMap[LEFT]->setVisible(LEFT & mFlag);
    mNodeMap[UP]->setVisible(UP & mFlag);
    mNodeMap[RIGHT]->setVisible(RIGHT & mFlag);
    mNodeMap[DOWN]->setVisible(DOWN & mFlag);
    mNodeMap[HINT_LEFT]->setVisible(HINT_LEFT & mFlag);
    mNodeMap[HINT_UP]->setVisible(HINT_UP & mFlag);
    mNodeMap[HINT_RIGHT]->setVisible(HINT_RIGHT & mFlag);
    mNodeMap[HINT_DOWN]->setVisible(HINT_DOWN & mFlag);
    if (mStatus != mPrevStatus) {
        showStatusChangeAnimation();
    }
}

void DotNode::setStatus(Status status, int flag) {
    if (mStatus == status && mFlag == flag) {
        return;
    }
    mPrevStatus = mStatus;
    mStatus = status;
    mFlag = flag;
    update();
}

void DotNode::createNodeMap(const ColorSpace& cs, float width, float height) {
    float dotRadius = width / 4;
    mNodeMap[UNKNOWN] = createStatusNode(cs, width, height, dotRadius, UNKNOWN);
    mNodeMap[EMPTY] = createStatusNode(cs, width, height, dotRadius, EMPTY);
    mNodeMap[DOT] = createStatusNode(cs, width, height, dotRadius, DOT);
    mNodeMap[HINT_EMPTY] = createStatusNode(cs, width, height, dotRadius, HINT_EMPTY);
    mNodeMap[HINT_DOT] = createStatusNode(cs, width, height,dotRadius, HINT_DOT);
    std::map<int, CCNode*>::iterator iter = mNodeMap.begin();
    for (; iter != mNodeMap.end(); ++iter) {
        iter->second->setAnchorPoint(ccp(0.5, 0.5));
        iter->second->setPosition(ccp(width / 2, height / 2));
        this->addChild(iter->second);
    }
    // left flag
    CCNode* node = createRectNode(width / 2 + GRID_GAP / 2, dotRadius*2, cs.light);
    node->setAnchorPoint(ccp(1, 0.5));
    node->setPosition(ccp(width / 2-1, height / 2));
    node->setVisible(false);
    this->addChild(node);
    mNodeMap[LEFT] = node;
    // hint left flag
    node = createRectNode(width / 2 + GRID_GAP / 2, dotRadius*2, cs.hintLight);
    node->setAnchorPoint(ccp(1, 0.5));
    node->setPosition(ccp(width / 2-1, height / 2));
    node->setVisible(false);
    this->addChild(node);
    mNodeMap[HINT_LEFT] = node;

    // up flag
    node = createRectNode(dotRadius*2, height / 2 + GRID_GAP / 2, cs.light);
    node->setAnchorPoint(ccp(0.5, 0));
    node->setPosition(ccp(width / 2, height / 2+1));
    node->setVisible(false);
    this->addChild(node);
    mNodeMap[UP] = node;
    // hint up flag
    node = createRectNode(dotRadius*2, height / 2 + GRID_GAP / 2, cs.hintLight);
    node->setAnchorPoint(ccp(0.5, 0));
    node->setPosition(ccp(width / 2, height / 2+1));
    node->setVisible(false);
    this->addChild(node);
    mNodeMap[HINT_UP] = node;

    // right flag
    node = createRectNode(width / 2 + GRID_GAP / 2, dotRadius*2, cs.light);
    node->setAnchorPoint(ccp(0, 0.5));
    node->setPosition(ccp(width / 2, height / 2));
    node->setVisible(false);
    this->addChild(node);
    mNodeMap[RIGHT] = node;
    // hint right flag
    node = createRectNode(width / 2 + GRID_GAP / 2, dotRadius*2, cs.hintLight);
    node->setAnchorPoint(ccp(0, 0.5));
    node->setPosition(ccp(width / 2, height / 2));
    node->setVisible(false);
    this->addChild(node);
    mNodeMap[HINT_RIGHT] = node;

    // down flag
    node = createRectNode(dotRadius*2, height / 2 + GRID_GAP / 2, cs.light);
    node->setAnchorPoint(ccp(0.5, 1));
    node->setPosition(ccp(width / 2, height / 2));
    node->setVisible(false);
    this->addChild(node);
    mNodeMap[DOWN] = node;
    // hint down flag
    node = createRectNode(dotRadius*2, height / 2 + GRID_GAP / 2, cs.hintLight);
    node->setAnchorPoint(ccp(0.5, 1));
    node->setPosition(ccp(width / 2, height / 2));
    node->setVisible(false);
    this->addChild(node);
    mNodeMap[HINT_DOWN] = node;
}

CCNode* DotNode::createStatusNode(const ColorSpace& cs, float width, float height, float dotRadius, Status status) {
    CCNode* node = NULL;
    switch (status) {
    case UNKNOWN:
        node = createRoundRectNode(width, height, MiddleRadius, cs.bg);
        break;
    case EMPTY:
        node = createRoundRectNode(width, height, MiddleRadius, cs.light);
        break;
    case DOT:
        node = createCircleNode(dotRadius, cs.normal);
        break;
    case HINT_EMPTY:
        node = createRoundRectNode(width, height, MiddleRadius, cs.hint);
        break;
    case HINT_DOT:
        node = createCircleNode(dotRadius, cs.hint);
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

void DotNode::showStatusChangeAnimation() {

}