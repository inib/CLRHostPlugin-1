/**
* John Bradley (jrb@turrettech.com)
*/
#include "stdafx.h"

#include "Localization.h"
#include "CLRHostPlugin.h"
#include "CLRHostApi.h"
#include "CLRHost.h"

HINSTANCE CLRHostPlugin::hinstDLL = NULL;
CLRHostPlugin *CLRHostPlugin::instance = NULL;

CLRHostPlugin::CLRHostPlugin() {

    CLRHostPlugin::instance = this;

    isDynamicLocale = false;

    if (!locale->HasLookup(KEY("PluginName"))) {
        isDynamicLocale = true;
        int localizationStringCount = sizeof(localizationStrings) / sizeof(CTSTR);
        Log(TEXT("CLR host plugin strings not found, dynamically loading %d strings"), sizeof(localizationStrings) / sizeof(CTSTR));
        for(int i = 0; i < localizationStringCount; i += 2) {
            locale->AddLookupString(localizationStrings[i], localizationStrings[i+1]);
        }
        if (!locale->HasLookup(KEY("PluginName"))) {
            AppWarning(TEXT("Uh oh..., unable to dynamically add our localization keys"));
        }
    }

    clrApi = new CLRHostApi();
    clrHost = new CLRHost(nullptr, clrApi);
    clrHost->Initialize();     
}

CLRHostPlugin::~CLRHostPlugin() {

    if (isDynamicLocale) {
        int localizationStringCount = sizeof(localizationStrings) / sizeof(CTSTR);
        Log(TEXT("CLR host plugin instance deleted; removing dynamically loaded localization strings"));
        for(int i = 0; i < localizationStringCount; i += 2) {
            locale->RemoveLookupString(localizationStrings[i]);
        }
    }

    isDynamicLocale = false;

    if (clrHost) {
        delete clrHost;
        clrHost = nullptr;
    }

    if (clrApi) {
        delete clrApi;
        clrApi = nullptr;
    }

}

void CLRHostPlugin::LoadPlugins()
{

    if (clrHost->LoadInteropLibrary()) {
        clrHost->LoadPlugins();
    }
}

void CLRHostPlugin::UnloadPlugins()
{
    clrHost->UnloadPlugins();
}

void CLRHostPlugin::OnStartStream()
{ 
    clrHost->OnStartStream();
}

void CLRHostPlugin::OnStopStream()
{
    clrHost->OnStopStream();
}

void CLRHostPlugin::OnSceneSwitch(CTSTR scene)
{
	clrHost->OnSceneSwitch(scene);
}

void CLRHostPlugin::OnOBSStatus(bool running, bool streaming, bool recording, bool previewing, bool reconnecting)
{
	clrHost->OnOBSStatus(running, streaming, recording, previewing, reconnecting);
}

void CLRHostPlugin::OnMicVolumeChanged(float level, bool muted, bool finalValue)
{
	clrHost->OnMicVolumeChanged(level, muted, finalValue);
}

void CLRHostPlugin::OnDesktopVolumeChanged(float level, bool muted, bool finalValue)
{
	clrHost->OnDesktopVolumeChanged(level, muted, finalValue);
}

bool LoadPlugin()
{
    if(CLRHostPlugin::instance != NULL) {
        return false;
    }
    CLRHostPlugin::instance = new CLRHostPlugin();
    CLRHostPlugin::instance->LoadPlugins();
    return true;
}

void UnloadPlugin()
{
    if(CLRHostPlugin::instance == NULL) {
        return;
    }

    CLRHostPlugin::instance->UnloadPlugins();
    delete CLRHostPlugin::instance;
    CLRHostPlugin::instance = NULL;
}

void OnStartStream()
{
    if(CLRHostPlugin::instance == NULL) {
        return;
    }
    CLRHostPlugin::instance->OnStartStream();
}

void OnStopStream()
{
    if(CLRHostPlugin::instance == NULL) {
        return;
    }
    CLRHostPlugin::instance->OnStopStream();
}

void OnOBSStatus(bool running, bool streaming, bool recording, bool previewing, bool reconnecting)
{
	if (CLRHostPlugin::instance == NULL) {
		return;
	}
	CLRHostPlugin::instance->OnOBSStatus(running, streaming, recording, previewing, reconnecting);
}

void OnSceneSwitch(CTSTR scene)
{
	if (CLRHostPlugin::instance == NULL) {
		return;
	}
	CLRHostPlugin::instance->OnSceneSwitch(scene);
}

void OnMicVolumeChanged(float level, bool muted, bool finalValue)
{
	if (CLRHostPlugin::instance == NULL) {
		return;
	}
	CLRHostPlugin::instance->OnMicVolumeChanged(level, muted, finalValue);
}

void OnDesktopVolumeChanged(float level, bool muted, bool finalValue)
{
	if (CLRHostPlugin::instance == NULL) {
		return;
	}
	CLRHostPlugin::instance->OnDesktopVolumeChanged(level, muted, finalValue);
}

CTSTR GetPluginName()
{
    return STR("PluginName");
}

CTSTR GetPluginDescription()
{
    return STR("PluginDescription");
}

BOOL CALLBACK DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if(fdwReason == DLL_PROCESS_ATTACH) {
        CLRHostPlugin::hinstDLL = hinstDLL;
    }
    return TRUE;
}
