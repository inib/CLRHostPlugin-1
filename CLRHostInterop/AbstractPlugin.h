#pragma once

#include "Plugin.h"
#include "API.h"

using namespace CLROBS;

namespace CLROBS 
{
    public ref class AbstractPlugin abstract : public Plugin
    {

    private:
        String^ pluginName;
        String^ pluginDescription;

    public:
        AbstractPlugin();
        ~AbstractPlugin();
    public:

        virtual bool LoadPlugin() { return true; };
        virtual void UnloadPlugin() {};
        virtual void OnStartStream() {};
        virtual void OnStopStream() {};
		virtual void OnOBSStatus(bool running, bool streaming, bool recording, bool previewing, bool reconnecting) {}
		virtual void OnSceneSwitch(System::String^ scene) {}
		virtual void OnMicVolumeChanged(float level, bool muted, bool finalValue) {}
		virtual void OnDesktopVolumeChanged(float level, bool muted, bool finalValue) {}

        property String^ Name
        {
        public:
            virtual String^ get() sealed;
        protected:
            void set(String^ name);
        }    
        property String^ Description 
        {
        public:
            virtual String^ get() sealed;
        protected:
            void set(String^ description);
        }
    };
};