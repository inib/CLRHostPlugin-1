#pragma once

#include "API.h"

using namespace System;
using namespace CLROBS;

namespace CLROBS {
    public interface class Plugin
    {

        virtual bool LoadPlugin() = 0;
        virtual void UnloadPlugin() = 0;
        virtual void OnStartStream() = 0;
        virtual void OnStopStream() = 0;
		virtual void OnSceneSwitch(System::String^ scene) = 0;
		virtual void OnOBSStatus(bool running, bool streaming, bool recording, bool previewing, bool reconnecting) = 0;
		virtual void OnMicVolumeChanged(float level, bool muted, bool finalValue) = 0;
		virtual void OnDesktopVolumeChanged(float level, bool muted, bool finalValue) = 0;

        property System::String^ Name {
            virtual System::String^ get();
        }
        property System::String^ Description {
            virtual System::String^ get();
        }
    };
};