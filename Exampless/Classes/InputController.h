#pragma once
#include "cocos_custom.h"

class CInputController
{
public:
    using PositionHandler = std::function<void(const cocos2d::Vec2 &)>;

    CInputController(const cocos2d::Vec2 &maxSpeed);
    ~CInputController();

    cocos2d::Vec2 GetSpeed() const;

private:
    void Update();
    void OnKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
    void OnKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);

    bool m_pressedKeyW = false;
    bool m_pressedKeyA = false;
    bool m_pressedKeyS = false;
    bool m_pressedKeyD = false;
    cocos2d::RefPtr<cocos2d::EventListenerKeyboard> m_keyboard;
    cocos2d::Vec2 m_speed;
    const cocos2d::Vec2 m_maxSpeed;
};


