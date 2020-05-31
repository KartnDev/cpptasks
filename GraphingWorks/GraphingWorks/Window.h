#pragma once
#include "KartWin.h"
#include "exception.h"


class Window
{
public:
	class Exception : public GameRuntimeError
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};



private:
	class WindowClass
	{
	public:
		static const LPCWSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr LPCWSTR wndClassName  = L"Engine Wnd";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const LPCWSTR name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator= (const Window&) = delete;
private:
	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	int width;
	int height;
	HWND hWnd;


};
