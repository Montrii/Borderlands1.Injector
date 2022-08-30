// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <fstream>  
#include <sys/stat.h>
#include <experimental/filesystem>



using namespace std;
namespace fs = std::experimental::filesystem;

extern "C"
{
	void* __CreateD3D9;
	__declspec(dllexport) void* CreateD3D9(bool Extended, void* ppDirect3D9Ex)
	{
		return __CreateD3D9;
	}
    void* __Direct3DCreate9;
    __declspec(dllexport) void* Direct3DCreate9(UINT SDKVersion)
	{
		return __Direct3DCreate9;
	}
	
	void* __Direct3DCreate9Ex;
    __declspec(dllexport) void* Direct3DCreate9Ex(UINT SDKVersion, void** ppD3D)
    {
		return __Direct3DCreate9Ex;
    }
	void* __D3DPERF_BeginEvent;
	__declspec(dllexport) void* D3DPERF_BeginEvent(void* col, LPCWSTR wszName)
	{
		return __D3DPERF_BeginEvent;
	}
	void* __D3DPERF_EndEvent;
	__declspec(dllexport) void*  D3DPERF_EndEvent()
	{
		return __D3DPERF_EndEvent;
	}
	void* __D3DPERF_GetStatus;
	__declspec(dllexport) void*  D3DPERF_GetStatus()
	{
		return __D3DPERF_GetStatus;
	}
	
	void* __D3DPERF_QueryRepeatFrame;
	__declspec(dllexport) void*  D3DPERF_QueryRepeatFrame()
	{
		return __D3DPERF_QueryRepeatFrame;
	}
	void* __D3DPERF_SetMarker;
	__declspec(dllexport) void*  D3DPERF_SetMarker(void* col, LPCWSTR wszName)
	{
		return __D3DPERF_SetMarker;
	}
	void* __D3DPERF_SetOptions;
	__declspec(dllexport) void*  D3DPERF_SetOptions(DWORD dwOptions)
	{
		return __D3DPERF_SetOptions;
	}
	void* __D3DPERF_SetRegion;
	__declspec(dllexport) void*  D3DPERF_SetRegion(void* col, LPCWSTR wszName)
	{
		return __D3DPERF_SetRegion;
	}

	void* __DebugSetMute;
	__declspec(dllexport) void*  DebugSetMute(void)
	{
		return __DebugSetMute;
	}
	
	void* __DebugSetLevel;
    __declspec(dllexport) void*  DebugSetLevel(void)
    {
		return __DebugSetLevel;
    }

	void* __PSGError;
    __declspec(dllexport) void*  PSGError(void* a, void* b, UINT c)
    {
		return __PSGError;
    }
	void* __PSGPSampleTexture;
	__declspec(dllexport) void*  PSGPSampleTexture(void* a, void* b, UINT c)
	{
		return __PSGPSampleTexture;
	}

    void* __Direct3DShaderValidatorCreate9;
    __declspec(dllexport) void* Direct3DShaderValidatorCreate9(void)
    {
        return __Direct3DShaderValidatorCreate9;
    }
	void* __Direct3D9EnableMaximizedWindowedModeShim;
	__declspec(dllexport) void*  Direct3D9EnableMaximizedWindowedModeShim(UINT a)
	{
		return __Direct3D9EnableMaximizedWindowedModeShim;
	}

    void* __DXVK_RegisterAnnotation;
	__declspec(dllexport) void*  DXVK_RegisterAnnotation(void* annotation)
	{
		return __DXVK_RegisterAnnotation;
	}
	void* __DXVK_UnRegisterAnnotation;
    __declspec(dllexport) void*  DXVK_UnRegisterAnnotation(void* annotation)
    {
		return __DXVK_UnRegisterAnnotation;
    }
	
	void* __Direct3D9ForceHybridEnumeration;
    __declspec(dllexport) void*  Direct3D9ForceHybridEnumeration(UINT uHybrid)
    {
		return __Direct3D9ForceHybridEnumeration;
    }
	
    
	
	
}

