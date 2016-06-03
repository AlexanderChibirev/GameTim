#include "Player.h"
#include "Bullet.h"
#include <iostream>
#include <string>

Player::Player() = default;

void Player::initOptions()
{
	this->SetDamage(10);
	this->SetHealthPoint(100);
	this->SetSpeed(250);
	this->SetDirection(MovementDirection(0, 0));
	this->m_state = this->state::stay;
	//this->m_states = 
	this->m_gun = this->CurrentGun::Knife;
	this->runAction(RepeatForever::create(m_currentState[0]));//это дл€ бега повтор€ем всегда
	this->schedule(schedule_selector(Player::Update), 1 / 60);
}

void Player::SetState(double const & move)
{
	if (m_currentAction->isDone())
	{
		if (m_state == state::stay && move != 0)
		{
			if (abs(m_moveController->getVelocity().x) + abs(m_moveController->getVelocity().y) != 0)
			{
				float angle = atan2(m_moveController->getVelocity().y, m_moveController->getVelocity().x);
				if (abs(angle) < 0.75)
				{
					CCLOG("R");
					this->stopAllActions();
					this->Right();
					m_state = run;
				}
				if (abs(angle) > 2.4 )
				{
					CCLOG("L");
					this->stopAllActions();
					this->Left();
					m_state = run;
				}
			}
		}
		else if (abs(m_moveController->getVelocity().x) + abs(m_moveController->getVelocity().y) == 0)
		{
			this->stopAllActions();
			this->Stay();
			m_state = state::stay;
		}
	}
}

void Player::ChooseNextGun()
{
	if ((m_gun == CurrentGun::Knife))
	{
		m_gun = CurrentGun::Pistol;
	}
	else
	{
		m_gun = CurrentGun::Knife;
	}
	m_currentState = m_states.find(m_gun)->second;
	m_currentAction = m_currentState[2];

	this->stopAllActions();
	state::run ? Right() : Stay();
}

void Player::initKnifeAnimations()
{
	SpriteFrameCache *sharedSpriteFrameCache = SpriteFrameCache::getInstance();
	std::vector<cocos2d::RefPtr<Animate>> animationsVector;

	auto animFrames = Vector<SpriteFrame*>(20);

	char str[100] = { 0 };
	for (int i = 1; i < 10; i++)
	{
		//survivor - idle_knife_00.png
		//idle_1.png
		sprintf(str, "idle_%d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.18);
	this->stayWithKnife = Animate::create(animation);
	animationsVector.push_back(Animate::create(animation));
	animFrames.clear();

	for (int i = 1; i < 27; i++) //ходьба с ножом
	{
		sprintf(str, "run_%d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	this->runWithKnife = Animate::create(animation);
	this->m_right = Animate::create(animation);
	animationsVector.push_back(Animate::create(animation));
	animFrames.clear();

	for (int i = 1; i < 27; i++) //ходьба с ножом
	{
		sprintf(str, "runL_%d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	this->m_left = Animate::create(animation);
	animationsVector.push_back(Animate::create(animation));


	////Sprite1->runAction(RepeatForever::create(Animate::create(animation)));
	animFrames.clear();

	for (int i = 1; i < 5; i++)
	{
		sprintf(str, "fire_%d.png", i);//анимаци€ атаки
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.1);
	animationsVector.push_back(Animate::create(animation));
	m_states.insert({ CurrentGun::Knife, animationsVector });
	m_currentAction = m_states.find(CurrentGun::Knife)->second[2];
}

void Player::initPistolAnimations()
{
	SpriteFrameCache *sharedSpriteFrameCache = SpriteFrameCache::getInstance();
	std::vector<cocos2d::RefPtr<Animate>> animationsVector;

	auto animFrames = Vector<SpriteFrame*>(20);

	char str[100] = { 0 };
	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "survivor-idle_handgun_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	this->stayWithKnife = Animate::create(animation);
	animationsVector.push_back(Animate::create(animation));
	animFrames.clear();

	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "survivor-move_handgun_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	this->runWithKnife = Animate::create(animation);
	animationsVector.push_back(Animate::create(animation));


	//Sprite1->runAction(RepeatForever::create(Animate::create(animation)));
	animFrames.clear();

	for (int i = 0; i < 3; i++)
	{
		sprintf(str, "survivor-shoot_handgun_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	animationsVector.push_back(Animate::create(animation));
	m_states.insert({ CurrentGun::Pistol, animationsVector });
}

Player* Player::create(Joystick *moveJoy/*, Joystick *rotateJoy, Legs * legs*/)

{
	Player* pSprite = new Player();
	pSprite->m_moveController = moveJoy;
	///pSprite->m_rotateController = rotateJoy;
	//pSprite->m_legs = legs;

	pSprite->initKnifeAnimations();
	pSprite->initPistolAnimations();
	pSprite->m_currentState = pSprite->m_states.find(CurrentGun::Knife)->second;

	if (pSprite->initWithSpriteFrameName("idle_1.png"))//тут создаетс€ картинка сто€чего персонажа 
	{
		pSprite->autorelease();
		pSprite->initOptions();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}


Vec2 Player::GetPositionHero()
{
	return { m_dx,m_dy } ;
}

void Player::SetGravityHero(float gravity)
{
	m_dy = gravity;
}

void Player::Update(float dt)
{
	double x = m_moveController->getVelocity().x;
	double y = m_moveController->getVelocity().y;
	double dx = 0;
	double dy = 0;

	//m_legs->Update(x, y);

	auto angle = this->getRotation();
	angle = (abs(360 - angle));
	angle = (int(angle) % 360 * M_PI) / 180;
	if (m_moveController->getVelocity().x != 0)
	{
		dx = x * cos(angle); //- y * sin(angle);
	}
	if (m_moveController->getVelocity().y != 0)
	{
		dy = x * sin(angle); //+ y * cos(angle);
	}
	m_dx = dx;
	
	x = dx*5 + this->getPosition().x;
	y = dy*5 + this->getPosition().y;

	this->setPosition(x, m_dy + y);
	//this->SetDirection(MovementDirection(dx, dy - 1));

	//m_shootDirection = (MovementDirection(-sin(angle), cos(angle)));
	//this->Move(dt);
	SetState(dx + dy);
}

void Player::Shoot(cocos2d::Layer * layer)
{

	if (m_gun != CurrentGun::Knife)
	{
		auto bullet = CBullet::create(this->m_shootDirection, this->getPosition());
		bullet->setRotation(this->getRotation() - 90);
		layer->addChild(bullet);
	}
	else
	{
		this->stopAllActions();
		m_state = state::run;
		m_currentAction = m_states.find(CurrentGun::Knife)->second[3];//вместо этого сделать прыжок
		this->runAction(m_currentAction);

	}
}

void Player::Stay()
{
	runAction(RepeatForever::create(m_currentState[0]));
}


void Player::Left()
{
	runAction(RepeatForever::create( (m_left)));
}

void Player::Right()
{
	runAction(RepeatForever::create(m_right));
}



//
//void Legs::Run()
//{
//	runAction(RepeatForever::create(m_run));
//}
//
//void Legs::Left()
//{
//	runAction(RepeatForever::create(m_left));
//}
//
//void Legs::Right()
//{
//	runAction(RepeatForever::create((m_left)->reverse()));
//}
//
