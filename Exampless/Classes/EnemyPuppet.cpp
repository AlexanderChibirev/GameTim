#include "EnemyPuppet.h"
//#include "Resources.h"

USING_NS_CC;

bool CEnemyPuppet::init(IMapPhysics &mapPhysics)
{
    if (!CPuppet::init(mapPhysics))
    {
        return false;
    }
    m_body = Sprite::create("enemyFly_1.png");

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
	//this->stayWithKnife = Animate::create(animation);
	animationsVector.push_back(Animate::create(animation));
	animFrames.clear();

	for (int i = 1; i < 8; i++)
	{
		sprintf(str, "enemyFly_%d.png", i);
		SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		frame->setOffset(m_body->getOffsetPosition());
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, 0.7);
	animationsVector.push_back(Animate::create(animation));
	m_attack = Animate::create(animation);
    return true;
}

cocos2d::RefPtr<cocos2d::Sprite> CEnemyPuppet::GetSprite()
{
	return m_body;
}

void CEnemyPuppet::onEnter()
{
    CPuppet::onEnter();
    addChild(m_body);
}

void CEnemyPuppet::onExit()
{
    m_body->removeFromParentAndCleanup(true);
    CPuppet::onExit();
}

cocos2d::RefPtr<Animate> CEnemyPuppet::GetAnim()
{
	return m_attack;
}