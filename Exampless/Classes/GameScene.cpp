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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	//auto backgrowndSprite = Sprite::create("bg.jpg");
	//backgrowndSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//this->addChild(backgrowndSprite);
	m_customMap = make_node<CCustomMap>("tmx/layer_1.tmx");
	addChild(m_customMap);


	auto joy = Joystick::create();
	//auto joyR = Joystick::create();
	//joyR->SetCenter(Director::getInstance()->getVisibleSize().width - 128, 0);
	m_joy = joy;
	//m_joyR = joyR;

	SpriteFrameCache *sharedSpriteFrameCache = SpriteFrameCache::getInstance();
	sharedSpriteFrameCache->addSpriteFramesWithFile("idleHero.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("fireHero.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("runHero.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("runHeroLeft.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("move_with_knife.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("melee_knife.plist");

	sharedSpriteFrameCache->addSpriteFramesWithFile("idle_pistol.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("move_pistol.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("shoot_pistol.plist");

	sharedSpriteFrameCache->addSpriteFramesWithFile("run.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("strafe_left.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("strafe_right.plist");

	//auto legs = Legs::create();


	m_player = Player::create(joy);//, legs);
	this->m_player->setPosition((m_customMap->GetHeroWorldPosition().origin));
	
	
	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(m_player->getPosition().x); // set to players x 
	cameraTarget->setPositionY(m_player->getPosition().y); // center of height 
	cameraTarget->retain();
	camera = Follow::create(cameraTarget, Rect::ZERO);
	camera->retain();
	this->runAction(camera);
	m_obstacles = m_customMap->GetObcaslePosition();

	//legs->setPosition(500, 500);
	//this->addChild(legs);
	
	this->addChild(joy);
	this->addChild(m_player);

	//this->schedule(schedule_selector(player->Shoot), 2);

	
	//this->addChild(joyR);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(GameScene::UpdateCamera, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto playItem = MenuItemImage::create("GUN.png", "GUN.png", CC_CALLBACK_1(GameScene::ChooseGun, this));
	playItem->setPosition(Point(visibleSize.width - playItem->getContentSize().width + origin.x, visibleSize.height / 2 + origin.y));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);
	//this->addChild(menu);

	
	this->scheduleUpdate();
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


void GameScene::update(float dt)
{
	cameraTarget->setPositionX(m_player->getPosition().x); // set to players x 
	cameraTarget->setPositionY(m_player->getPosition().y); // center of height 
	cameraTarget->retain();

	camera = Follow::create(cameraTarget, Rect::ZERO);
	camera->retain();
	this->runAction(camera);

	float dx = m_player->GetPositionHero().x;
	float dy = m_player->GetPositionHero().y;
	float x = m_player->getPosition().x;
	float y = m_player->getPosition().y;

	
	if(m_player->m_onGround)
	{
		m_player->SetGravityHero(0);
	}
	else
	{
		m_player->SetGravityHero(-3);
	}
	m_joy->setPosition(x - 470, y - 300);
	for (auto &it : m_obstacles)
	{
		if (it.intersectsRect(m_player->getBoundingBox()))
		{
			if (dy > 0)//если мы шли наверх
			{
				m_player->setPosition(x, y - 2.8);//зависит от скорости прыжка
			}
			if (dy < 0)
			{
				m_player->m_onGround = true;
				m_player->setPosition(x, y+3.1);//если падаем
			}
			if (dx > 0)
			{
				m_player->setPosition(x - 5 , y);//4.15 с мотором
			}
			if (dx < 0)
			{
				m_player->setPosition(x + 4.15, y);
			}
		}
	}
}