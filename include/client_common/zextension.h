#pragma once

///> Extension type def
#define ExtensionType_Map       0x1
#define ExtensionType_Npc       0x2

typedef struct _ZExtensionInfo
{
    DWORD dwType;
    char szVersion[64];

    _ZExtensionInfo()
    {
        dwType = 0;
        szVersion[0] = '\0';
    }
}ZExtensionInfo;

interface IZExtension
{
    virtual __stdcall bool Init() = 0;
    virtual __stdcall void Uninit() = 0;
    virtual __stdcall void GetExtensionInfo(ZExtensionInfo& info) = 0;
    virtual __stdcall bool DoWork(int nType, void* pData) = 0;
};
