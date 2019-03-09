#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWind, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	}
	return DefWindowProc(hWind,msg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInctance, LPSTR lpCmdLine, int nCmdShow)
{
	const auto pClassName = "hw3dbutts";
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName; 
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	//4th param might be only one like WS_CAPTION (WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU)
	HWND hwnd = CreateWindowEx(0, pClassName, "MyWindow", WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, 200, 200, 640, 480, nullptr, nullptr, hInstance, nullptr); 
	ShowWindow(hwnd, SW_SHOW);
	
	MSG msg;
	BOOL gResult;


	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	if (gResult == -1) {
		return -1;
	}
	else
	{
		return msg.wParam;
	}


	return 0;
}