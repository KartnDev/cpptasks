// include the basic windows header files and the Direct3D header files
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <sstream>


// include the Direct3D Library file

// define the screen resolution
//#define SCREEN_WIDTH  800
//#define SCREEN_HEIGHT 600
//
//
//// the WindowProc function prototype
//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//
//
//// the entry point for any Windows program
//int WINAPI WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine,
//	int nCmdShow)
//{
//	HWND hWnd;
//	WNDCLASSEX wc;
//
//	ZeroMemory(&wc, sizeof(WNDCLASSEX));
//
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = WindowProc;
//	wc.hInstance = hInstance;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.lpszClassName = L"WindowClass";
//
//	RegisterClassEx(&wc);
//
//	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
//
//	hWnd = CreateWindowEx(NULL,
//		L"WindowClass",
//		L"Our First Direct3D Program",
//		WS_OVERLAPPEDWINDOW,
//		300,
//		300,
//		wr.right - wr.left,
//		wr.bottom - wr.top,
//		NULL,
//		NULL,
//		hInstance,
//		NULL);
//
//	ShowWindow(hWnd, nCmdShow);
//
//
//	// enter the main loop:
//
//	MSG msg;
//
//	while (TRUE)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//
//			if (msg.message == WM_QUIT)
//				break;
//		}
//	}
//
//
//	return msg.wParam;
//}
//
//
//std::wstring s2ws(const std::string& s)
//{
//	int len;
//	int slength = (int)s.length() + 1;
//	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
//	wchar_t* buf = new wchar_t[len];
//	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
//	std::wstring r(buf);
//	delete[] buf;
//	return r;
//}
//
//
//// this is the main message handler for the program
//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	SetConsoleOutputCP(1251);
//	switch (message)
//	{
//	case WM_DESTROY:
//	{
//		PostQuitMessage(0);
//		break;
//	}
//	case WM_CHAR:
//	{
//		static std::string title;
//		title.push_back((char)wParam);
//
//		std::wstring stemp = s2ws(title);
//		SetWindowText(hWnd, reinterpret_cast<LPCWSTR>(stemp.c_str()));
//	}
//	case WM_KEYDOWN:
//	{
//		if (wParam == 'Q')
//		{
//			SetWindowText(hWnd, L"HYI!");
//		}
//		break;
//	}
//	case WM_LBUTTONUP:
//		{
//			const POINTS pt = MAKEPOINTS(lParam);
//			std::ostringstream oss;
//			oss << "(" << pt.x << ", " << pt.y << ")";
//			std::wstring stemp = s2ws(oss.str());
//			SetWindowText(hWnd, stemp.c_str());
//		}
//	}
//
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}
//
//
