/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: LevelNode.cpp
 * $Id: LevelNode.cpp v 1.0 2015-01-27 09:44:14 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-27 11:21:09 $
 * @brief
 *
 ******************************************************************/

#include <sstream>
#include <string>
#include "LevelNode.h"
#include "Util.h"

bool LevelNode::init() {
    mPressed = false;
    return CCNode::init();
}

void LevelNode::init(int level, CCNode* normal, CCNode* pressed, CCSize size) {
    mLevel = level;
    mNormalNode = normal;
    mPressedNode = pressed;
    this->setContentSize(size);
    mNormalNode->setAnchorPoint(ccp(0.5, 0.5));
    mNormalNode->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(mNormalNode);
    mPressedNode->setAnchorPoint(ccp(0.5, 0.5));
    mPressedNode->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(mPressedNode);

    std::stringstream ss;
    ss << (mLevel + 1);
    CCLabelTTF* levelLabel = CCLabelTTF::create(ss.str().c_str(), fontName, 32, size, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    levelLabel->setAnchorPoint(ccp(0, 0));
    levelLabel->setPosition(ccp(0, 0));
    this->addChild(levelLabel);

    this->updateState();
}

void LevelNode::press() {
    mPressed = true;
    updateState();
}

void LevelNode::unpress() {
    mPressed = false;
    updateState();
}

void LevelNode::updateState() {
    mNormalNode->setVisible(!mPressed);
    mPressedNode->setVisible(mPressed);
}
