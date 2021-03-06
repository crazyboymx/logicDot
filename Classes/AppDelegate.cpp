#include "AppDelegate.h"
#include "MenuLayer.h"
#include "GameLayer.h"
#include "Data.h"
#include <vector>
#include <algorithm>
#include <ctime>

USING_NS_CC;

void generatePuzzles() {
    for (int i = 0; i < puzzleData.count; i++) {
        int dotCount = 0;
        for (int j = 0; j < puzzleData.stages[i].count; j++) {
            int size = puzzleData.stages[i].puzzleSize;
            Puzzle* p = Puzzle::generate(size, size);
            dotCount += p->solution.dots;
            CCLOG("==%d==, ===%s===", size, p->toString().c_str());
        }
        CCLOG("==stage %d, dotcount: %d", i+1, dotCount);
    }
}

void updateDesignResolutionSize() {
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize designSize = screenSize;

    float scales[] = {1.33, 1.5, 1.6, 1.71, 1.775, 1.7777, 2};
    std::vector<float> ratios(scales, scales + 7);
    std::sort(ratios.begin(), ratios.end());

    float ratio = screenSize.height / (screenSize.width * 1.0);
    typedef std::vector<float>::iterator RtatiosIter;
    RtatiosIter up = std::upper_bound(ratios.begin(), ratios.end(), ratio);
    RtatiosIter low = ratios.begin();
    if (up != ratios.begin()) {
        low = --up;
    }

    if (ratio - (*low) > ratio - (*up)) {
        ratio = *up;
    } else {
        ratio = *low;
    }

    if (ratio < 1.5) {
        float scale = std::max(screenSize.width / 768.0, screenSize.height / 1024.0);
        float scale1 = std::max(640 / 768.0, 960 / 1024.0);
        designSize.width = screenSize.width / scale * scale1;
        designSize.height = screenSize.height / scale * scale1;
    } else if (ratio < 1.6) {
        float scale = std::max(screenSize.width / 640.0, screenSize.height / 960.0);
        designSize.width = screenSize.width / scale;
        designSize.height = screenSize.height / scale;
    } else if (ratio < 1.75) {
        float scale = std::max(screenSize.width / 640.0, screenSize.height / 1024.0);
        designSize.width = screenSize.width / scale;
        designSize.height = screenSize.height / scale;
    } else if (ratio < 1.77) {
        float scale = std::max(screenSize.width / 640.0, screenSize.height / 1136.0);
        designSize.width = screenSize.width / scale;
        designSize.height = screenSize.height / scale;
    } else {
        float scale = std::max(screenSize.width / 576.0, screenSize.height / 1024.0);
        float scale1 = std::max(1024 / 960.0, 576 / 640.0);
        designSize.width = screenSize.width / scale * scale1;
        designSize.height = screenSize.height / scale * scale1;
    }

    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
}

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
    std::srand(unsigned(std::time(0)));
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    updateDesignResolutionSize();

    loadPlayerData();

    CCScene *pScene = createMenuScene();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
