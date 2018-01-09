#include "PullToRefreshScene.h"



class ScrollPaneHeader : public GComponent
{
public:
    CREATE_FUNC(ScrollPaneHeader);

    bool isReadyToRefresh()
    {
        return _c1->getSelectedIndex() == 1;
    }
    void setRefreshStatus(int value);
protected:
    virtual void constructFromXML(TXMLElement*);
private:
    void onSizeChanged(EventContext*);

    GController* _c1;
};

void ScrollPaneHeader::constructFromXML(TXMLElement* xml)
{
    GComponent::constructFromXML(xml);

    _c1 = getController("c1");

    addListener(UIEventType::SizeChange, CALLBACK_1(ScrollPaneHeader::onSizeChanged, this));
}

void ScrollPaneHeader::onSizeChanged(EventContext*)
{
    if (_c1->getSelectedIndex() == 2 || _c1->getSelectedIndex() == 3)
        return;

    if (getHeight() > sourceSize.y)
        _c1->setSelectedIndex(1);
    else
        _c1->setSelectedIndex(0);
}

void ScrollPaneHeader::setRefreshStatus(int value)
{
    _c1->setSelectedIndex(value);
}

void PullToRefreshScene::continueInit()
{
    UIPackage::addPackage("UI/PullToRefresh");
    UIObjectFactory::setPackageItemExtension("ui://PullToRefresh/Header", []() {return ScrollPaneHeader::create(); });

    _view = UIPackage::createObject("PullToRefresh", "Main")->as<GComponent>();
    _groot->addChild(_view);

    _list1 = _view->getChild("list1")->as<GList>();
    _list1->itemRenderer = CALLBACK_2(PullToRefreshScene::renderListItem1, this);
    _list1->setVirtual();
    _list1->setNumItems(1);
    _list1->addListener(UIEventType::PullDownRelease, CALLBACK_1(PullToRefreshScene::onPullDownToRefresh, this));

    _list2 = _view->getChild("list2")->as<GList>();
    _list2->itemRenderer = CALLBACK_2(PullToRefreshScene::renderListItem2, this);
    _list2->setVirtual();
    _list2->setNumItems(1);
    _list2->addListener(UIEventType::PullUpRelease, CALLBACK_1(PullToRefreshScene::onPullUpToRefresh, this));
}

void PullToRefreshScene::renderListItem1(int index, GObject* obj)
{
    obj->setText("Item " + Value(_list1->getNumItems() - index - 1).asString());
}

void PullToRefreshScene::renderListItem2(int index, GObject* obj)
{
    obj->setText("Item " + Value(index).asString());
}

void PullToRefreshScene::onPullDownToRefresh(EventContext*)
{
    ScrollPaneHeader* header = dynamic_cast<ScrollPaneHeader*>(_list1->getScrollPane()->getHeader());
    if (header->isReadyToRefresh())
    {
        header->setRefreshStatus(2);
        _list1->getScrollPane()->lockHeader(header->sourceSize.y);

        //Simulate a async resquest
        this->scheduleOnce([header, this](float)
        {
            _list1->setNumItems(_list1->getNumItems() + 5);

            //Refresh completed
            header->setRefreshStatus(3);
            _list1->getScrollPane()->lockHeader(35);

            this->scheduleOnce([header, this](float)
            {
                header->setRefreshStatus(0);
                _list1->getScrollPane()->lockHeader(0);
            }, 2, "pull_down2");
        }, 2, "pull_down1");
    }
}

void PullToRefreshScene::onPullUpToRefresh(EventContext*)
{
    GComponent* footer = dynamic_cast<GComponent*>(_list2->getScrollPane()->getFooter());

    footer->getController("c1")->setSelectedIndex(1);
    _list2->getScrollPane()->lockFooter(footer->sourceSize.y);

    //Simulate a async resquest
    this->scheduleOnce([footer, this](float)
    {
        _list2->setNumItems(_list2->getNumItems() + 5);

        //Refresh completed
        footer->getController("c1")->setSelectedIndex(0);
        _list2->getScrollPane()->lockFooter(0);
    }, 2, "pull_up");
}