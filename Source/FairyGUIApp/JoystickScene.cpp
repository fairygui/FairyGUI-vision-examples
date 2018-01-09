#include "JoystickScene.h"



JoystickScene::~JoystickScene()
{
    CC_SAFE_RELEASE(_joystick);
}

void JoystickScene::continueInit()
{
    UIPackage::addPackage("UI/Joystick");

    _view = UIPackage::createObject("Joystick", "Main")->as<GComponent>();
    _groot->addChild(_view);

    _joystick = JoystickModule::create(_view);
    _joystick->retain();

    GObject* tf = _view->getChild("n9");

    _joystick->addListener(JoystickModule::MOVE, [tf](EventContext*context) {
        tf->setText(context->getDataValue().asString());
    });

    _joystick->addListener(JoystickModule::END, [tf](EventContext*context) {
        tf->setText("");
    });
}