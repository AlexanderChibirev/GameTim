#pragma once
#include "cocos2d.h"
#include "Joystick.h"
#include "Player.h"

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	bool onTouchBegan(Touch* pTouches, Event* event);


	void SetJoystick(Joystick *joy) { m_joy = joy; };
	void ChooseGun(cocos2d::Ref *sender);

	Joystick *m_joy;
	//Joystick *m_joyR;

	Player *m_player;
};

