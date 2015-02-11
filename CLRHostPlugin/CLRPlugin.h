#pragma once

#include "CLRObject.h"
#include "CLRObjectRef.h"

#include <string>

namespace mscorlib {
    struct _EventInfo;
    struct _MethodInfo;
}

class CLRPlugin : public CLRObject
{
protected:
    mscorlib::_MethodInfo *loadPluginMethod;
    mscorlib::_MethodInfo *unloadPluginMethod;
    mscorlib::_MethodInfo *onStartStreamMethod;
    mscorlib::_MethodInfo *onStopStreamMethod;
	mscorlib::_MethodInfo *onSceneSwitchMethod;
	mscorlib::_MethodInfo *onOBSStatusMethod;
	mscorlib::_MethodInfo *onMicVolumeChangedMethod;
	mscorlib::_MethodInfo *onDesktopVolumeChangedMethod;
    mscorlib::_MethodInfo *getPluginNameMethod;
    mscorlib::_MethodInfo *getPluginDescriptionMethod;

public:
    virtual bool Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType);
    virtual void Detach();

public:
    bool LoadPlugin();
    void UnloadPlugin();
    void OnStartStream();
    void OnStopStream();
	void OnSceneSwitch(CTSTR scene);
	void OnOBSStatus(bool running, bool streaming, bool recording, bool previewing, bool reconnecting);
	void OnMicVolumeChanged(float level, bool muted, bool finalValue);
	void OnDesktopVolumeChanged(float level, bool muted, bool finalValue);
    std::wstring GetPluginName();
    std::wstring GetPluginDescription();
};