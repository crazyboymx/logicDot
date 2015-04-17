/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: StageLayer.cpp
 * $Id: StageLayer.cpp v 1.0 2015-01-27 07:59:26 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-04-16 10:02:18 $
 * @brief
 *
 ******************************************************************/

#include "Util.h"
#include "StageLayer.h"
#include "GameLayer.h"
#include "MenuLayer.h"
#include "Data.h"

#define SPEED 0.0015625     // 0.5/320
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

    this->setTouchEnabled(true);
    mLevelNodeList = NULL;
    return true;
}

void StageLayer::onEnter() {
    CCLayerColor::onEnter();
}

void StageLayer::onExit() {
    CCLayerColor::onExit();
}

void StageLayer::initWithConfig(const StageConfig& config) {
    mConfig = config;

    CCSize winSize = screenSize();

    CCNode* titleBg = createRectNode(winSize.width, 100, mConfig.cs.normal);
    CCLabelTTF* titleLabel = CCLabelTTF::create(mConfig.title.c_str(), fontName, 52, titleBg->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    titleLabel->setAnchorPoint(ccp(0, 0));
    titleLabel->setFontFillColor(fontColor);
    titleBg->addChild(titleLabel);
    titleBg->setAnchorPoint(ccp(0, 1));
    titleBg->setPosition(ccp(0, winSize.height));
    this->addChild(titleBg);

    initLevel();

    CCNode* menuNorm = createRoundRectNode(winSize.width - 20, 100, LargeRadius, mConfig.cs.normal);
    CCNode* menuSel = createRoundRectNode(winSize.width - 20, 100, LargeRadius, mConfig.cs.dark);
    CCLabelTTF* menuLabel = CCLabelTTF::create("Menu", fontName, 52, menuNorm->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    menuLabel->setAnchorPoint(ccp(0, 0));
    menuLabel->setFontFillColor(fontColor);
    CCMenuItem* menuItem = CCMenuItemSprite::create(menuNorm, menuSel, NULL, this, menu_selector(StageLayer::menuMenuCallback));
    menuItem->addChild(menuLabel);
    CCMenu* pMenu = CCMenu::create(menuItem, NULL);
    pMenu->setPosition(ccp(winSize.width / 2, 120));
    this->addChild(pMenu);
}

void StageLayer::initLevel() {
    int itemLength = 70;
    int gridLength = 80;
    int colCount = 5;
    int rowCount = mConfig.levelCount / 5 + (mConfig.levelCount % 5 == 0 ? 0 : 1);
    CCSize size = CCSize(gridLength * colCount, gridLength * rowCount);
    CCSize winSize = screenSize();

    CCNode* node = createRoundRectNode(size.width, size.height, MiddleRadius, mConfig.cs.light);
    node->setAnchorPoint(ccp(0.5, 1));
    node->setPosition(ccp(winSize.width / 2, winSize.height * 0.75));
    this->addChild(node);
    mLevelNodeList = new LevelNode*[mConfig.levelCount];
    for (int i = 0; i < mConfig.levelCount; i++) {
        mLevelNodeList[i] = LevelNode::create();
        CCNode* normal = createRoundRectNode(itemLength, itemLength, SmallRadius, mConfig.cs.normal);
        CCNode* pressed = createRoundRectNode(itemLength, itemLength, SmallRadius, mConfig.cs.dark);
        mLevelNodeList[i]->init(i, normal, pressed, CCSize(itemLength, itemLength));
        mLevelNodeList[i]->setAnchorPoint(ccp(0.5, 0.5));
        int row = i / colCount;
        int col = i % colCount;
        mLevelNodeList[i]->setPosition(ccp(col * gridLength + gridLength / 2, size.height - row * gridLength - gridLength / 2));
        node->addChild(mLevelNodeList[i]);
    }
}

bool StageLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    mTouchBeginLoc = location;
    for (int i = 0; i < mConfig.levelCount; i++) {
        if (pointInNode(mLevelNodeList[i], location)) {
            return true;
        }
    }
    return false;
}

void StageLayer::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
}

void StageLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();

    if (moved(location, mTouchBeginLoc)) {
        return;
    }

    for (int i = 0; i < mConfig.levelCount; i++) {
        if (pointInNode(mLevelNodeList[i], location)) {
            CCDirector::sharedDirector()->replaceScene(createGameScene(Puzzle::load(puzzleData.stages[playerData.currentStage].puzzles[i]), Red));
            break;
        }
    }
}

