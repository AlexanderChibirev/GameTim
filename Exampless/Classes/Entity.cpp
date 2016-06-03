#include "Entity.h"
#include "ui/CocosGUI.h" 
#include "MathAndLogic.h"



CEntity::CEntity()
	: m_damage(0)
	, m_health(0)
	, m_isLife(true)
{
}


CEntity::~CEntity()
{
}

void CEntity::Move(float dt)
{
	this->setPosition(MoveToward(this->getPosition(), dt));
}

void CEntity::SetHealthPoint(float health)
{
	m_health = health;
}

void CEntity::SetDamage(float damage)
{
	m_damage = damage;
}

float CEntity::GetDamage()
{
	return m_damage;
}
