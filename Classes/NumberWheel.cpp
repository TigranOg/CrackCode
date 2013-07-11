#include "NumberWheel.h"


NumberWheel::NumberWheel(GameScene* pOwner, int positionOfCode, char startSymbol, int startWidth)
{	
	this->pOwner = pOwner;
	//pOwner->currentState.code.length;
    this->positionOfCode = positionOfCode;

	int startHeight = (int)CCDirector::sharedDirector()->getWinSize().height - 70;

	// offset added to show preview of next/previous screens
	CCMenuItem* plusButton = CCMenuItemImage::create("plus_button_normal.png", "plus_button_pressed.png", this,
                                                                menu_selector(NumberWheel::plusClickCallback));
    plusButton->setPosition(ccp(startWidth, startHeight + 42));
	CCMenuItem* minusButton = CCMenuItemImage::create("minus_button_normal.png", "minus_button_pressed.png", this,
                                                                menu_selector(NumberWheel::minusClickCallback));
    minusButton->setPosition(ccp(startWidth, startHeight - 40));
    std::string tempStr;
    tempStr.push_back(startSymbol);
    pSymbolLabel = CCLabelBMFont::create(tempStr.c_str(), "futura-48.fnt");
	CCMenuItem * symbolItem = CCMenuItemLabel::create(pSymbolLabel, this, NULL);
    symbolItem->setPosition(ccp(startWidth, startHeight));
    
	CCMenu* menu = CCMenu::create(plusButton, symbolItem, minusButton, NULL);
	menu->setPosition(CCPointZero);
    
	this->addChild(menu, 1);
}


NumberWheel::~NumberWheel() {
}

void NumberWheel::plusClickCallback(CCObject* pSender)
{
    char newSymbol = pOwner->changeSymbol(positionOfCode, true);
    if (newSymbol != '&') {
        std::string tempStr;
        tempStr.push_back(newSymbol);
        pSymbolLabel->setCString(tempStr.c_str());
    }
}

void NumberWheel::minusClickCallback(CCObject* pSender)
{
    char newSymbol = pOwner->changeSymbol(positionOfCode, false);
    if (newSymbol != '&') {
        std::string tempStr;
        tempStr.push_back(newSymbol);
        pSymbolLabel->setCString(tempStr.c_str());
    }
}



