#pragma once

#include <Windows.h>
#include "import\hge\include\hge.h"
#include "import\hge\include\hgesprite.h"
#include <vector>

#include "engine\sceneengine.h"
#include "engine\inputengine.h"

extern HGE* hge;
extern SceneEngine* SceneEngine_;
extern InputEngine* InputEngine_;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600


/*
**  Virtual-key codes
*/
#define KEY_LBUTTON	0x01
#define KEY_RBUTTON	0x02
#define KEY_MBUTTON	0x04

#define KEY_ESCAPE		0x1B
#define KEY_BACKSPACE	0x08
#define KEY_TAB		0x09
#define KEY_ENTER		0x0D
#define KEY_SPACE		0x20

#define KEY_SHIFT		0x10
#define KEY_CTRL		0x11
#define KEY_ALT		0x12

#define KEY_LWIN		0x5B
#define KEY_RWIN		0x5C
#define KEY_APPS		0x5D

#define KEY_PAUSE		0x13
#define KEY_CAPSLOCK	0x14
#define KEY_NUMLOCK	0x90
#define KEY_SCROLLLOCK	0x91

#define KEY_PGUP		0x21
#define KEY_PGDN		0x22
#define KEY_HOME		0x24
#define KEY_END		0x23
#define KEY_INSERT		0x2D
#define KEY_DELETE		0x2E

#define KEY_LEFT		0x25
#define KEY_UP			0x26
#define KEY_RIGHT		0x27
#define KEY_DOWN		0x28

#define KEY_0			0x30
#define KEY_1			0x31
#define KEY_2			0x32
#define KEY_3			0x33
#define KEY_4			0x34
#define KEY_5			0x35
#define KEY_6			0x36
#define KEY_7			0x37
#define KEY_8			0x38
#define KEY_9			0x39

#define KEY_A			0x41
#define KEY_B			0x42
#define KEY_C			0x43
#define KEY_D			0x44
#define KEY_E			0x45
#define KEY_F			0x46
#define KEY_G			0x47
#define KEY_H			0x48
#define KEY_I			0x49
#define KEY_J			0x4A
#define KEY_K			0x4B
#define KEY_L			0x4C
#define KEY_M			0x4D
#define KEY_N			0x4E
#define KEY_O			0x4F
#define KEY_P			0x50
#define KEY_Q			0x51
#define KEY_R			0x52
#define KEY_S			0x53
#define KEY_T			0x54
#define KEY_U			0x55
#define KEY_V			0x56
#define KEY_W			0x57
#define KEY_X			0x58
#define KEY_Y			0x59
#define KEY_Z			0x5A

#define KEY_GRAVE		0xC0
#define KEY_MINUS		0xBD
#define KEY_EQUALS		0xBB
#define KEY_BACKSLASH	0xDC
#define KEY_LBRACKET	0xDB
#define KEY_RBRACKET	0xDD
#define KEY_SEMICOLON	0xBA
#define KEY_APOSTROPHE	0xDE
#define KEY_COMMA		0xBC
#define KEY_PERIOD		0xBE
#define KEY_SLASH		0xBF

#define KEY_NUMPAD0	0x60
#define KEY_NUMPAD1	0x61
#define KEY_NUMPAD2	0x62
#define KEY_NUMPAD3	0x63
#define KEY_NUMPAD4	0x64
#define KEY_NUMPAD5	0x65
#define KEY_NUMPAD6	0x66
#define KEY_NUMPAD7	0x67
#define KEY_NUMPAD8	0x68
#define KEY_NUMPAD9	0x69

#define KEY_MULTIPLY	0x6A
#define KEY_DIVIDE		0x6F
#define KEY_ADD		0x6B
#define KEY_SUBTRACT	0x6D
#define KEY_DECIMAL	0x6E

#define KEY_F1			0x70
#define KEY_F2			0x71
#define KEY_F3			0x72
#define KEY_F4			0x73
#define KEY_F5			0x74
#define KEY_F6			0x75
#define KEY_F7			0x76
#define KEY_F8			0x77
#define KEY_F9			0x78
#define KEY_F10		0x79
#define KEY_F11		0x7A
#define KEY_F12		0x7B

#define PI                  3.141592f