/*
Implementation of https://www.youtube.com/watch?v=5tg_TbURMy0
"Tiny executables with MSVCRT features without depending on compiler
redistributables" / Per Vognsen

*/

#include <Windows.h>

extern "C"
{
	int _fltused;
}

void WinMainCRTStartup()
{
	MessageBoxA(0, "txt", "", MB_OK);
}
