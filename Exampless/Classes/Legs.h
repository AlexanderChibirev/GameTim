#pragma once
#include "cocos2d.h" 
#include <vector>
#include <map>

class Legs : public cocos2d::Sprite
{
public:
	static Legs *create();
	void Update(float dx, float dy);
private:
	void initAnimations();
	Legs() = default;

	void Run();
	void Left();
	void Right();
	cocos2d::RefPtr<cocos2d::Animate> m_run;
	cocos2d::RefPtr<cocos2d::Animate> m_left;
	cocos2d::RefPtr<cocos2d::Animate> m_right;


	enum state {run, stay, left, right} m_state;
};

