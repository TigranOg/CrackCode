//
//  GameScene.cpp
//  CrackCode
//
//  Created by Olga on 17.02.13.
//
//

#include "GameScene.h"
#include "CodeChecker.h"
#include "LevelChooser.h"
#include "NumberWheel.h"
#include "UserInfoManager.h"


using namespace cocos2d;

static CCPoint s_tCurPos = CCPointZero;

CCScene* GameScene::scene(int level)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
    
	// 'layer' is an autorelease object
	GameScene * pGameScene = GameScene::create();
    pGameScene->GameScene::loadLevel(level);
    
	// add layer as a child to scene
	scene->addChild(pGameScene);
    
    
	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();
        
	CCMenuItem* submitButton = CCMenuItemImage::create("submit.png", "submit.png", this, menu_selector(GameScene::submitCallback));
    submitButton->setPosition(ccp(size.width - 50, 30));
    
	CCMenuItem* restartButton = CCMenuItemImage::create("restart.png", "restart_2.png", this, menu_selector(GameScene::restartCallback));
    restartButton->setPosition(ccp(size.width/2, 30));

	CCMenuItem* pBack = CCMenuItemImage::create("back.png", "back.png", this, menu_selector(GameScene::backCallback));
    pBack->setPosition(ccp(50, 30));

	pTime = CCLabelBMFont::create( "", "futura-48.fnt" );
    pTime->setPosition(ccp(100, 50));
	CCMenu* pMenu = CCMenu::create(pBack, restartButton, submitButton, NULL);
    pMenu->setPosition(ccp(0,0));
       
    attemptsLayer = AttemptScrollLayer::layerWithLayers();
    attemptsLayer->setPosition(ccp(0, 0));
    
	this->addChild(pMenu, 1);
    this->addChild(pTime, 1);
    this->addChild(attemptsLayer, 0);
    this->schedule(schedule_selector(GameScene::TimeDisplay),1.0);
    
	CCSprite* pSprite = CCSprite::create("safe_background.jpg");

	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width / 2, size.height / 2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, -1);
    
	return true;
}

void GameScene::TimeDisplay(CCTime dt){
    CodeChecker::currentState.time++;
    char time[10] = {0};
    sprintf(time, "%i : %i", CodeChecker::currentState.time / 60, CodeChecker::currentState.time % 60);
    pTime->setString(time);
}

void GameScene::backCallback(CCObject* sender)
{
    UserInfoManager::saveLevelInfo();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1.0f, LevelChooser::scene()));
}

void GameScene::submitCallback(CCObject* sender)
{
    std::string attempt;
    for (int i=0; i<CodeChecker::currentState.code.length(); i++) {
        attempt.push_back(CodeChecker::levelParams.possibleSymbols[tempSymbolPositions[i]]);
    }
    if ((CodeChecker::attempts.size() > 0) && (CodeChecker::attempts.back().attempt == attempt)) {
        return;
    }
    std::string resStr;
    Attempt a;
    a.attempt = attempt;
    a.results = CodeChecker::checkCode(attempt, CodeChecker::currentState.code);
    
    CodeChecker::attempts.push_back(a);
    attemptsLayer->redrawAttempts(true);
    
    UserInfoManager::saveLevelInfo();
}

void GameScene::loadLevel(int level) {
    if (CodeChecker::currentState.code == "") {
        restartLevel();
    } else {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        tempSymbolPositions = new int[CodeChecker::currentState.code.length()];
        for (int i=0; i<CodeChecker::currentState.code.length(); i++) {
            if (CodeChecker::attempts.size() > 0) {
                tempSymbolPositions[i] = CodeChecker::getPositionOfSymbol(CodeChecker::attempts.back().attempt[i]);
            } else {
                tempSymbolPositions[i] = 0;
            }
            NumberWheel * nw = new NumberWheel(this, i, CodeChecker::levelParams.possibleSymbols[tempSymbolPositions[i]],
                                               size.width/2 - (CodeChecker::currentState.code.length()/2.0 - 0.5 - i) * 90);
            this->addChild(nw);
        }
        attemptsLayer->redrawAttempts(false);
    }
}

void GameScene::restartLevel() {
    LevelParams params = CodeChecker::levels[CodeChecker::currentState.level];
    CodeChecker::levelParams = CodeChecker::levels[CodeChecker::currentState.level];
    CodeChecker::currentState.time = 0;
    CodeChecker::currentState.code = CodeChecker::generateCode(params.length, params.minRepeats, params.maxRepeats, params.possibleSymbols);
	
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    tempSymbolPositions = new int[CodeChecker::currentState.code.length()];
    for (int i=0; i<CodeChecker::currentState.code.length(); i++) {
        tempSymbolPositions[i] = 0;
        NumberWheel * nw = new NumberWheel(this, i, CodeChecker::levelParams.possibleSymbols[tempSymbolPositions[i]],
                                           size.width/2 - (CodeChecker::currentState.code.length()/2.0 - 0.5 - i) * 90);
        this->addChild(nw);
    }
    CodeChecker::attempts.clear();
}

void GameScene::restartCallback(CCObject* sender) {
    this->restartLevel();
    CCScene* s = GameScene::scene(CodeChecker::currentState.level);
    CCDirector::sharedDirector()->replaceScene(s);
}

char GameScene::changeSymbol(int position, bool isPlus) {
    int newPosition;
    if (isPlus) {
        newPosition = tempSymbolPositions[position] + 1;
    } else {
        newPosition = tempSymbolPositions[position] - 1;
    }
    if ((newPosition >= 0) && (newPosition < (CodeChecker::levelParams.possibleSymbols.length()))) {
        tempSymbolPositions[position] = newPosition;
        return CodeChecker::levelParams.possibleSymbols[newPosition];
    }
    return '&';
}


