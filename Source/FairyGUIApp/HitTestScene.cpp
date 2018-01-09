#include "HitTestScene.h"



void HitTestScene::continueInit()
{
    UIPackage::addPackage("UI/HitTest");

    _view = UIPackage::createObject("HitTest", "Main")->as<GComponent>();
    _groot->addChild(_view);
}