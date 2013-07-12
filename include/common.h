#ifndef ZEUS_COMMON_H_
#define ZEUS_COMMON_H_

//stl
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <unordered_map> //c++0x

//socket dependencies
#if defined(_WIN32)
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

//debug
#include <assert.h>

//Datatypes
#if defined(_WIN32)	//for windows
#ifndef byte
typedef unsigned __int8    byte;
#endif
typedef __int8             int8;
typedef __int16            int16;
typedef __int32            int32;
typedef __int64            int64;
typedef unsigned __int32   uint;
typedef unsigned __int8    uint8;
typedef unsigned __int16   uint16;
typedef unsigned __int32   uint32;
typedef unsigned __int64   uint64;
#else
#ifndef byte
typedef unsigned char      byte;
#endif
typedef char               int8;
typedef short              int16;
typedef int                int32;
typedef long long          int64;
typedef unsigned int       uint;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;
#endif

//Endianness
#define swap16(s) ((((s) & 0xff) << 8) | (((s) >> 8) & 0xff))
#define swap32(l) (((l) >> 24) | \
           (((l) & 0x00ff0000) >> 8)  | \
           (((l) & 0x0000ff00) << 8)  | \
           ((l) << 24)) 

#define swap64(ll)(((ll) >> 56) | \
                    (((ll) & 0x00ff000000000000) >> 40) | \
                    (((ll) & 0x0000ff0000000000) >> 24) | \
                    (((ll) & 0x000000ff00000000) >> 8)  | \
                    (((ll) & 0x00000000ff000000) << 8)  | \
                    (((ll) & 0x0000000000ff0000) << 24) | \
                    (((ll) & 0x000000000000ff00) << 40) | \
                    (((ll) << 56)))


static float swapfloat(const float& p)
{
	union { float asfloat; byte asbytes[4]; } u1, u2;
	u1.asfloat = p;
	u2.asbytes[0] = u1.asbytes[3];
	u2.asbytes[1] = u1.asbytes[2];
	u2.asbytes[2] = u1.asbytes[1];
	u2.asbytes[3] = u1.asbytes[0];
	//*p = u2.asfloat;
    return u2.asfloat;
}

static double swapdouble(const double& p)
{
	union { double asdouble; byte asbytes[8]; } u1, u2;
	u1.asdouble = p;
	u2.asbytes[0] = u1.asbytes[7];
	u2.asbytes[1] = u1.asbytes[6];
	u2.asbytes[2] = u1.asbytes[5];
	u2.asbytes[3] = u1.asbytes[4];
	u2.asbytes[4] = u1.asbytes[3];
	u2.asbytes[5] = u1.asbytes[2];
	u2.asbytes[6] = u1.asbytes[1];
	u2.asbytes[7] = u1.asbytes[0];
	//*p = u2.asfloat;
    return u2.asdouble;
}

//Lines
#if defined(_WIN32)
#define NEWLINE "\r\n"
#else
#define NEWLINE "\n"
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if (NULL != (x)) { delete (x); (x) = NULL; }
#endif
#endif