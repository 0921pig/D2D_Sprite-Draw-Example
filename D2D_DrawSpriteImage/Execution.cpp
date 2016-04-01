#include "stdafx.h"
#include "Execution.h"
#include "DeviceMgr.h"
#include "Base.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT, WPARAM wParam, LPARAM lParam);

// 전역 변수
HWND g_hWnd;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG msg;
	msg.message = WM_NULL;
	HWND hWnd;
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = TEXT("Client");
	WndClass.lpszMenuName = 0;
	WndClass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClass(&WndClass))
		return 0;

	RECT rcWindow = { 0, 0, WINSIZEX, WINSIZEY };

	//윈도우가 원하는 클라이언트 영역의 크기를 가지도록 윈도우의 크기를 계산하는 함수
	AdjustWindowRect(&rcWindow, WS_OVERLAPPEDWINDOW, false);
	/*		 rcWindow : 원하는 클라이언트 영역의 크기를 나타내는 사각형을 지정한다. 윈도우의 새로운 크기를 lpRect를 통해 반환한다.
	dwStyle : 윈도우의 스타일을 지정한다
	bMenu :  윈도우가 메뉴를 가지는가를 지정한다. true 이면 윈도우가 메뉴를 가진다. false이면 윈도우가 메뉴를 가지지 않는다.
	*/


	hWnd = CreateWindow(WndClass.lpszClassName, L"Window Caption", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top, NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return FALSE;

	g_hWnd = hWnd;

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	//처음에 한번만 ㅇㅇ
	GET_SINGLE(CDeviceMgr)->InitDevice(WINMODE_WIN);

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GET_SINGLE(CDeviceMgr)->Render_Begin();
			GET_SINGLE(CDeviceMgr)->Draw();
			GET_SINGLE(CDeviceMgr)->Render_End();
		}

	}

	GET_SINGLE(CDeviceMgr)->Release();
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