wstring getGamePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    // get current module (Borderlands.exe) filename
    GetModuleFileName(NULL, buffer, MAX_PATH);
    // get path
    wstring::size_type pos = wstring(buffer).find_last_of(L"\\/");
    // return
    return wstring(buffer).substr(0, pos);
}


string createScriptDirectory(wstring path)
{
    // add scripts folder to current path
    string actualPath = string(path.begin(), path.end()) + "\\scripts";
    struct stat buffer;

    // if directory does not exist
    if (stat(actualPath.c_str(), &buffer) != 0)
    {

        // create it
        CreateDirectory(wstring(actualPath.begin(), actualPath.end()).c_str(), NULL);
    }

    return actualPath;
}

void loadScripts(string path)
{

    // trying to loop directories with findfirstfile, findnextfile and findclose for some reason causes game to crash upon launch.
    for (const auto& item : fs::recursive_directory_iterator(path))
    {
        // if file is regular file (no . or .. directory) and has extension of .dll, load it.
        if (fs::is_regular_file(item.path()) && item.path().extension() == ".dll")
        {
            string fileNameString = item.path().string();
            wstring fileName = wstring(fileNameString.begin(), fileNameString.end());
            LoadLibrary(fileName.c_str());
        }
    }
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        // if module can be loaded
        HMODULE vorbisSenc = LoadLibrary(L"d3d9");
        if (vorbisSenc)
        {


            // allow Borderlands to still import this function by importing this function here from original vorbisenc.dll
            __Direct3DCreate9 = (void*)GetProcAddress(vorbisSenc, "Direct3DCreate9");
			__Direct3DCreate9Ex = (void*)GetProcAddress(vorbisSenc, "Direct3DCreate9Ex");
			__Direct3DShaderValidatorCreate9 = (void*)GetProcAddress(vorbisSenc, "Direct3DShaderValidatorCreate9");
			__Direct3D9EnableMaximizedWindowedModeShim = (void*)GetProcAddress(vorbisSenc, "Direct3D9EnableMaximizedWindowedModeShim");
			__DXVK_RegisterAnnotation = (void*)GetProcAddress(vorbisSenc, "DXVK_RegisterAnnotation");
			__DXVK_UnRegisterAnnotation = (void*)GetProcAddress(vorbisSenc, "DXVK_UnRegisterAnnotation");
			__Direct3D9ForceHybridEnumeration = (void*)GetProcAddress(vorbisSenc, "Direct3D9ForceHybridEnumeration");
			__DebugSetMute = (void*)GetProcAddress(vorbisSenc, "DebugSetMute");
			__DebugSetLevel = (void*)GetProcAddress(vorbisSenc, "DebugSetLevel");
			__PSGError = (void*)GetProcAddress(vorbisSenc, "PSGError");
			__PSGPSampleTexture = (void*)GetProcAddress(vorbisSenc, "PSGPSampleTexture");
			__D3DPERF_BeginEvent = (void*)GetProcAddress(vorbisSenc, "D3DPERF_BeginEvent");
			__D3DPERF_EndEvent = (void*)GetProcAddress(vorbisSenc, "D3DPERF_EndEvent");
			__D3DPERF_GetStatus = (void*)GetProcAddress(vorbisSenc, "D3DPERF_GetStatus");
			__D3DPERF_QueryRepeatFrame = (void*)GetProcAddress(vorbisSenc, "D3DPERF_QueryRepeatFrame");
			__D3DPERF_SetMarker = (void*)GetProcAddress(vorbisSenc, "D3DPERF_SetMarker");
			__D3DPERF_SetOptions = (void*)GetProcAddress(vorbisSenc, "D3DPERF_SetOptions");
			__D3DPERF_SetRegion = (void*)GetProcAddress(vorbisSenc, "D3DPERF_SetRegion");
			


            // create directory if not existent
            string actualPath = createScriptDirectory(getGamePath());

            // load scripts within path and all sub directories within that path
            loadScripts(actualPath);

        }
    }
    return TRUE;
}


