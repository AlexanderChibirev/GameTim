#pragma once
#include "cocos_custom.h"
//#include "InputController.h"
#include "IPuppeteer.h"
//#include "IGameWorld.h"
#include "EnemyPuppet.h"
#include "Player.h"
#include "CustomMap.h"

class CEnemyPuppeteer : protected IPuppeteer
{
public:
    CEnemyPuppeteer(Player * player, CCustomMap *customMap);

    void SetPuppet(CEnemyPuppet *enemy);

protected:
    void OnEnter() override;
    void Update(float delta) override;
    void OnExit() override;
    cocos2d::Vec2 GetVelocity() const override;

private:
	enum ActionState
	{
		stay = 0,
		fly,
		attack,
		none,
	};
	ActionState m_actionState;
    void UpdateAI();
	Player *m_player;
	CCustomMap *m_customMap;
    //IGameWorld & m_world;
    CPuppetPtr m_enemy;
   // std::unique_ptr<CInputController> m_controller;
    float m_timeSinceLastUpdate = 0;
	float m_time = 0;
    cocos2d::Vec2 m_velocity;
	cocos2d::RefPtr<Animate> m_attack;
	cocos2d::Sprite *m_sprite;
};

typedef std::unique_ptr<CEnemyPuppeteer> CEnemyPuppeteerPtr;
