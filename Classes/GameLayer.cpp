/* vim: set expandtab tabstop=4 shiftwidth=4 foldmethod=marker:   */

/*******************************************************************
 * @File: GameLayer.cpp
 * $Id: GameLayer.cpp v 1.0 2015-01-27 07:59:49 maxing $
 * $Author: maxing <xm.crazyboy@gmail.com> $
 * $Last modified: 2015-04-16 09:44:04 $
 * @brief
 *
 ******************************************************************/

#include "GameLayer.h"
#include "Util.h"
#include "WinLayer.h"

USING_NS_CC;

#define MAP_INDEX(i, j) ((i) * 100 + (j))

GameLayer::~GameLayer() {
    if (mPuzzle != NULL) {
        delete mPuzzle;
    }
}

bool GameLayer::init() {
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }
    this->setTouchEnabled(true);
    mPuzzle = NULL;
    mBoard = NULL;
    mStatusInDrag = UNKNOWN;
    mLastTouchTime = 0;
    mLastTouchIndex = -1;
    return true;
}

void GameLayer::onEnter() {
    CCLayerColor::onEnter();
}

void GameLayer::onExit() {
    CCLayerColor::onExit();
}

void GameLayer::initWithConfig(const GameConfig& config, const ColorSpace& cs) {
    Puzzle* puzzle = Puzzle::load(config.puzzle);
    initWithPuzzle(puzzle, cs);
}

void GameLayer::initWithPuzzle(Puzzle* puzzle, const ColorSpace& cs) {
    this->removeAllChildren();
    mPuzzle = puzzle;
    mCs = cs;
    initTitle();
    initShapes();
    initDotNodes();
    initMenus();
    updateDotStatus();
    puzzle->print();
    updateStatus();
    this->setTouchEnabled(true);
}

