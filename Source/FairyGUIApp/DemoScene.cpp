#include "DemoScene.h"
#include "MenuScene.h"

#include <Vision/Runtime/Framework/VisionApp/VAppBase.hpp>

void DemoScene::handleInit()
{
    GComponent::handleInit();

    _groot = UIRoot;

    continueInit();

    //add a closebutton to scene
    GObject* closeButton = UIPackage::createObject("MainMenu", "CloseButton");
    closeButton->setPosition(_groot->getWidth() - closeButton->getWidth() - 10, _groot->getHeight() - closeButton->getHeight() - 10);
    closeButton->addRelation(_groot, RelationType::Right_Right);
    closeButton->addRelation(_groot, RelationType::Bottom_Bottom);
    closeButton->setSortingOrder(100000);
    closeButton->addClickListener(CALLBACK_1(DemoScene::onClose, this));

    _groot->addChild(closeButton);
}

void DemoScene::continueInit()
{
}

void DemoScene::onClose(EventContext* context)
{
    if (!dynamic_cast<MenuScene*>(this))
    {
        UIRoot->removeChildren();
        UIRoot->addChild(MenuScene::create());
    }
    else
    {
        VAppBase::Get()->Quit();
    }
}

DemoScene::DemoScene():_groot(nullptr)
{
}

DemoScene::~DemoScene()
{
}
