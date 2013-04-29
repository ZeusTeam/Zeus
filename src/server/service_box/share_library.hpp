#ifndef SHARE_LIBRARY_H_
#define SHARE_LIBRARY_H_

#if defined(_WINDOWS_)
#include <Windows.h>
typedef HMODULE ShareObject
#else
#include <dlfcn.h>
typedef void* ShareObject
#endif

class ShareLibrary
{

};

#endif