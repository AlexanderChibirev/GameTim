#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Legs.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//1. super init first
	if (!Layer::init())
	{
		return false;
	}

	/*CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(POINT_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(LOSE_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(DROP_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_SOUND.c_str());*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto backgrowndSprite = Sprite::create("SS.jpg");
	backgrowndSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgrowndSprite);
	auto joy = Joystick::create();
	//auto joyR = Joystick::create();
	//joyR->SetCenter(Director::getInstance()->getVisibleSize().width - 128, 0);
	m_joy = joy;
	//m_joyR = joyR;

	SpriteFrameCache *sharedSpriteFrameCache = SpriteFrameCache::getInstance();
	sharedSpriteFrameCache->addSpriteFramesWithFile("idle.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("move_with_knife.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("melee_knife.plist");

	sharedSpriteFrameCache->addSpriteFramesWithFile("idle_pistol.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("move_pistol.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("shoot_pistol.plist");

	sharedSpriteFrameCache->addSpriteFramesWithFile("run.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("strafe_left.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("strafe_right.plist");

	auto legs = Legs::create();


	m_player = Player::create(joy, legs);
	this->m_player->setPosition(500, 500);
	legs->setPosition(500, 500);
	this->addChild(legs);
	this->addChild(m_player);

	//this->schedule(schedule_selector(player->Shoot), 2);

	this->addChild(joy);
	//this->addChild(joyR);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto playItem = MenuItemImage::create("GUN.png", "GUN.png", CC_CALLBACK_1(GameScene::ChooseGun, this));
	playItem->setPosition(Point(visibleSize.width - playItem->getContentSize().width + origin.x, visibleSize.height / 2 + origin.y));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

bool GameScene::onTouchBegan(Touch * pTouches, Event * event)
{
	if (!m_joy->isContainTouch(pTouches)/* && !m_joyR->isContainTouch(pTouches)*/)
	{
		m_player->Shoot(this);
	}
	return true;
}

void GameScene::ChooseGun(cocos2d::Ref *sender)
{
	m_player->ChooseNextGun();
}

