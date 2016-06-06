#include "Player.h"
#include "Bullet.h"


Player::Player() = default;

void Player::initOptions()
{
	this->SetDamage(10);
	this->SetHealthPoint(100);
	this->SetSpeed(100);
	this->SetDirection(MovementDirection(0, 0));
	this->m_state = this->state::stay;
	this->m_gun = this->CurrentGun::Knife;
	this->runAction(RepeatForever::create(m_currentState[0]));//это для бега повторяем всегда

	this->schedule(schedule_selector(Player::Update), 1 / 60);
}

void Player::SetState(double const & move)
{
	if (m_currentAction->isDone())
	{
		if (m_state == state::stay && move != 0)
		{
			this->stopAllActions();
			this->Run();
			this->m_state = state::run;
		}
		else if (m_state == state::run && move == 0)
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
	state::run ? Run() : Stay();
}

void Player::initKnifeAnimations()
{
	SpriteFrameCache *sharedSpriteFrameCache = SpriteFrameCache::getInstance();
	std::vector<cocos2d::RefPtr<Animate>> animationsVector;

	auto animFrames = Vector<SpriteFrame*>(20);

	char str[100] = { 0 };
	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "survivor-idle_knife_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	this->stayWithKnife = Animate::create(animation);
	animationsVector.push_back(Animate::create(animation));
	animFrames.clear();

	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "survivor-move_knife_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	this->runWithKnife = Animate::create(animation);
	animationsVector.push_back(Animate::create(animation));


	//Sprite1->runAction(RepeatForever::create(Animate::create(animation)));
	animFrames.clear();

	for (int i = 0; i < 14; i++)
	{
		sprintf(str, "survivor-meleeattack_knife_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
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

Player* Player::create(Joystick *moveJoy,/* Joystick *rotateJoy, */Legs * legs)

{
	Player* pSprite = new Player();
	pSprite->m_moveController = moveJoy;
	///pSprite->m_rotateController = rotateJoy;
	pSprite->m_legs = legs;

	pSprite->initKnifeAnimations();
	pSprite->initPistolAnimations();
	pSprite->m_currentState = pSprite->m_states.find(CurrentGun::Knife)->second;

	if (pSprite->initWithSpriteFrameName("survivor-idle_knife_00.png"))//тут создается картинка стоячего персонажа 
	{
		pSprite->autorelease();
		pSprite->initOptions();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

void Player::Update(float dt)
{
	double x = m_moveController->getVelocity().x;
	double y = m_moveController->getVelocity().y;
	double dx = 0;
	double dy = 0;

	m_legs->Update(x, y);

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
	x = dx + this->getPosition().x;
	y = dy + this->getPosition().y;

	this->SetDirection(MovementDirection(dx, dy));

	m_shootDirection = (MovementDirection(-sin(angle), cos(angle)));
	this->Move(dt);
	m_legs->setPosition(this->getPosition());
	SetState(dx + dy);
	////func
	//double rotateX = m_rotateController->getVelocity().x;

	//this->setRotation(this->getRotation() + rotateX);
	m_legs->setRotation(this->getRotation());


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
		m_currentAction = m_states.find(CurrentGun::Knife)->second[2];
		this->runAction(m_currentAction);

	}
}


void Player::Run()
{
	runAction(RepeatForever::create(m_currentState[1]));
}

void Player::Stay()
{
	runAction(RepeatForever::create(m_currentState[0]));
}


