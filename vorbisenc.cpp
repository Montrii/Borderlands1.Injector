// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <fstream>  
#include <sys/stat.h>


extern "C"
{
	// building struct for exporting function
    struct vorbis_info {
        int version;
        int channels;
        long rate;

        long bitrate_upper;
        long bitrate_nominal;
        long bitrate_lower;
        long bitrate_window;

        void* codec_setup;

    };

	// calling convention is __declspec

    void* __vorbis_encode_init_vbr;
    __declspec(dllexport, naked) int vorbis_encode_init_vbr(vorbis_info* vi, long channels, long rate, float base_quality)
    {
        _asm jmp __vorbis_encode_init_vbr;
    }
}

std::wstring getGamePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
	// get current module (Borderlands.exe) filename
    GetModuleFileName(NULL, buffer, MAX_PATH);
	// get path
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	// return
    return std::wstring(buffer).substr(0, pos);
}


void createScriptDirectory(std::wstring path)
{
	// add scripts folder to current path
    std::string actualPath = std::string(path.begin(), path.end()) + "\\scripts";
    struct stat buffer;
	
	// if directory does not exist
    if (stat(actualPath.c_str(), &buffer) != 0)
    {

		// create it
        CreateDirectory(std::wstring(actualPath.begin(), actualPath.end()).c_str(), NULL);
    }
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	// if module can be loaded
    HMODULE vorbisSenc = LoadLibrary (L"vorbisenc");
    if (vorbisSenc)
    {
		

		// allow Borderlands to still import this function by importing this function here from original vorbisenc.dll
		__vorbis_encode_init_vbr = (void*)GetProcAddress(vorbisSenc, "vorbis_encode_init_vbr");
		

		// create directory if not existent
        createScriptDirectory(getGamePath());

		// load scripts within path and all sub directories within that path
		
    }
    return TRUE;
}


