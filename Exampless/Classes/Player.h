#pragma once
#include "cocos2d.h" 
#include "Joystick.h"
#include "Entity.h"
#include "Legs.h"
#include <vector>
#include <map>

class Player : public CEntity
{
public:
	static Player *create(Joystick *moveJoy,/* Joystick *rotateJoy*/ Legs * legs);
	void Update(float dt) override;
	void Shoot(cocos2d::Layer *layer);
	void ChooseNextGun();
	void Run();
	void Stay();
private:
	enum state {stay, run} m_state;

	Player();
	void initOptions();
	void SetState(double const& move);

	void initKnifeAnimations();
	void initPistolAnimations();

	Joystick * m_moveController;
	//Joystick * m_rotateController;
	Legs * m_legs;

	enum CurrentGun { Knife, Pistol } m_gun;

	std::map<CurrentGun, std::vector<cocos2d::RefPtr<Animate>>> m_states;
	std::vector<cocos2d::RefPtr<Animate>> m_currentState;

	cocos2d::RefPtr<Animate> stayWithKnife;
	cocos2d::RefPtr<Animate> runWithKnife;
	cocos2d::RefPtr<Animate> m_currentAction;
	MovementDirection m_shootDirection;
	bool m_isShooting;
	//Vector<SpriteFrame*> animFrames;
};

