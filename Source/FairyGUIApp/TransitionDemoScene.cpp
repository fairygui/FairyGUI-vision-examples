#include "TransitionDemoScene.h"



TransitionDemoScene::~TransitionDemoScene()
{
    CC_SAFE_RELEASE(_g1);
    CC_SAFE_RELEASE(_g2);
    CC_SAFE_RELEASE(_g3);
    CC_SAFE_RELEASE(_g4);
    CC_SAFE_RELEASE(_g5);
}

void TransitionDemoScene::continueInit()
{
    UIPackage::addPackage("UI/Transition");
    _view = UIPackage::createObject("Transition", "Main")->as<GComponent>();
    _groot->addChild(_view);

    _btnGroup = _view->getChild("g0")->as<GGroup>();

    _g1 = UIPackage::createObject("Transition", "BOSS")->as<GComponent>();
    _g1->retain();
    _g2 = UIPackage::createObject("Transition", "BOSS_SKILL")->as<GComponent>();
    _g2->retain();
    _g3 = UIPackage::createObject("Transition", "TRAP")->as<GComponent>();
    _g3->retain();
    _g4 = UIPackage::createObject("Transition", "GoodHit")->as<GComponent>();
    _g4->retain();
    _g5 = UIPackage::createObject("Transition", "PowerUp")->as<GComponent>();
    _g5->retain();
    _g5->getTransition("t0")->setHook("play_num_now", CALLBACK_0(TransitionDemoScene::playNum, this));

    _view->getChild("btn0")->addClickListener([this](EventContext*) { __play(_g1); });
    _view->getChild("btn1")->addClickListener([this](EventContext*) { __play(_g2); });
    _view->getChild("btn2")->addClickListener([this](EventContext*) { __play(_g3); });
    _view->getChild("btn3")->addClickListener(CALLBACK_1(TransitionDemoScene::__play4, this));
    _view->getChild("btn4")->addClickListener(CALLBACK_1(TransitionDemoScene::__play5, this));
}

void TransitionDemoScene::__play(GComponent* target)
{
    _btnGroup->setVisible(false);
    _groot->addChild(target);
    Transition* t = target->getTransition("t0");
    t->play([this, target]()
    {
        _btnGroup->setVisible(true);
        _groot->removeChild(target);
    });
}

void TransitionDemoScene::__play4(EventContext* context)
{
    _btnGroup->setVisible(false);
    _g4->setPosition(_groot->getWidth() - _g4->getWidth() - 20, 100);
    _groot->addChild(_g4);
    Transition* t = _g4->getTransition("t0");
    t->play(3, 0, [this]()
    {
        _btnGroup->setVisible(true);
        _groot->removeChild(_g4);
    });
}

void TransitionDemoScene::__play5(EventContext* context)
{
    _btnGroup->setVisible(false);
    _g5->setPosition(20, _groot->getHeight() - _g5->getHeight() - 100);
    _groot->addChild(_g5);
    Transition* t = _g5->getTransition("t0");
    _startValue = 10000;
    int add = 1000 + rand_0_1() * 2000;
    _endValue = _startValue + add;
    _g5->getChild("value")->setText(Value(_startValue).asString());
    _g5->getChild("add_value")->setText(Value(add).asString());
    t->play([this]()
    {
        _btnGroup->setVisible(true);
        _groot->removeChild(_g5);
    });
}

void TransitionDemoScene::playNum()
{
    ActionFloat* action = ActionFloat::create(0.3f, _startValue, _endValue, [this](float value)
    {
        _g5->getChild("value")->setText(Value((int)value).asString());
    });
    _view->runAction(action);
}
