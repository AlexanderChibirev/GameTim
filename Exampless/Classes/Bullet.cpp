#include "Bullet.h"

CBullet * CBullet::create(MovementDirection const& direction, cocos2d::Point const& position)

{
	CBullet* pSprite = new CBullet();
	pSprite->setPosition(position);
	pSprite->SetDirection(direction);


	if (pSprite->initWithFile("bullet.png"))
	{
		pSprite->autorelease();

		pSprite->initOptions();

		//	pSprite->runAction(RepeatForever::create(Animate::create(pSprite->stayWithKnife)));
		return pSprite;
	}



	CC_SAFE_DELETE(pSprite);
	return nullptr;
}


void CBullet::Update(float dt)
{
	Move(dt);
}

void CBullet::initOptions()
{
	this->SetSpeed(1000);
	this->SetDamage(10);
	this->SetHealthPoint(1);
	this->schedule(schedule_selector(CBullet::Update), 1 / 60);
}

CBullet::CBullet() = default;