void GameLayer::initTitle() {
    mTitleBg = createRectNode(screenSize().width, 36, mCs.dark);
    mTitleBg->setAnchorPoint(ccp(0, 1));
    mTitleBg->setPosition(ccp(0, screenSize().height));
    this->addChild(mTitleBg);

    CCSize halfSize = CCSize(mTitleBg->getContentSize().width / 2, mTitleBg->getContentSize().height);
    std::string titleString = "" + number2string(mPuzzle->size.width) + "x" + number2string(mPuzzle->size.height) + "    ";
    CCLabelTTF* title = CCLabelTTF::create(titleString.c_str(), fontName, 32, halfSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    title->setAnchorPoint(ccp(0, 0));
    title->setPosition(ccp(0, 0));
    mTitleBg->addChild(title);

    std::string scoreString = "    Score: " + number2string(0);
    mScoreLabel = CCLabelTTF::create(scoreString.c_str(), fontName, 32, halfSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
    mScoreLabel->setAnchorPoint(ccp(0, 0));
    mScoreLabel->setPosition((ccp(halfSize.width, 0)));
    mTitleBg->addChild(mScoreLabel);
}

void GameLayer::initShapes() {
    float shapeBgHeight = 100.0f;
    float shapeRowCount = 3;
    float padding = 5;
    float shapeRowHeight = (shapeBgHeight - padding * 2) / shapeRowCount;
    float shapeDotSize = shapeRowHeight * 0.75;
    if (mPuzzle->size.width > 10) {
        shapeDotSize *= 0.75;
    }
    float shapeBgPosY = mTitleBg->getPositionY() - mTitleBg->getContentSize().height * mTitleBg->getAnchorPoint().y;
    mShapesBg = createRectNode(screenSize().width, shapeBgHeight, mCs.shapeBg);
    mShapesBg->setAnchorPoint(ccp(0, 1));
    mShapesBg->setPosition(ccp(0, shapeBgPosY));
    this->addChild(mShapesBg);

    float rowPosY[3] = { shapeRowHeight * 2.5, shapeRowHeight * 1.5, shapeRowHeight * 0.5 };
    int row = 0;
    float posX = 20.0;
    float nextPosX = posX;
    for (int i = mPuzzle->solution.shapes.size() - 1; i >= 0; -- i) {
        for (int j = 0; j < mPuzzle->solution.shapes[i]; ++ j) {
            CCNode* shape = createShape(i, shapeDotSize, mCs.shapeDark, mCs.shapeLight);
            shape->setAnchorPoint(ccp(0.0, 0.5));
            shape->setPosition(ccp(posX, rowPosY[row]));
            mShapesBg->addChild(shape);
            mShapesList[MAP_INDEX(i, j)] = shape;
            CCNode* matchedShape = createShape(i, shapeDotSize, mCs.normal, mCs.light);
            matchedShape->setAnchorPoint(ccp(0.0, 0.5));
            matchedShape->setPosition(ccp(posX, rowPosY[row]));
            mMatchedShapesList[MAP_INDEX(i, j)] = matchedShape;
            CCLOG("create shape: %d, pos %0.2f, %0.2f", i, posX, rowPosY[row]);
            mShapesBg->addChild(matchedShape);
            if (row == 0) {
                nextPosX = posX + shape->getContentSize().width;
            }
            row = (row + 1) % 3;
            if (row == 0) {
                posX = nextPosX;
            }
        }
    }
}

void GameLayer::initDotNodes() {
    if (mPuzzle == NULL) {
        return;
    }
    Size size = mPuzzle->size;
    CCSize winSize = screenSize();
    float gridBoarder = 10;
    float labelSize = 60;
    CCSize gridSize = CCSize(winSize.width - labelSize * 2, winSize.width - labelSize * 2);
    float gridLength = (gridSize.width - gridBoarder * 2) / size.width;
    float dotNodeLength = gridLength - GRID_GAP;
    mBoard = createRoundRectNode(gridSize.width, gridSize.height, MiddleRadius, mCs.normal);
    mBoard->setAnchorPoint(ccp(0.5, 0));
    mBoard->setPosition(ccp(winSize.width / 2, mShapesBg->getPositionY() - mShapesBg->getContentSize().height * mShapesBg->getAnchorPoint().y - gridSize.height - labelSize - 50));
    this->addChild(mBoard);
    CCLabelTTF* lt = CCLabelTTF::create("0", fontName, 32);
    this->addChild(lt);
    for (int row = 0; row < mPuzzle->row.size(); row++) {
        CCLabelTTF* label = CCLabelTTF::create(number2string(mPuzzle->row[row]).c_str(), fontName, 32);
        label->setAnchorPoint(ccp(0.5, 0.5));
        label->setPosition(ccp(- labelSize / 2, gridLength * row + gridLength / 2 + gridBoarder));
        label->setFontFillColor(mCs.fontColor);
        mBoard->addChild(label);
        mRowLabelList[row] = label;
    }
    for (int col = 0; col < mPuzzle->size.width; col++) {
        CCLabelTTF* label = CCLabelTTF::create(number2string(mPuzzle->column[col]).c_str(), fontName, 32);
        label->setAnchorPoint(ccp(0.5, 0.5));
        label->setPosition(ccp(gridLength * col + gridLength / 2 + gridBoarder, gridSize.height + labelSize / 2));
        label->setFontFillColor(mCs.fontColor);
        mBoard->addChild(label);
        mColLabelList[col] = label;
    }
    for (int row = 0; row < mPuzzle->size.height; row++) {
        for (int col = 0; col < mPuzzle->size.width; col++) {
            int idx = index(row, col);
            mDotNodeList.push_back(DotNode::create());
            mDotNodeList[idx]->init(mCs, dotNodeLength, dotNodeLength, mPuzzle->cells[row][col].status);
            mDotNodeList[idx]->setAnchorPoint(ccp(0.5, 0.5));
            mDotNodeList[idx]->setPosition(ccp(gridLength * col + gridLength / 2 + gridBoarder, gridLength * row + gridLength / 2 + gridBoarder));
            mBoard->addChild(mDotNodeList[idx]);
        }
    }
}

void GameLayer::initMenus() {
    CCSize winSize = screenSize();
    float menuHeight = 64.0f;
    float menuWidth = winSize.width / 5;
    ccColor4F normColor = ccc4f(0.15, 0.15, 0.15, 1.0);
    ccColor4F selColor = ccc4f(0.35, 0.35, 0.35, 1.0);

    CCNode* norm = createRectNode(menuWidth, menuHeight, normColor);
    CCNode* sel = createRectNode(menuWidth, menuHeight, selColor);
    CCSprite* normSprite = CCSprite::create("1.png");
    CCSprite* selSprite = CCSprite::create("1.png");
    normSprite->setPosition(ccp(norm->getContentSize().width * 0.5, norm->getContentSize().height * 0.5));
    selSprite->setPosition(ccp(sel->getContentSize().width * 0.5, sel->getContentSize().height * 0.5));
    norm->addChild(normSprite);
    sel->addChild(selSprite);
    mPush = CCMenuItemSprite::create(norm, sel, NULL, this, menu_selector(GameLayer::menuPushCallback));
    mPush->setAnchorPoint(ccp(0.5, 0));
    mPush->setPosition(ccp(menuWidth * -2, 0));

    norm = createRectNode(menuWidth, menuHeight, normColor);
    sel = createRectNode(menuWidth, menuHeight, selColor);
    normSprite = CCSprite::create("2.png");
    selSprite = CCSprite::create("2.png");
    normSprite->setPosition(ccp(norm->getContentSize().width * 0.5, norm->getContentSize().height * 0.5));
    selSprite->setPosition(ccp(sel->getContentSize().width * 0.5, sel->getContentSize().height * 0.5));
    norm->addChild(normSprite);
    sel->addChild(selSprite);
    mPop = CCMenuItemSprite::create(norm, sel, NULL, this, menu_selector(GameLayer::menuPopCallback));
    mPop->setAnchorPoint(ccp(0.5, 0));
    mPop->setPosition(ccp(menuWidth * -1, 0));

    norm = createRectNode(menuWidth, menuHeight, normColor);
    sel = createRectNode(menuWidth, menuHeight, selColor);
    normSprite = CCSprite::create("3.png");
    selSprite = CCSprite::create("3.png");
    normSprite->setPosition(ccp(norm->getContentSize().width * 0.5, norm->getContentSize().height * 0.5));
    selSprite->setPosition(ccp(sel->getContentSize().width * 0.5, sel->getContentSize().height * 0.5));
    norm->addChild(normSprite);
    sel->addChild(selSprite);
    mRank = CCMenuItemSprite::create(norm, sel, NULL, this, menu_selector(GameLayer::menuRankCallback));
    mRank->setAnchorPoint(ccp(0.5, 0));
    mRank->setPosition(ccp(menuWidth * 0, 0));

    norm = createRectNode(menuWidth, menuHeight, normColor);
    sel = createRectNode(menuWidth, menuHeight, selColor);
    normSprite = CCSprite::create("4.png");
    selSprite = CCSprite::create("4.png");
    normSprite->setPosition(ccp(norm->getContentSize().width * 0.5, norm->getContentSize().height * 0.5));
    selSprite->setPosition(ccp(sel->getContentSize().width * 0.5, sel->getContentSize().height * 0.5));
    norm->addChild(normSprite);
    sel->addChild(selSprite);
    mHint = CCMenuItemSprite::create(norm, sel, NULL, this, menu_selector(GameLayer::menuHintCallback));
    mHint->setAnchorPoint(ccp(0.5, 0));
    mHint->setPosition(ccp(menuWidth * 1, 0));

    norm = createRectNode(menuWidth, menuHeight, normColor);
    sel = createRectNode(menuWidth, menuHeight, selColor);
    normSprite = CCSprite::create("5.png");
    selSprite = CCSprite::create("5.png");
    normSprite->setPosition(ccp(norm->getContentSize().width * 0.5, norm->getContentSize().height * 0.5));
    selSprite->setPosition(ccp(sel->getContentSize().width * 0.5, sel->getContentSize().height * 0.5));
    norm->addChild(normSprite);
    sel->addChild(selSprite);
    mRestart = CCMenuItemSprite::create(norm, sel, NULL, this, menu_selector(GameLayer::menuRestartCallback));
    mRestart->setAnchorPoint(ccp(0.5, 0));
    mRestart->setPosition(ccp(menuWidth * 2, 0));

    CCMenu* pMenu = CCMenu::create(mPush, mPop, mRank, mHint, mRestart, NULL);
    pMenu->setPosition(ccp(winSize.width * 0.5, 0));
    this->addChild(pMenu);

    /*norm = createRectNode(menuWidth, menuHeight, normColor);
    sel = createRectNode(menuWidth, menuHeight, selColor);
    normSprite = CCSprite::create("menu.png");
    selSprite = CCSprite::create("menu.png");
    norm->addChild(normSprite);
    sel->addChild(selSprite);
    mPush = CCMenuItemSprite::create(norm, sel, NULL, this, menu_selector(GameLayer::menuPushCallback));
    mPush->setAnchorPoint(ccp(0.5, 0.5));
    mPush->setPosition(ccp(menuWidth * 2, menuHeight * 0.5));*/
}

CCNode* GameLayer::createShape(int dotCount, float dotSize, ccColor4F dark, ccColor4F light) {
    CCNode* node = CCNode::create();
    node->setContentSize(CCSize(dotSize * (3 * dotCount + 1) / 2, dotSize));
    float radius = dotSize * 0.5;
    for (int i = 0; i < dotCount; ++ i) {
        CCNode* dot = createCircleNode(radius, dark);
        dot->setAnchorPoint(ccp(0.5, 0.5));
        dot->setPosition(ccp(radius * 2 + i * radius * 3, radius));
        node->addChild(dot);
    }
    for (int i = 0; i < dotCount - 1; ++ i) {
        CCNode* link = createRectNode(radius * 3, radius * 2, light);
        link->setAnchorPoint(ccp(0, 0.5));
        link->setPosition(ccp(radius * 2 + radius * i * 3, radius));
        node->addChild(link);
    }
    return node;
}

void GameLayer::winGame() {
    this->setTouchEnabled(false);
    WinLayer* wl = WinLayer::create();
    CCLOG("winGame");
    this->addChild(wl);
    nextLevel();
}

void GameLayer::updateStatus() {
    updateLabels();
    updateShapes();
    if (mPuzzle->isWin()) {
        winGame();
    }
}

void GameLayer::updateLabels() {
    for (int i = 0; i < mPuzzle->row.size(); i++) {
        mRowLabelList[i]->setString(number2string(mPuzzle->row[i]).c_str());
    }
    for (int i = 0; i < mPuzzle->column.size(); i++) {
        mColLabelList[i]->setString(number2string(mPuzzle->column[i]).c_str());
    }
}

void GameLayer::updateShapes() {
    std::map<int, CCNode*>::iterator iter = mShapesList.begin();
    for (; iter != mShapesList.end(); ++ iter) {
        iter->second->setVisible(true);
        mMatchedShapesList[iter->first]->setVisible(false);
    }
    for (int i = mPuzzle->shapes.size() - 1; i >= 0; -- i) {
        for (int j = 0; j < mPuzzle->shapes[i]; ++ j) {
            int idx = MAP_INDEX(i, j);
            if (mMatchedShapesList.find(idx) == mMatchedShapesList.end()) {
                continue;
            }
            mMatchedShapesList[MAP_INDEX(i, j)]->setVisible(true);
            mShapesList[MAP_INDEX(i, j)]->setVisible(false);
        }
    }
}

bool GameLayer::setDotStatus(int row, int col, Status status) {
    mPuzzle->setStatus(row, col, status);
    updateDotStatus(row, col);
    return status == mPuzzle->cells[row][col].status;
}

void GameLayer::updateDotStatus(int row, int col) {
    mDotNodeList[index(row, col)]->setStatus(mPuzzle->cells[row][col].status, mPuzzle->cells[row][col].flag);
    if (col - 1 >= 0) {
        mDotNodeList[index(row, col - 1)]->setStatus(mPuzzle->cells[row][col - 1].status, mPuzzle->cells[row][col - 1].flag);
    }
    if (row + 1 < mPuzzle->row.size()) {
        mDotNodeList[index(row + 1, col)]->setStatus(mPuzzle->cells[row + 1][col].status, mPuzzle->cells[row + 1][col].flag);
    }
    if (col + 1 < mPuzzle->column.size()) {
        mDotNodeList[index(row, col + 1)]->setStatus(mPuzzle->cells[row][col + 1].status, mPuzzle->cells[row][col + 1].flag);
    }
    if (row - 1 >= 0) {
        mDotNodeList[index(row - 1, col)]->setStatus(mPuzzle->cells[row - 1][col].status, mPuzzle->cells[row - 1][col].flag);
    }
}

void GameLayer::updateDotStatus() {
    for (int i = 0; i < mPuzzle->row.size(); i++) {
        for (int j = 0; j < mPuzzle->column.size(); j++) {
            updateDotStatus(i, j);
        }
    }
}

void GameLayer::touchOnBoard(int row, int col) {
    Status status = mPuzzle->cells[row][col].status;
    if (status == UNKNOWN) {
        setDotStatus(row, col, EMPTY);
    }
    else {
        setDotStatus(row, col, UNKNOWN);
    }
    updateStatus();
}

void GameLayer::doubleTouchOnBoard(int row, int col) {
    if (mPuzzle->canPutDot(row, col) == false) {
        return;
    }
    setDotStatus(row, col, DOT);
    updateStatus();
}

bool GameLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    if (pointInNode(mBoard, location) == false) {
        return false;
    }
    for (int row = 0; row < mPuzzle->size.height; row++) {
        for (int col = 0; col < mPuzzle->size.width; col++) {
            int idx = index(row, col);
            if (pointInNode(mDotNodeList[idx], location) == false) {
                continue;
            }
            if (isHint(mPuzzle->cells[row][col].status)) {
                return false;
            }
            double touchTime = currentTime();
            if ((touchTime - mLastTouchTime) < DOUBLE_CLICK_THRESHOLD) {
                doubleTouchOnBoard(row, col);
                mLastTouchTime = 0;
                mStatusInDrag = mPuzzle->cells[row][col].status;
            }
            else {
                mLastTouchTime = touchTime;
                touchOnBoard(row, col);
                mStatusInDrag = mPuzzle->cells[row][col].status;
            }
            mLastTouchIndex = idx;
            return true;
        }
    }

    return false;
}

void GameLayer::ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CCPoint location = touch->getLocation();
    if (pointInNode(mBoard, location) == false) {
        return;
    }
    for (int row = 0; row < mPuzzle->size.height; row++) {
        for (int col = 0; col < mPuzzle->size.width; col++) {
            int idx = index(row, col);
            if (pointInNode(mDotNodeList[idx], location) == false) {
                continue;
            }
            if (isHint(mPuzzle->cells[row][col].status)) {
                return;
            }
            if (mLastTouchIndex != idx) {
                mLastTouchIndex = idx;
                if (mStatusInDrag == DOT && mPuzzle->canPutDot(row, col) == false) {
                    return;
                }
                setDotStatus(row, col, mStatusInDrag);
                updateStatus();
            }
            return;
        }
    }
}

void GameLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
    mLastTouchIndex = -1;
    //CCPoint location = touch->getLocation();
    //this->removeFromParent();
}

void GameLayer::menuPushCallback(CCObject* pSender) {
}

void GameLayer::menuPopCallback(CCObject* pSender) {
}

void GameLayer::menuRankCallback(CCObject* pSender) {
}

void GameLayer::menuHintCallback(CCObject* pSender) {
}

void GameLayer::menuRestartCallback(CCObject* pSender) {
}

void GameLayer::menuPauseCallback(CCObject* pSender) {
}

void GameLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kTouchPriorityLayer, true);
}

CCScene* createGameScene(Puzzle* puzzle, const ColorSpace& cs) {
    CCScene *pScene = CCScene::create();
    GameLayer* gl = GameLayer::create();
    gl->initWithPuzzle(puzzle, cs);
    pScene->addChild(gl);
    return pScene;
}
