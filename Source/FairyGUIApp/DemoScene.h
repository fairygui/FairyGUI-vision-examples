#ifndef __DEMO_SCENE_H__
#define __DEMO_SCENE_H__

#include "FairyGUI.h"

USING_NS_FGUI;

class DemoScene : public GComponent
{
public:
    DemoScene();
    virtual ~DemoScene();

protected:
    virtual void handleInit() override;
    virtual void continueInit();

    GRoot* _groot;

private:
    void onClose(EventContext* context);
};

#endif
