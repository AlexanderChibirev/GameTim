#include "Enemy.h"
#include "MathAndLogic.h"
#include "Definitions.h"
CEnemy * CEnemy::create(cocos2d::Point const& position, Player * player)

{
	CEnemy* pSprite = new CEnemy();

	pSprite->setPosition(position);
	pSprite->m_target = player;
	
	if (pSprite->initWithFile("enemy.png"))
	{
		pSprite->autorelease();
		pSprite->initOptions();
		//	pSprite->runAction(RepeatForever::create(Animate::create(pSprite->stayWithKnife)));
		return pSprite;
	}



	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

void CEnemy::initAnimations()
{
	/*SpriteFrameCache *sharedSpriteFrameCache = SpriteFrameCache::getInstance();
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
	animationsVector.push_back(Animate::create(animation));
	m_stay = Animate::create(animation);
	animFrames.clear();

	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "survivor-move_knife_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	animationsVector.push_back(Animate::create(animation));
	m_run = Animate::create(animation);

	animFrames.clear();

	for (int i = 0; i < 14; i++)
	{
		sprintf(str, "survivor-meleeattack_knife_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		frame->setOffset(this->getOffsetPosition());
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	animationsVector.push_back(Animate::create(animation));
	m_attack = Animate::create(animation);*/
}

void CEnemy::Update(float dt)
{
	if (IsLife())
	{
		if (m_angry)
		{
			Move(dt);
			auto angle = SMath::CalculateAngle(this->getPosition(), m_target->getPosition());
			this->setRotation(angle);
			this->SetDirection(MovementDirection(sin(angle + 90), cos(angle + 90)));
		}
	}
	else
	{
		this->Destroy();
	}
}

void CEnemy::MakeAngry()
{
	m_angry = true;
}


void CEnemy::initOptions()
{
	this->m_angry = false;
	this->SetSpeed(100);
	this->SetDamage(10);
	this->SetHealthPoint(150);
	this->m_action = ActionStay;
	this->schedule(schedule_selector(CEnemy::Update), 1 / 60);
	//auto playerPhysicsBoby = PhysicsBody::createBox(this->getContentSize());
	//playerPhysicsBoby->setCollisionBitmask(0x000002);
	//playerPhysicsBoby->setContactTestBitmask(true);
	//playerPhysicsBoby->setGravityEnable(false);
	//this->setPhysicsBody(playerPhysicsBoby);
}

CEnemy::CEnemy() = default;

void CEnemy::Run()
{
	runAction(RepeatForever::create(m_run));
}

void CEnemy::Stay()
{
	runAction(RepeatForever::create(m_stay));
}