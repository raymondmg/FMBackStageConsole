// DllTest.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"

extern "C" __declspec(dllexport) char* Add()
 {
	HWND hwnd = FindWindow(NULL, L"WindowName");
	SendMessage(hwnd, 0x300, NULL, NULL);
	return "ok";
 }


#define WM_TEST WM_USER+1//�Զ�����Ϣ

struct LParamDataSruct
{
public:
	char* lParamData;       //Ҫ���͵���Ϣ
};

//hwndΪC#����ľ��
extern "C" __declspec(dllexport) bool Get_Msg_Test(HWND hwnd)
{
	LParamDataSruct lparam;
	WPARAM wPARAM = 0;
	char* test = "This is test MSG ������";
	lparam.lParamData = test;

	::SendMessage(hwnd, WM_TEST, wPARAM, (LPARAM)&lparam);
	return true;
}