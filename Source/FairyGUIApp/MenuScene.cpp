#include "MenuScene.h"
#include "BasicsScene.h"
#include "TransitionDemoScene.h"
#include "VirtualListScene.h"
#include "LoopListScene.h"
#include "HitTestScene.h"
#include "PullToRefreshScene.h"
#include "ModalWaitingScene.h"
#include "JoystickScene.h"
#include "BagScene.h"
#include "ChatScene.h"
#include "ListEffectScene.h"
#include "ScrollPaneScene.h"
#include "TreeViewScene.h"

void MenuScene::continueInit()
{
    UIPackage::addPackage("UI/MainMenu");
    _view = UIPackage::createObject("MainMenu", "Main")->as<GComponent>();
    UIRoot->addChild(_view);

    _view->getChild("n1")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(BasicsScene::create());
    });
    _view->getChild("n2")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(TransitionDemoScene::create());
    });
    _view->getChild("n4")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(VirtualListScene::create());
    });
    _view->getChild("n5")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(LoopListScene::create());
    });
    _view->getChild("n6")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(HitTestScene::create());
    });
    _view->getChild("n7")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(PullToRefreshScene::create());
    });
    _view->getChild("n8")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(ModalWaitingScene::create());
    });
    _view->getChild("n9")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(JoystickScene::create());
    });
    _view->getChild("n10")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(BagScene::create());
    });
    _view->getChild("n11")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(ChatScene::create());
    });
    _view->getChild("n12")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(ListEffectScene::create());
    });
    _view->getChild("n13")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(ScrollPaneScene::create());
    });
    _view->getChild("n14")->addClickListener([this](EventContext*)
    {
        UIRoot->removeChildren();
        UIRoot->addChild(TreeViewScene::create());
    });
}