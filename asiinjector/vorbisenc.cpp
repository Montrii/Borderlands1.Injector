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
        HMODULE vorbisSenc = LoadLibrary(L"vorbisenc");
        if (vorbisSenc)
        {


            // allow Borderlands to still import this function by importing this function here from original vorbisenc.dll
            __vorbis_encode_init_vbr = (void*)GetProcAddress(vorbisSenc, "vorbis_encode_init_vbr");


            // create directory if not existent
            string actualPath = createScriptDirectory(getGamePath());

            // load scripts within path and all sub directories within that path
            loadScripts(actualPath);

        }
    }
    return TRUE;
}


