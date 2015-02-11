#pragma once

#include <string>
#include <map>

#include "CLRApiCommon.h"
#include "CLRObjectRef.h"
#include "CLRImageSourceFactory.h"

class CLRHostApi 
{
private:
    std::map<std::wstring, CLRImageSourceFactory *> imageSourceFactories;

public:
    ~CLRHostApi();
public:
    CLR_API void AddSettingsPane(CLRObjectRef &clrObjectReference);
    CLR_API void AddImageSourceFactory(CLRObjectRef &clrObjectReference);
	CLR_API void SetSceneName(const TCHAR * sceneName, bool bPost);
	CLR_API const TCHAR * GetSceneName();
	CLR_API float GetDesktopVolume();
	CLR_API void SetDesktopVolume(float val, bool finalValue);
	CLR_API bool GetDesktopMuted();
	CLR_API void ToggleDesktopMute();
	CLR_API const TCHAR * GetScenes(int numb);
	CLR_API int GetSceneCount();

public:
    std::map<std::wstring, CLRImageSourceFactory *> &GetImageSourceFactories() { return imageSourceFactories; }
};