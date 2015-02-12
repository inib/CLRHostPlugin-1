#include "OBSApi.h"
#include "API.h"
#include "CLRHostApi.h"
#include "OBSUtils.h"

using namespace System::Runtime::InteropServices;

void API::AddSettingsPane(CLROBS::SettingsPane^ settingsPane)
{
    System::IntPtr unkRef = Marshal::GetIUnknownForObject(settingsPane);
    CLRObjectRef objectRef(unkRef.ToPointer(), nullptr);
    clrHostApi->AddSettingsPane(objectRef);
}

void API::AddImageSourceFactory(CLROBS::ImageSourceFactory^ imageSourceFactory)
{
    System::IntPtr unkRef = Marshal::GetIUnknownForObject(imageSourceFactory);
    CLRObjectRef objectRef(unkRef.ToPointer(), nullptr);
    clrHostApi->AddImageSourceFactory(objectRef);
}

System::IntPtr API::GetMainWindowHandle()
{
    return System::IntPtr(::API->GetMainWindow());
}

void API::Log(System::String^ format, ...array<System::Object^> ^arguments)
{
    System::String ^formattedString = System::String::Format(format, arguments);
    ::Log(L"CLRHost:: %s", ToWString(formattedString).c_str());
}

System::String^ API::GetPluginDataPath()
{
    return gcnew System::String(OBSGetPluginDataPath().Array());
}

void API::SetChangedSettings(bool isChanged)
{
    ::API->SetChangedSettings(isChanged);
}

int API::GetMaxFPS()
{
    return ::API->GetMaxFPS();
}

void API::SetSceneName(System::String^ sceneName, bool bPost)
{
	TCHAR* unmanagedstring = (TCHAR *)Marshal::StringToHGlobalAuto(sceneName).ToPointer();
	clrHostApi->SetSceneName(unmanagedstring, bPost);
	Marshal::FreeHGlobal((System::IntPtr)unmanagedstring);
}

System::String^ API::GetSceneName()
{
	return gcnew System::String(clrHostApi->GetSceneName());
}

void API::SetDesktopVolume(float value, bool bo)
{
	::API->SetDesktopVolume(value, bo);
}

void API::SetMicVolume(float value, bool bo)
{
	::API->SetMicVolume(value, bo);
}

float API::GetDesktopVolume()
{
	return ::API->GetDesktopVolume();
}

float API::GetMicVolume()
{
	return ::API->GetMicVolume();
}

bool API::GetDesktopMuted()
{
	return ::API->GetDesktopMuted();
}

bool API::GetMicMuted()
{
	return ::API->GetMicMuted();
}

void API::ToggleDesktopMute()
{
	::API->ToggleDesktopMute();
}

void API::ToggleMicMute()
{
	::API->ToggleMicMute();
}

System::String^ API::GetScenes(int numb)
{
	return gcnew System::String(clrHostApi->GetScenes(numb));
}

int API::GetSceneCount()
{
	return clrHostApi->GetSceneCount();
}