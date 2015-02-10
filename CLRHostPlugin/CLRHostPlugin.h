/**
* John Bradley (jrb@turrettech.com)
*/
#pragma once

#include "OBSApi.h"

class CLRPlugin;
class CLRHostPlugin;
class CLRHostApi;
class CLRHost;

#include <vector>

#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

class CLRHostPlugin
{

public:
    static HINSTANCE hinstDLL;
    static CLRHostPlugin *instance;

private:
    bool isDynamicLocale;
    CLRHostApi *clrApi;
    CLRHost *clrHost;

    std::vector<CLRPlugin *> clrPlugins;

public:
    CLRHostPlugin();
    ~CLRHostPlugin();

public:
    CLRHost *GetCLRHost() { return clrHost; }
    CLRHostApi *GetCLRApi() { return clrApi; }

public:
    void LoadPlugins();
    void UnloadPlugins();
    void OnStartStream();
    void OnStopStream();
	void OnOBSStatus(bool running, bool streaming, bool recording, bool previewing, bool reconnecting);
	void OnMicVolumeChanged(float level, bool muted, bool finalValue);
	void OnDesktopVolumeChanged(float level, bool muted, bool finalValue);
	void OnSceneSwitch(CTSTR scene);

};

EXTERN_DLL_EXPORT bool LoadPlugin();
EXTERN_DLL_EXPORT void UnloadPlugin();
EXTERN_DLL_EXPORT void OnStartStream();
EXTERN_DLL_EXPORT void OnStopStream();
EXTERN_DLL_EXPORT void OnSceneSwitch(CTSTR scene);
EXTERN_DLL_EXPORT void OnOBSStatus(bool running, bool streaming, bool recording, bool previewing, bool reconnecting);
EXTERN_DLL_EXPORT void OnMicVolumeChanged(float level, bool muted, bool finalValue);
EXTERN_DLL_EXPORT void OnDesktopVolumeChanged(float level, bool muted, bool finalValue);
EXTERN_DLL_EXPORT CTSTR GetPluginName();
EXTERN_DLL_EXPORT CTSTR GetPluginDescription();
