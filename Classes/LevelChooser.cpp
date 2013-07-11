#include "LevelChooser.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "CCScrollLayer.h"
#include "MultiResolution.h"
#include "CodeChecker.h"
#include "UserInfoManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScrollLayer* pScrollLevelLayer;

CCScene* LevelChooser::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	LevelChooser *pTestLayer = LevelChooser::create();

	// add layer as a child to scene
	scene->addChild(pTestLayer);


	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelChooser::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

    CodeChecker::initLevels();
    
	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	float scale = MultiResolution::getScale();
	CCLabelBMFont* pLabel = CCLabelBMFont::create("Select Level", "futura-48.fnt");
	pLabel->setPosition( ccp(size.width / 2, size.height - 50*scale) );
	pLabel->setScale(MultiResolution::getScale());
	this->addChild(pLabel, 1);

	LevelLayer *level1 = new LevelLayer("lvl1.png", 1);
	LevelLayer *level2 = new LevelLayer("lvl2.png", 2);
	LevelLayer *level3 = new LevelLayer("lvl3.png", 3);
	LevelLayer *level4 = new LevelLayer("lvl4.png", 4);

    CCArray layers;
	layers.addObject(level1);
    layers.addObject(level2);
    layers.addObject(level3);
    layers.addObject(level4);

    pScrollLevelLayer = CCScrollLayer::layerWithLayers(&layers, 160, 60);
    this->addChild(pScrollLevelLayer,1);
	
	CCLabelBMFont * pLabel1 = CCLabelBMFont::create( "go back", "futura-48.fnt" );
	CCMenuItemLabel * pBack = CCMenuItemLabel::create(pLabel1, this, menu_selector(LevelChooser::backCallback));
	CCMenu* pMenu = CCMenu::create(pBack, NULL);
    pMenu->setPosition(ccp(size.width - 100, 50));

	this->addChild(pMenu, 1);

	CCSprite* pSprite = CCSprite::create("safe_background.jpg");
	pSprite->setPosition( ccp(size.width / 2, size.height / 2) );
	this->addChild(pSprite, 0);
	return true;
}

void LevelChooser::backCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1.0f, MainMenu::scene()));
}

LevelLayer::LevelLayer(const char *picName, int levlNo) {
	this->levlNo = levlNo;
	pSpriteLvl = CCSprite::create(picName);
    pSpriteLvl->setAnchorPoint(ccp(0,0));
	addChild(pSpriteLvl);
	setContentSize(CCSizeMake(160, 160));
}

LevelLayer::~LevelLayer() {

}

void LevelLayer::onEnter(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1,false);
    CCLayer::onEnter();
}

void LevelLayer::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool LevelLayer::ccTouchBegan(CCTouch *touch, CCEvent *withEvent) {
	CCPoint point = touch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    point.x += (pScrollLevelLayer->currentScreen - 1) * pScrollLevelLayer->scrollWidth;
    return rect().containsPoint(point);
}

void LevelLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
	CCPoint point = pTouch->getLocationInView();
    point = CCDirector::sharedDirector()->convertToGL(point);
    point.x += (pScrollLevelLayer->currentScreen - 1) * pScrollLevelLayer->scrollWidth;
    if (rect().containsPoint(point)) {
        CCScaleBy * firstAction = CCScaleBy::create(0.05f, 0.95f);
        CCScaleTo * secondAction = CCScaleTo::create(0.125f, 1);
        CCCallFunc * callStartGame = CCCallFunc::create(this, callfunc_selector(LevelLayer::gameSceneCallback));
        CCSequence * actionSequence = CCSequence::create(firstAction, secondAction, callStartGame, NULL);
        pSpriteLvl->runAction(actionSequence);
	}
}

CCRect LevelLayer::rect() {
    CCRect c = CCRectMake(this->getPosition().x, this->getPosition().y, this->getContentSize().width, this->getContentSize().height);
    return c;
}

void LevelLayer::gameSceneCallback()
{
    UserInfoManager::loadLevelInfo(levlNo);
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1.0f, GameScene::scene(levlNo)));
}


