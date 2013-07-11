//  CCScrollLayer.h
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010 All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CCScrollLayer : public CCLayer 
{
protected:
	// Holds the current height and width of the screen
	int scrollHeight;
	
	// Holds the height and width of the screen when the class was inited
	int startHeight;
	int startWidth;
	
	// A count of the total screens available
	int totalScreens;

	// The initial point the user starts their swipe
	int startSwipe;	

	void moveToPage(int page);
	void moveToNextPage();
	void moveToPreviousPage();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *withEvent);
	virtual void ccTouchMoved(CCTouch *touch, CCEvent *withEvent);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent *withEvent);
    
public:
	// Holds the current page being displayed
	int currentScreen;
	int scrollWidth;

	static CCScrollLayer* layerWithLayers(CCArray * layers, float layerWidth, int space);
	bool initWithLayers(CCArray * layers, float layerWidth, int space);
	CREATE_FUNC(CCScrollLayer);
};