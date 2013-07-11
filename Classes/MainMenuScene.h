#ifndef __MainMenu_SCENE_H__
#define __MainMenu_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

typedef struct
{
	cocos2d::CCSize size;
	char directory[100];
}Resolution;

class MainMenu : public CCLayer
{
public:
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
	virtual bool init();

	static cocos2d::CCScene* scene();
	void menuStartCallback(CCObject* pSender);
	void levelStartCallback(CCObject* pSender);
	void menuOptionsCallback(CCObject* pSender);
	void menuCloseCallback(CCObject* pSender);

	// preprocessor macro for "static create()" constructor ( node() deprecated )
	CREATE_FUNC(MainMenu);
};

#endif // __MainMenu_SCENE_H__

class OptionsLayer : public CCLayer
{
public:
	OptionsLayer(void);
	~OptionsLayer();

public:
	void menuCallback(CCObject* pSender);
	void backCallback(CCObject* pSender);

	//CREATE_NODE(OptionsLayer);
};




