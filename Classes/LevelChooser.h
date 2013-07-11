#ifndef __Level_Chooser_H__
#define __Level_Chooser_H__

#include "cocos2d.h"

using namespace cocos2d;

class LevelChooser: public CCLayer
{
public:
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
	virtual bool init();
	static cocos2d::CCScene* scene();
	void backCallback(CCObject* pSender);
	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(LevelChooser);
};


class LevelLayer : public CCLayer {

private:
    virtual void onEnter();
    virtual void onExit();
    
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *withEvent);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent *withEvent);
    
    void gameSceneCallback();
    bool containsTouchLocation(CCTouch* touch);
    CCRect rect();
	int levlNo;

public:
	LevelLayer(const char *picName, int levlNo);
	~LevelLayer();
	CCSprite* pSpriteLvl;
};

#endif // __Level_Chooser_H__
