#include "CCScrollLayer.h"

CCScrollLayer* CCScrollLayer::layerWithLayers(CCArray * layers, float layerWidth, int space)
{	
	CCScrollLayer * pRet = new CCScrollLayer();
	if (pRet && pRet->initWithLayers(layers, layerWidth, space))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCScrollLayer::initWithLayers(CCArray * layers, float layerSize, int space)
{	
	if (CCLayer::init())
	{		
		// Make sure the layer accepts touches
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
        
		currentScreen = 1;
		// offset added to show preview of next/previous screens
		scrollWidth  = (int)CCDirector::sharedDirector()->getWinSize().width;
		scrollHeight = (int)CCDirector::sharedDirector()->getWinSize().height / 2;
		
        CCAssert( (layerSize + space) <= scrollWidth, "Scroll  width must be greater then layer width");
        int layersInScreen = 0;
		unsigned int i = 1;
        while ((i<layers->count()) && ((layerSize + space) * i <= scrollWidth)) {
            layersInScreen++;
            i++;
        }
        startWidth = space/2;
        scrollWidth = layersInScreen * (layerSize + space);
        
        totalScreens = ceil(layers->count() / (float)layersInScreen);
		for (i=0; i<layers->count(); i++)
		{
                    CCLayer* l = (CCLayer *)layers->objectAtIndex(i);
                    l->setAnchorPoint(ccp(0, 0));
                    l->setPosition(ccp(startWidth + (layerSize + space) * i, scrollHeight-layerSize/2));
                    addChild(l);
		}
        
		return true;	
	}
	else
	{
		return false;
	}	
}

void CCScrollLayer::moveToPage(int page)
{	
	CCEaseBounce* changePage = CCEaseBounce::create(CCMoveTo::create(0.3f, ccp(-((page-1)*scrollWidth),0)));
	this->runAction(changePage);
	currentScreen = page;	
}

void CCScrollLayer::moveToNextPage()
{	
	CCEaseBounce* changePage = CCEaseBounce::create(CCMoveTo::create(0.3f, ccp(-(((currentScreen+1)-1)*scrollWidth),0)));
	
	this->runAction(changePage);
	currentScreen = currentScreen+1;	
}

void CCScrollLayer::moveToPreviousPage()
{	
	CCEaseBounce* changePage = CCEaseBounce::create(CCMoveTo::create(0.3f, ccp(-(((currentScreen-1)-1)*scrollWidth),0)));
	this->runAction(changePage);
	currentScreen = currentScreen-1;	
}

void CCScrollLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool CCScrollLayer::ccTouchBegan(CCTouch *touch, CCEvent *withEvent)
{
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	startSwipe = (int)touchPoint.x;
	return true;
}

void CCScrollLayer::ccTouchMoved(CCTouch *touch, CCEvent *withEvent)
{	
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	this->setPosition(ccp((-(currentScreen-1)*scrollWidth)+(touchPoint.x-startSwipe),0));
}

void CCScrollLayer::ccTouchEnded(CCTouch *touch, CCEvent *withEvent)
{
	
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	
	int newX = (int)touchPoint.x;
		
	if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
	{
		this->moveToNextPage();
	}
	else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
	{
		this->moveToPreviousPage();
	}
	else
	{
		this->moveToPage(currentScreen);		
	}	
}