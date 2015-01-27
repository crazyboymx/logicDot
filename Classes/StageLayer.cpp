/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: StageLayer.cpp
 * $Id: StageLayer.cpp v 1.0 2015-01-27 07:59:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-01-27 11:20:45 $
 * @brief
 *
 ******************************************************************/

#include "Util.h"
#include "StageLayer.h"

USING_NS_CC;

StageLayer::~StageLayer() {
    if (mLevelNodeList) {
        delete[] mLevelNodeList;
        mLevelNodeList = NULL;
    }
}

bool StageLayer::init() {
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }

    mLevelNodeList = NULL;
}

void StageLayer::onEnter() {
    CCLayerColor::onEnter();
}

void StageLayer::onExit() {
    CCLayerColor::onExit();
}

void StageLayer::initWithConfig(const StageConfig& config) {
    mConfig = config;

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCNode* titleBg = createRectNode(visibleSize.width, 100, mConfig.cs.normal);
    CCLabelTTF* titleLabel = CCLabelTTF::create(mConfig.title.c_str(), fontName, 52, titleBg->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    titleLabel->setAnchorPoint(ccp(0, 0));
    titleLabel->setFontFillColor(fontColor);
    titleBg->addChild(titleLabel);
    titleBg->setAnchorPoint(ccp(0, 1));
    titleBg->setPosition(ccp(0, visibleSize.height));
    this->addChild(titleBg);

    initLevel();

    CCNode* menuNorm = createRoundRectNode(visibleSize.width - 20, 100, 20, mConfig.cs.normal);
    CCNode* menuSel = createRoundRectNode(visibleSize.width - 20, 100, 20, mConfig.cs.dark);
    CCLabelTTF* menuLabel = CCLabelTTF::create("Menu", fontName, 52, menuNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    menuLabel->setAnchorPoint(ccp(0.5, 0));
    menuLabel->setFontFillColor(fontColor);
    CCMenuItem* menuItem = CCMenuItemSprite::create(menuNorm, menuSel, NULL, this, menu_selector(StageLayer::menuMenuCallback));
    menuItem->addChild(menuLabel);
    CCMenu* pMenu = CCMenu::create(menuItem, NULL);
    pMenu->setPosition(ccp(visibleSize.width / 2, 140));
    this->addChild(pMenu);
}

void StageLayer::initLevel() {
    int itemLength = 70;
    int gridLength = 80;
    int colCount = 5;
    int rowCount = mConfig.levelCount / 5 + (mConfig.levelCount % 5 == 0 ? 0 : 1);
    CCSize size = CCSize(gridLength * colCount, gridLength * rowCount);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCNode* node = createRoundRectNode(size.width, size.height, 15, mConfig.cs.light);
    node->setAnchorPoint(ccp(0.5, 1));
    node->setPosition(ccp(visibleSize.width / 2, visibleSize.height * 0.75));
    this->addChild(node);
    mLevelNodeList = new LevelNode*[mConfig.levelCount];
    for (int i = 0; i < mConfig.levelCount; i++) {
        mLevelNodeList[i] = LevelNode::create();
        CCNode* normal = createRoundRectNode(itemLength, itemLength, 10, mConfig.cs.normal);
        CCNode* pressed = createRoundRectNode(itemLength, itemLength, 10, mConfig.cs.dark);
        mLevelNodeList[i]->init(i, normal, pressed, CCSize(itemLength, itemLength));
        mLevelNodeList[i]->setAnchorPoint(ccp(0.5, 0.5));
        int row = i / colCount;
        int col = i % colCount;
        mLevelNodeList[i]->setPosition(ccp(col * gridLength + gridLength / 2, size.height - row * gridLength - gridLength / 2));
        node->addChild(mLevelNodeList[i]);
    }
}

void StageLayer::menuMenuCallback(CCObject* pSender) {
    this->removeFromParent();
}
