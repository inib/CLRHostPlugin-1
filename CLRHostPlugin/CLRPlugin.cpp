#include "stdafx.h"

#include "CLRPlugin.h"

#include "mscorelib.h"

bool CLRPlugin::Attach(CLRObjectRef &clrObjectRef, mscorlib::_Type *objectType)
{
    CLRObject::Attach(clrObjectRef, objectType);

    bstr_t loadPlugindName("LoadPlugin");
    bstr_t unloadPluginMethodName("UnloadPlugin");
    bstr_t onStartStreamMethodName("OnStartStream");
    bstr_t onStopStreamMethodName("OnStopStream");
	bstr_t onSceneSwitchMethodName("OnSceneSwitch");
	bstr_t onOBSStatusMethodName("OnOBSStatus");
	bstr_t onMicVolumeChangedMethodName("OnMicVolumeChanged");
	bstr_t onDesktopVolumeChangedMethodName("OnDesktopVolumeChanged");

    // properties
    bstr_t getPluginNameMethodName("get_Name");
    bstr_t getPluginDescriptionMethodName("get_Description");

    HRESULT hr;

    hr = objectType->GetMethod_6(loadPlugindName, &loadPluginMethod);
    if (FAILED(hr) || !loadPluginMethod) {
        Log(TEXT("Failed to get LoadPlugin method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(unloadPluginMethodName, &unloadPluginMethod);
    if (FAILED(hr) || !unloadPluginMethod) {
        Log(TEXT("Failed to get UnloadPlugin method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }


    hr = objectType->GetMethod_6(onStartStreamMethodName, &onStartStreamMethod);
    if (FAILED(hr) || !onStartStreamMethod) {
        Log(TEXT("Failed to get OnStartStream method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(onStopStreamMethodName, &onStopStreamMethod);
    if (FAILED(hr) || !onStopStreamMethod) {
        Log(TEXT("Failed to get OnStopStream method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

	hr = objectType->GetMethod_6(onSceneSwitchMethodName, &onSceneSwitchMethod);
	if (FAILED(hr) || !onSceneSwitchMethod) {
		Log(TEXT("Failed to get onSceneSwitch method definition of Plugin class: 0x%08lx"), hr);
		goto errorCleanup;
	}

	hr = objectType->GetMethod_6(onOBSStatusMethodName, &onOBSStatusMethod);
	if (FAILED(hr) || !onOBSStatusMethod) {
		Log(TEXT("Failed to get onOBSStatus method definition of Plugin class: 0x%08lx"), hr);
		goto errorCleanup;
	}


	hr = objectType->GetMethod_6(onMicVolumeChangedMethodName, &onMicVolumeChangedMethod);
	if (FAILED(hr) || !onMicVolumeChangedMethod) {
		Log(TEXT("Failed to get onMicVolumeChanged method definition of Plugin class: 0x%08lx"), hr);
		goto errorCleanup;
	}

	hr = objectType->GetMethod_6(onDesktopVolumeChangedMethodName, &onDesktopVolumeChangedMethod);
	if (FAILED(hr) || !onDesktopVolumeChangedMethod) {
		Log(TEXT("Failed to get onDesktopVolumeChanged method definition of Plugin class: 0x%08lx"), hr);
		goto errorCleanup;
	}

    hr = objectType->GetMethod_6(getPluginNameMethodName, &getPluginNameMethod);
    if (FAILED(hr) || !getPluginNameMethod) {
        Log(TEXT("Failed to get Name property get() method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    hr = objectType->GetMethod_6(getPluginDescriptionMethodName, &getPluginDescriptionMethod);
    if (FAILED(hr) || !getPluginDescriptionMethod) {
        Log(TEXT("Failed to get Description property get() method definition of Plugin class: 0x%08lx"), hr); 
        goto errorCleanup;
    }

    goto success;

errorCleanup:
    Detach();
    return false;

success:
    return true;
}

void CLRPlugin::Detach()
{
    if (loadPluginMethod) {
        loadPluginMethod->Release();
        loadPluginMethod = nullptr;
    }
    if (unloadPluginMethod) {
        unloadPluginMethod->Release();
        unloadPluginMethod = nullptr;
    }
    if (onStartStreamMethod) {
        onStartStreamMethod->Release();
        onStartStreamMethod = nullptr;
    }
    if (onStopStreamMethod) {
        onStopStreamMethod->Release();
        onStopStreamMethod = nullptr;
    }
	if (onSceneSwitchMethod) {
		onSceneSwitchMethod->Release();
		onSceneSwitchMethod = nullptr;
	}
	if (onOBSStatusMethod) {
		onOBSStatusMethod->Release();
		onOBSStatusMethod = nullptr;
	}
	if (onMicVolumeChangedMethod) {
		onMicVolumeChangedMethod->Release();
		onMicVolumeChangedMethod = nullptr;
	}
	if (onDesktopVolumeChangedMethod) {
		onDesktopVolumeChangedMethod->Release();
		onDesktopVolumeChangedMethod = nullptr;
	}
    if (getPluginNameMethod) {
        getPluginNameMethod->Release();
        getPluginNameMethod = nullptr;
    }
    if (getPluginDescriptionMethod) {
        getPluginDescriptionMethod->Release();
        getPluginDescriptionMethod = nullptr;
    }

    CLRObject::Detach();
}

bool CLRPlugin::LoadPlugin()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::OnStopStream() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = loadPluginMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke OnStopStream on managed instance: 0x%08lx"), hr); 
    }

    return returnVal.boolVal == VARIANT_TRUE;
}

void CLRPlugin::UnloadPlugin()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::UnloadPlugin() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = unloadPluginMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke UnloadPlugin on managed instance: 0x%08lx"), hr); 
    }

    return;
}

void CLRPlugin::OnStartStream()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::OnStartStream() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = onStartStreamMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke OnStartStream on managed instance: 0x%08lx"), hr); 
    }


    return;
}

void CLRPlugin::OnStopStream()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::OnStopStream() no managed object attached"));
    }

    variant_t objectRef(GetObjectRef());

    HRESULT hr = onStopStreamMethod->Invoke_3(objectRef, nullptr, nullptr);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke OnStopStream on managed instance: 0x%08lx"), hr); 
    }

    return;
}

void CLRPlugin::OnSceneSwitch(CTSTR scene)
{
	if (!IsValid()) {
		Log(TEXT("CLRPlugin::OnSceneSwitch() no managed object attached"));
	}
	SAFEARRAY *args = SafeArrayCreateVector(VT_VARIANT, 0, 1);
	LONG index = 0;

	variant_t objectRef(GetObjectRef());
	variant_t valScene(scene);

	SafeArrayPutElement(args, &index, &valScene);

	HRESULT hr = onSceneSwitchMethod->Invoke_3(objectRef, args, nullptr);
	SafeArrayDestroy(args);

	if (FAILED(hr)) {
		Log(TEXT("Failed to invoke OnSceneSwitch on managed instance: 0x%08lx"), hr);
	}

	return;
}

void CLRPlugin::OnOBSStatus(bool running, bool streaming, bool recording, bool previewing, bool reconnecting)
{
	if (!IsValid()) {
		Log(TEXT("CLRPlugin::OnOBSStatus() no managed object attached"));
	}

	SAFEARRAY *args = SafeArrayCreateVector(VT_VARIANT, 0, 5);
	LONG index = 0;

	variant_t objectRef(GetObjectRef());
	variant_t valRun(running);
	variant_t valStream(streaming);
	variant_t valRec(recording);
	variant_t valPre(previewing);
	variant_t valRe(reconnecting);

	SafeArrayPutElement(args, &index, &valRun);
	index++;
	SafeArrayPutElement(args, &index, &valStream);
	index++;
	SafeArrayPutElement(args, &index, &valRec);
	index++;
	SafeArrayPutElement(args, &index, &valPre);
	index++;
	SafeArrayPutElement(args, &index, &valRe);

	HRESULT hr = onOBSStatusMethod->Invoke_3(objectRef, args, nullptr);
	if (FAILED(hr)) {
		Log(TEXT("Failed to invoke OnOBSStatus on managed instance: 0x%08lx"), hr);
	}

	SafeArrayDestroy(args);
	return;
}

void CLRPlugin::OnDesktopVolumeChanged(float level, bool muted, bool finalValue)
{
	if (!IsValid()) {
		Log(TEXT("CLRPlugin::OnDesktopVolumeChanged() no managed object attached"));
	}

	SAFEARRAY *args = SafeArrayCreateVector(VT_VARIANT, 0, 3);
	LONG index = 0;

	variant_t objectRef(GetObjectRef());
	variant_t valLev(level);
	variant_t valMut(muted);
	variant_t valFin(finalValue);

	SafeArrayPutElement(args, &index, &valLev);
	index++;
	SafeArrayPutElement(args, &index, &valMut);
	index++;
	SafeArrayPutElement(args, &index, &valFin);

	HRESULT hr = onDesktopVolumeChangedMethod->Invoke_3(objectRef, args, nullptr);
	if (FAILED(hr)) {
		Log(TEXT("Failed to invoke OnDesktopVolumeChanged on managed instance: 0x%08lx"), hr);
	}

	SafeArrayDestroy(args);
	return;
}

void CLRPlugin::OnMicVolumeChanged(float level, bool muted, bool finalValue)
{
	if (!IsValid()) {
		Log(TEXT("CLRPlugin::OnDesktopVolumeChanged() no managed object attached"));
	}

	SAFEARRAY *args = SafeArrayCreateVector(VT_VARIANT, 0, 3);
	LONG index = 0;

	variant_t objectRef(GetObjectRef());
	variant_t valLev(level);
	variant_t valMut(muted);
	variant_t valFin(finalValue);

	SafeArrayPutElement(args, &index, &valLev);
	index++;
	SafeArrayPutElement(args, &index, &valMut);
	index++;
	SafeArrayPutElement(args, &index, &valFin);

	HRESULT hr = onMicVolumeChangedMethod->Invoke_3(objectRef, args, nullptr);
	if (FAILED(hr)) {
		Log(TEXT("Failed to invoke OnMicVolumeChanged on managed instance: 0x%08lx"), hr);
	}

	SafeArrayDestroy(args);
	return;
}

std::wstring CLRPlugin::GetPluginName()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::GetPluginName() no managed object attached"));
        return std::wstring(TEXT("!error! see log"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getPluginNameMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke GetPluginName on managed instance: 0x%08lx"), hr); 
        return std::wstring(TEXT("!error! see log"));
    }

    return std::wstring((const wchar_t*)returnVal.bstrVal);
}

std::wstring CLRPlugin::GetPluginDescription()
{
    if (!IsValid()) {
        Log(TEXT("CLRPlugin::GetPluginDescription() no managed object attached"));
        return std::wstring(TEXT("!error! see log"));
    }

    variant_t objectRef(GetObjectRef());
    variant_t returnVal;

    HRESULT hr = getPluginDescriptionMethod->Invoke_3(objectRef, nullptr, &returnVal);
    if (FAILED(hr)) {
        Log(TEXT("Failed to invoke GetPluginDescription on managed instance: 0x%08lx"), hr); 
        return std::wstring(TEXT("!error! see log"));
    }

    return std::wstring((const wchar_t*)returnVal.bstrVal);
}