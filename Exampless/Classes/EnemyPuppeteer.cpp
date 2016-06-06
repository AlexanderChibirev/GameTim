#include "EnemyPuppeteer.h"

USING_NS_CC;

namespace
{
const float AI_UPDATE_INTERVAL = 0.5f; // in seconds.
const float NEAR_DISTANCE = 100.f;
const float ENEMY_SPEED = 100.f;
}

CEnemyPuppeteer::CEnemyPuppeteer(Player * player, CCustomMap *customMap)
	: m_player(player)
	, m_customMap(customMap)
{

}

void CEnemyPuppeteer::SetPuppet(CEnemyPuppet *enemy)
{
    m_enemy = enemy;
	m_attack = enemy->GetAnim();
	m_sprite = enemy->GetSprite();
    if (m_enemy)
    {
        m_enemy->SetPuppeteer(this);
    }
}

void CEnemyPuppeteer::OnEnter()
{
}

void CEnemyPuppeteer::Update(float delta)
{
	m_sprite->runAction(RepeatForever::create(m_attack));//анимация
    m_timeSinceLastUpdate += delta;
	if (m_time > AI_UPDATE_INTERVAL*2)
	{
		m_sprite->stopAllActions();
	}
    if (m_timeSinceLastUpdate > AI_UPDATE_INTERVAL)
    {
        m_timeSinceLastUpdate = 0;
        UpdateAI();
    }
}

void CEnemyPuppeteer::OnExit()
{
}

cocos2d::Vec2 CEnemyPuppeteer::GetVelocity() const
{
    return m_velocity;
}

void CEnemyPuppeteer::UpdateAI()
{
    Vec2 heroPos = m_player->getPosition();
    Vec2 ownPos = m_enemy->getPosition();

    Vec2 directPath = heroPos - ownPos;
    if (directPath.getLength() < NEAR_DISTANCE)
    {
        float factor = std::min<float>(ENEMY_SPEED, directPath.getLength());
        m_velocity = directPath.getNormalized() * factor;
    }
    else if (m_customMap->CanWalkDirectlyForEnemy(ownPos, heroPos))
    {
		//m_enemy->
        m_velocity = directPath.getNormalized() * ENEMY_SPEED;
	}
    else
    {
        m_velocity = Vec2(0, 0);
    }
}