void StageLayer::menuMenuCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->replaceScene(createMenuScene());
}

void StageLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kTouchPriorityLayer, false);
}

bool StageTouchLayer::init() {
    if (!CCLayer::init()) {
        return false;
    }
    left = NULL;
    middle = NULL;
    right = NULL;
    this->setTouchEnabled(true);
    return true;
}

bool StageTouchLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    mTouchLastLoc = location;
    mTouchBeginLoc = location;
    return true;
}

void StageTouchLayer::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    if (moved(location, mTouchBeginLoc) == false) {
        return;
    }
    float dx = location.x - mTouchLastLoc.x;
    mTouchLastLoc = location;
    if (dx < 0 && right != NULL || dx > 0 && left != NULL) {
        this->setPositionX(this->getPositionX() + dx);
    }
}

void StageTouchLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    if (moved(location, mTouchBeginLoc) == false) {
        return;
    }

    float x = this->getPositionX();
    float half = screenSize().width / 2;
    CCLOG("x: %0.2f, half:%0.2f, time: %0.2f", x, half, SPEED * (half*2 + x));
    CCAction* callback = CCCallFunc::create(this, callfunc_selector(StageTouchLayer::onMoveEndCallback));
    CCFiniteTimeAction* move = NULL;
    if (x <= -half) {
        move = CCEaseExponentialOut::create(CCMoveTo::create(SPEED * (half*2 + x), ccp(-screenSize().width, 0)));
    }
    else if (x < half) {
        move = CCEaseExponentialOut::create(CCMoveTo::create(SPEED * abs(x), ccp(0, 0)));
    }
    else {
        move = CCEaseExponentialOut::create(CCMoveTo::create(SPEED * (half*2 - x), ccp(screenSize().width, 0)));
    }
    this->runAction(CCSequence::create(move, callback, NULL));
}

void StageTouchLayer::onMoveEndCallback() {
    float x = this->getPositionX();
    float half = screenSize().width / 2;
    if (x < -half) {
        if (left != NULL) {
            left->removeFromParent();
        }
        left = middle;
        middle = right;
        right = NULL;
        playerData.currentStage += 1;
        if (playerData.currentStage < puzzleData.count - 1) {
            right = createStageLayer(puzzleData.stages[playerData.currentStage + 1]);
            this->addChild(right);
        }
    }
    else if (x > half) {
        if (right != NULL) {
            right->removeFromParent();
        }
        right = middle;
        middle = left;
        left = NULL;
        playerData.currentStage -= 1;
        if (playerData.currentStage > 0) {
            left = createStageLayer(puzzleData.stages[playerData.currentStage - 1]);
            this->addChild(left);
        }
    }
    resetStageLayerPosition();
}

void StageTouchLayer::resetStageLayerPosition() {
    this->setPosition(ccp(0, 0));
    if (left != NULL) {
        left->setPosition(ccp(-screenSize().width, 0));
    }
    middle->setPosition(ccp(0, 0));
    if (right != NULL) {
        right->setPosition(ccp(screenSize().width, 0));
    }
}

void StageTouchLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kTouchPriorityLayer, false);
}

StageLayer* createStageLayer(const StageData& sd) {
    std::string title = "";
    title += number2string(sd.puzzleSize) + "X" + number2string(sd.puzzleSize) + " Packer";
    StageConfig config = {sd.count, Red, title};
    StageLayer* sl = StageLayer::create();
    sl->initWithConfig(config);
    return sl;
}

CCScene* createStageScene() {
    CCScene* scene = CCScene::create();
    StageTouchLayer* stl = StageTouchLayer::create();
    scene->addChild(stl);
    StageLayer* ls = createStageLayer(puzzleData.stages[playerData.currentStage]);
    stl->addChild(ls);
    stl->middle = ls;
    if (playerData.currentStage > 0) {
        StageLayer* left = createStageLayer(puzzleData.stages[playerData.currentStage - 1]);
        stl->addChild(left);
        stl->left = left;
    }
    if (playerData.currentStage < puzzleData.count - 1) {
        StageLayer* right = createStageLayer(puzzleData.stages[playerData.currentStage + 1]);
        stl->addChild(right);
        stl->right = right;
    }
    stl->resetStageLayerPosition();
    return scene;
}
