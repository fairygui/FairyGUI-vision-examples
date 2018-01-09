#include "JoystickModule.h"

JoystickModule * JoystickModule::create(GComponent * mainView)
{
    JoystickModule *pRet = new JoystickModule();
    if (pRet && pRet->init(mainView))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool JoystickModule::init(GComponent * mainView)
{
    _button = mainView->getChild("joystick")->as<GButton>();
    _button->setChangeStateOnClick(false);

    _thumb = _button->getChild("thumb");
    _touchArea = mainView->getChild("joystick_touch");
    _center = mainView->getChild("joystick_center");

    _InitX = _center->getX() + _center->getWidth() / 2;
    _InitY = _center->getY() + _center->getHeight() / 2;
    touchId = -1;
    _radius = 150;

    _touchArea->addListener(UIEventType::TouchBegin, CALLBACK_1(JoystickModule::onTouchBegin, this));
    _touchArea->addListener(UIEventType::TouchMove, CALLBACK_1(JoystickModule::onTouchMove, this));
    _touchArea->addListener(UIEventType::TouchEnd, CALLBACK_1(JoystickModule::onTouchEnd, this));

    return true;
}

void JoystickModule::onTouchBegin(EventContext * context)
{
    if (touchId == -1)//First touch
    {
        InputEvent* evt = (InputEvent*)context->getInput();
        touchId = evt->getTouchId();

        _button->displayObject()->stopActionByTag(1);

        hkvVec2 pt = UIRoot->globalToLocal(evt->getPosition());
        float bx = pt.x;
        float by = pt.y;
        _button->setSelected(true);

        if (bx < 0)
            bx = 0;
        else if (bx > _touchArea->getWidth())
            bx = _touchArea->getWidth();

        if (by > UIRoot->getHeight())
            by = UIRoot->getHeight();
        else if (by < _touchArea->getY())
            by = _touchArea->getY();

        _lastStageX = bx;
        _lastStageY = by;
        _startStageX = bx;
        _startStageY = by;

        _center->setVisible(true);
        _center->setPosition(bx - _center->getWidth() / 2, by - _center->getHeight() / 2);
        _button->setPosition(bx - _button->getWidth() / 2, by - _button->getHeight() / 2);

        float deltaX = bx - _InitX;
        float deltaY = by - _InitY;
        float degrees = atan2(deltaY, deltaX) * 180 / hkvMath::pi();
        _thumb->setRotation(degrees + 90);

        context->captureTouch();
    }
}

void JoystickModule::onTouchMove(EventContext * context)
{
    InputEvent* evt = (InputEvent*)context->getInput();
    if (touchId != -1 && evt->getTouchId() == touchId)
    {
        hkvVec2 pt = UIRoot->globalToLocal(evt->getPosition());
        float bx = pt.x;
        float by = pt.y;
        float moveX = bx - _lastStageX;
        float moveY = by - _lastStageY;
        _lastStageX = bx;
        _lastStageY = by;
        float buttonX = _button->getX() + moveX;
        float buttonY = _button->getY() + moveY;

        float offsetX = buttonX + _button->getWidth() / 2 - _startStageX;
        float offsetY = buttonY + _button->getHeight() / 2 - _startStageY;

        float rad = atan2(offsetY, offsetX);
        float degree = rad * 180 / hkvMath::pi();
        _thumb->setRotation(degree + 90);

        float maxX = _radius * cos(rad);
        float maxY = _radius * sin(rad);
        if (std::abs(offsetX) > std::abs(maxX))
            offsetX = maxX;
        if (std::abs(offsetY) > std::abs(maxY))
            offsetY = maxY;

        buttonX = _startStageX + offsetX;
        buttonY = _startStageY + offsetY;
        if (buttonX < 0)
            buttonX = 0;
        if (buttonY > UIRoot->getHeight())
            buttonY = UIRoot->getHeight();

        _button->setPosition(buttonX - _button->getWidth() / 2, buttonY - _button->getHeight() / 2);

        dispatchEvent(MOVE, nullptr, Value(degree));
    }
}

void JoystickModule::onTouchEnd(EventContext * context)
{
    InputEvent* evt = (InputEvent*)context->getInput();
    if (touchId != -1 && evt->getTouchId() == touchId)
    {
        touchId = -1;
        _thumb->setRotation(_thumb->getRotation() + 180);
        _center->setVisible(false);

        Action* action = Sequence::createWithTwoActions(ActionFloat2::create(0.3f,
            _button->getPosition(),
            hkvVec2(_InitX - _button->getWidth() / 2, _InitY - _button->getHeight() / 2), CALLBACK_2(GObject::setPosition, _button)),
        CallFunc::create([this]()
        {
            _button->setSelected(false);
            _thumb->setRotation(0);
            _center->setVisible(true);
            _center->setPosition(_InitX - _center->getWidth() / 2, _InitY - _center->getHeight() / 2);
        }));
        action->setTag(1);

        _button->runAction(action);
        dispatchEvent(END);
    }
}
