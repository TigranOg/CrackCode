//
//  GameScene.h
//  CrackCode
//
//  Created by Olga on 17.02.13.
//
//

#ifndef __CrackCode__GameScene__
#define __CrackCode__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "AttemptScrollLayer.h"

using namespace cocos2d;

typedef enum {
	GameStateNotStarted,
	GameStateRunning,
	GameStateGameOver,
	GameStateLevelOver,
	GameStatePaused,
} GameState;


class GameScene: public CCLayer
{
public:
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
	virtual bool init();
	static cocos2d::CCScene* scene(int level);

	void loadLevel(int level);

	void restartLevel();

	void backCallback(CCObject* pSender);

	void submitCallback(CCObject* sender);

	void restartCallback(CCObject* sender);

	char changeSymbol(int position, bool isPlus);

	int* tempSymbolPositions;
    void TimeDisplay(CCTime dt);
    CCLabelBMFont * pTime;
    
	//preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(GameScene);

private:
	GameState gameState;
	AttemptScrollLayer* attemptsLayer;
};


#endif /* defined(__CrackCode__GameScene__) */
