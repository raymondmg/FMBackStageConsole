// DllTest.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

extern "C" __declspec(dllexport) char* Add()
 {
	HWND hwnd = FindWindow(NULL, L"WindowName");
	SendMessage(hwnd, 0x300, NULL, NULL);
	return "ok";
 }


#define WM_TEST WM_USER+1//自定义消息

struct LParamDataSruct
{
public:
	char* lParamData;       //要发送的信息
};

//hwnd为C#窗体的句柄
extern "C" __declspec(dllexport) bool Get_Msg_Test(HWND hwnd)
{
	LParamDataSruct lparam;
	WPARAM wPARAM = 0;
	char* test = "This is test MSG 哈哈。";
	lparam.lParamData = test;

	::SendMessage(hwnd, WM_TEST, wPARAM, (LPARAM)&lparam);
	return true;
}