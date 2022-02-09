#pragma once

#include<Windows.h>

//WindowsAPI
class WinApp
{
public:
	static const int window_width = 1280;//横幅
	static const int window_height = 720;//縦幅
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	~WinApp();
	void Initialize();
	bool Update();
	const HWND& GetHwnd(){ return hwnd; }
	const WNDCLASSEX& GetWndClass(){ return wndClass; }
private:
	HWND hwnd = nullptr;	//ウィンドウハンドル
	WNDCLASSEX wndClass{};	//ウィンドウクラス
	MSG msg{}; //メッセージ

};

