//  CCScrollLayer.h
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010 All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
#pragma once
#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class NumberWheel : public CCLayer 
{	   
public:
	NumberWheel(GameScene* pOwner, int positionOfCode, char startSymbol, int startWidth);
	~NumberWheel();
    void plusClickCallback(CCObject* pSender);
    void minusClickCallback(CCObject* pSender);
    
private:
    CCLabelBMFont* pSymbolLabel;
    int positionOfCode;
    GameScene* pOwner;
};