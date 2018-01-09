/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2015 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include "FairyGUIAppPCH.h"
#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>
#include <Vision/Runtime/Framework/VisionApp/Modules/VHelp.hpp>

#include "FairyGUI.h"
#include "MenuScene.h"

USING_NS_FGUI;

// Use the following line to initialize a plugin that is statically linked.
// Note that only Windows platform links plugins dynamically (on Windows you can comment out this line).
VIMPORT IVisPlugin_cl* GetEnginePlugin_FairyGUIEnginePlugin();

class FairyGUIApp : public VAppImpl
{
public:
    FairyGUIApp() {}
    virtual ~FairyGUIApp() {}

    virtual void SetupAppConfig(VisAppConfig_cl& config) HKV_OVERRIDE;

    virtual void Init() HKV_OVERRIDE;
    virtual void AfterSceneLoaded(bool bLoadingSuccessful) HKV_OVERRIDE;
    virtual bool Run() HKV_OVERRIDE;
    virtual void DeInit() HKV_OVERRIDE;
};

VAPP_IMPLEMENT_SAMPLE(FairyGUIApp);

void FairyGUIApp::SetupAppConfig(VisAppConfig_cl& config)
{
    // Set custom file system root name ("havok_sdk" by default)
    config.m_sFileSystemRootName = "workspace";

    // Set the initial starting position of our game window and other properties
    // if not in fullscreen. This is only relevant on windows
#if defined(WIN32)
    config.m_videoConfig.m_iXRes = 1136; // Set the Window size X if not in fullscreen.
    config.m_videoConfig.m_iYRes = 640;  // Set the Window size Y if not in fullscreen.
    config.m_videoConfig.m_iXPos = 50;   // Set the Window position X if not in fullscreen.
    config.m_videoConfig.m_iYPos = 50;   // Set the Window position Y if not in fullscreen.

    // Fullscreen mode with current desktop resolution
    /*
    DEVMODEA deviceMode;
    deviceMode = Vision::Video.GetAdapterMode(config.m_videoConfig.m_iAdapter);
    config.m_videoConfig.m_iXRes = deviceMode.dmPelsWidth;
    config.m_videoConfig.m_iYRes = deviceMode.dmPelsHeight;
    config.m_videoConfig.m_bFullScreen = true;
    */
#endif
    // Name to be displayed in the windows title bar.
    config.m_videoConfig.m_szWindowTitle = "FairyGUI";

    config.m_videoConfig.m_bWaitVRetrace = true;
}

//---------------------------------------------------------------------------------------------------------
// Init function. Here we trigger loading our scene
//---------------------------------------------------------------------------------------------------------
void FairyGUIApp::Init()
{
    // Use the following line to load a plugin. Remember that, except on Windows platform, in addition
    // you still need to statically link your plugin library (e.g. on mobile platforms) through project
    // Properties, Linker, Additional Dependencies.
    VISION_PLUGIN_ENSURE_LOADED(FairyGUIEnginePlugin);

    // Set filename and paths to our stand alone version.
    // Note: "/Data/Vision/Base" is always added by the sample framework
    VisAppLoadSettings settings("Scenes/Default.vscene");
    settings.m_customSearchPaths.Append(":workspace/Assets");
    LoadScene(settings);

    FGUIManager::GlobalManager().registerFont("<default>", "Fonts/YaHei.fnt", 22, true);
    FGUIManager::GlobalManager().setShowCursor(true);

    UIRoot->setContentScaleFactor(1136, 640);

    UIRoot->addChild(MenuScene::create());
}

//---------------------------------------------------------------------------------------------------------
// Gets called after the scene has been loaded
//---------------------------------------------------------------------------------------------------------
void FairyGUIApp::AfterSceneLoaded(bool bLoadingSuccessful)
{
    // Define some help text
    VArray<const char*> help;
    help.Append("How to use this demo...");
    help.Append("");
    RegisterAppModule(new VHelp(help));

    // Create a free camera (set above the ground so that we can see the ground)
    //Vision::Game.CreateEntity("VFreeCamera", hkvVec3(0.0f, 0.0f, 170.0f));
    
    // Add other initial game code here
}

//---------------------------------------------------------------------------------------------------------
// Main Loop of the application until we quit
//---------------------------------------------------------------------------------------------------------
bool FairyGUIApp::Run()
{
    return true;
}

void FairyGUIApp::DeInit()
{
    // De-Initialization
    // [...]
}

/*
 * Havok SDK - Base file, BUILD(#20150320)
 *
 * Confidential Information of Havok.  (C) Copyright 1999-2015
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 *
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available from salesteam@havok.com.
 *
 */

