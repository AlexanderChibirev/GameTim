#include "InputController.h"

USING_NS_CC;

namespace
{
const int FIXED_EVENT_PRIORITY = 100;

EventDispatcher *getEvents()
{
    return Director::getInstance()->getEventDispatcher();
}
}

CInputController::CInputController(const Vec2 &maxSpeed)
    : m_maxSpeed(maxSpeed)
{
    m_keyboard = EventListenerKeyboard::create();
    m_keyboard->onKeyPressed = CC_CALLBACK_2(CInputController::OnKeyPressed, this);
    m_keyboard->onKeyReleased = CC_CALLBACK_2(CInputController::OnKeyReleased, this);
    getEvents()->addEventListenerWithFixedPriority(m_keyboard, FIXED_EVENT_PRIORITY);
}

CInputController::~CInputController()
{
    getEvents()->removeEventListener(m_keyboard);
}

Vec2 CInputController::GetSpeed() const
{
    if (m_speed != Vec2(0, 0))
    {
        return m_speed;
    }
    return m_speed;
}

void CInputController::Update()
{
    cocos2d::Vec2 speed;
    if (m_pressedKeyW)
    {
        speed.y = +1.f;
    }
    if (m_pressedKeyA)
    {
        speed.x = -1.f;
    }
    if (m_pressedKeyS)
    {
        speed.y = -1.f;
    }
    if (m_pressedKeyD)
    {
        speed.x = +1.f;
    }
    speed.normalize();
    speed.scale(m_maxSpeed);
    m_speed = speed;
}

void CInputController::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    (void)event;
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_W:
        m_pressedKeyW = true;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        m_pressedKeyA = true;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        m_pressedKeyS = true;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        m_pressedKeyD = true;
        break;
    default:
        return;
    }
    Update();
}

void CInputController::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    (void)event;

    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_W:
        m_pressedKeyW = false;
        break;
    case EventKeyboard::KeyCode::KEY_A:
        m_pressedKeyA = false;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        m_pressedKeyS = false;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        m_pressedKeyD = false;
        break;
    default:
        return;
    }
    Update();
}
