#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "LevelChooser.h"
#include "CCScrollLayer.h"
#include "GameScene.h"
#include "MultiResolution.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MainMenu::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MainMenu *pMenuLayer = MainMenu::create();

	OptionsLayer *pOptionsLayer = new OptionsLayer();

	CCLayerMultiplex* layer = CCLayerMultiplex::create(pMenuLayer, pOptionsLayer, NULL);

	// add layer as a child to scene
	scene->addChild(layer);


	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float scale = MultiResolution::getScale();
	/////////// Menu ////////////
	CCLabelBMFont* labelStart = CCLabelBMFont::create("Start", "futura-48.fnt");
	CCMenuItemLabel* pStartItem = CCMenuItemLabel::create(labelStart, this, menu_selector(MainMenu::menuStartCallback));
	pStartItem->setPosition(ccp(size.width/2, size.height/2));
	pStartItem->setScale(scale);

	CCLabelBMFont* labelOptions = CCLabelBMFont::create("Options", "futura-48.fnt");
	CCMenuItemLabel *pOptionsItem = CCMenuItemLabel::create(labelOptions, this, menu_selector(MainMenu::menuOptionsCallback));
	pOptionsItem->setPosition(ccp(size.width/2, size.height/2 - pStartItem->getContentSize().height*scale));
	pOptionsItem->setScale(scale);

	CCLabelBMFont* labelExit = CCLabelBMFont::create("Exit", "futura-48.fnt");
	CCMenuItemLabel *pExitItem = CCMenuItemLabel::create(labelExit, this, menu_selector(MainMenu::menuCloseCallback));
	pExitItem->setPosition(ccp(size.width/2, size.height/2 - 2*pStartItem->getContentSize().height*scale));
	pExitItem->setScale(scale);

	CCMenu* pMenu = CCMenu::create(pStartItem, pOptionsItem, pExitItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);
	/////////////////////////////

	//////////// Game title and background image  ////////////
	CCLabelBMFont* pLabel = CCLabelBMFont::create("Crack Code", "futura-48.fnt");

	// position the label on the center of the screen
	pLabel->setPosition( ccp(size.width / 2, size.height - 50*scale) );
	pLabel->setScale(scale+0.3);

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "MainMenu" splash screen"
	CCSprite* pSprite = CCSprite::create("safe_background.jpg");

	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width / 2, size.height / 2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	//////////////////////////////////////////////////////////

	return true;
}

void MainMenu::menuStartCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1.0f, LevelChooser::scene()));
}

void MainMenu::menuOptionsCallback(CCObject* pSender)
{
	((CCLayerMultiplex*)m_pParent)->switchTo(1);
}

void MainMenu::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

OptionsLayer::OptionsLayer()
{
	CCMenuItemFont::setFontName("American Typewriter");
	CCMenuItemFont::setFontSize(26);
	CCMenuItemFont*title1 = CCMenuItemFont::create("Sound");
	title1->setEnabled(false);
	CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize(46);
	CCMenuItemToggle* item1 = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(OptionsLayer::menuCallback), 
		CCMenuItemFont::create( "On" ),
		CCMenuItemFont::create( "Off"),
		NULL );

	CCMenuItemFont::setFontName( "American Typewriter" );
	CCMenuItemFont::setFontSize(26);
	CCMenuItemFont* title2 = CCMenuItemFont::create( "Music" );
	title2->setEnabled(false);
	CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize(46);
	CCMenuItemToggle *item2 = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(OptionsLayer::menuCallback),
		CCMenuItemFont::create( "On" ),
		CCMenuItemFont::create( "Off"),
		NULL );

	CCMenuItemFont::setFontName( "American Typewriter" );
	CCMenuItemFont::setFontSize(26);
	CCMenuItemFont* title3 = CCMenuItemFont::create( "Quality" );
	title3->setEnabled( false );
	CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize(46);
	CCMenuItemToggle *item3 = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(OptionsLayer::menuCallback), 
		CCMenuItemFont::create( "High" ),
		CCMenuItemFont::create( "Low" ),
		NULL );

	CCMenuItemFont::setFontName( "American Typewriter" );
	CCMenuItemFont::setFontSize(26);
	CCMenuItemFont* title4 = CCMenuItemFont::create( "Orientation" );
	title4->setEnabled(false);
	CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize(46);
	CCMenuItemToggle *item4 = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(OptionsLayer::menuCallback), 
		CCMenuItemFont::create( "Off" ), 
		NULL );

	//UxArray* more_items = UxArray::arrayWithObjects(
	//                                                 CCMenuItemFont::create( "33%" ),
	//                                                 CCMenuItemFont::create( "66%" ),
	//                                                 CCMenuItemFont::create( "100%" ),
	//                                                 NULL );
	// TIP: you can manipulate the items like any other CCMutableArray
	item4->getSubItems()->addObject( CCMenuItemFont::create( "33%" ) ); 
	item4->getSubItems()->addObject( CCMenuItemFont::create( "66%" ) ); 
	item4->getSubItems()->addObject( CCMenuItemFont::create( "100%" ) ); 

	// you can change the one of the items by doing this
	item4->setSelectedIndex( 2 );

	CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize( 60 );

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenu *menu = CCMenu::create(
		title1, title2,
		item1, item2,
		title3, title4,
		item3, item4, NULL); 

	menu->alignItemsInColumns(2, 2, 2, 2);

	this->addChild(menu, 1);

	CCLabelBMFont *label = CCLabelBMFont::create( "go back", "futura-48.fnt" );
	CCMenuItemLabel* back = CCMenuItemLabel::create(label, this, menu_selector(OptionsLayer::backCallback) );
	CCMenu *menuBack = CCMenu::create(back, NULL);
	menuBack->setPosition(ccp(size.width - 100, 50));
	this->addChild(menuBack, 1);
	
	menu->setPosition(ccp(size.width/2, size.height/2));

	// add "MainMenu" splash screen"
	CCSprite* pSprite = CCSprite::create("safe_background.jpg");

	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width / 2, size.height / 2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
}

OptionsLayer::~OptionsLayer()
{
}

void OptionsLayer::menuCallback(CCObject* sender)
{
	//UXLOG("selected item: %x index:%d", dynamic_cast<CCMenuItemToggle*>(sender)->selectedItem(), dynamic_cast<CCMenuItemToggle*>(sender)->selectedIndex() ); 
}

void OptionsLayer::backCallback(CCObject* sender)
{
	((CCLayerMultiplex*)m_pParent)->switchTo(0);
}




