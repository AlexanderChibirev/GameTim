#include "Legs.h"

using namespace cocos2d;
void Legs::initAnimations()
{
	SpriteFrameCache *sharedSpriteFrameCache = SpriteFrameCache::getInstance();
	auto animFrames = Vector<SpriteFrame*>(20);

	char str[100] = { 0 };
	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "survivor-run_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	this->m_run = Animate::create(animation);
	animFrames.clear();

	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "survivor-strafe_left_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	this->m_left = Animate::create(animation);
	animFrames.clear();

	for (int i = 0; i < 3; i++)
	{
		sprintf(str, "survivor-strafe_right_%02d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.05);
	this->m_right = Animate::create(animation);
}

Legs* Legs::create()
{
	Legs* pSprite = new Legs();
	pSprite->initAnimations();
	pSprite->m_state = stay;

	if (pSprite->initWithFile("survivor-idle_0.png"))
	{
		pSprite->autorelease();
		pSprite->Right();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

void Legs::Update(float dx, float dy)
{
	if (abs(dx) + abs(dy) != 0)
	{
		float angle = atan2(dy, dx);
		if (m_state != right && abs(angle) < 0.75 )
		{
			CCLOG("R");
			this->stopAllActions();
			this->Right();
			m_state = right;
		}
		else if (m_state != left && abs(angle) > 2.4)
		{
			CCLOG("L");
			this->stopAllActions();
			this->Left();
			m_state = left;
		}
		else if (m_state != run && (abs(angle) <= 2.4 && abs(angle) >= 0.75))
		{
			CCLOG("RUN");
			this->stopAllActions();
			this->Run();
			m_state = run;
		}
	}
	else
	{
		this->stopAllActions();
		m_state = stay;
	}
}



void Legs::Run()
{
	runAction(RepeatForever::create(m_run));
}

void Legs::Left()
{
	runAction(RepeatForever::create(m_left));
}

void Legs::Right()
{
	runAction(RepeatForever::create((m_left)->reverse()));
}

