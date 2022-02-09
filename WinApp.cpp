#include "WinApp.h"

//ウィンドウプロシージャ
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//メッセージで分岐
	switch (msg) {
	case WM_DESTROY://ウィンドウが破棄された
		PostQuitMessage(0);//OSに対して、アプリの終了を伝える
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);//標準の処理を行う
}

WinApp::~WinApp()
{
	// ウィンドウクラスを登録解除
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);

}

void WinApp::Initialize()
{
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = (WNDPROC)WindowProc;//ウィンドウプロシージャを設定
	wndClass.lpszClassName = L"DirectXGame";//ウィンドウクラス名
	wndClass.hInstance = GetModuleHandle(nullptr);//ウィンドウハンドル
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル指定
	//ウィンドウクラスをOSに登録
	RegisterClassEx(&wndClass);
	//ウィンドウサイズ{ X 座標 Y 座標 横幅 縦幅 }
	RECT wrc = { 0, 0, window_width, window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);//自動でサイズ補正
	//ウィンドウオブジェクトの生成
	hwnd = CreateWindow(wndClass.lpszClassName,//クラス名
		L"1015395_山田将希",//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,//標準的なウィンドウスタイル
		CW_USEDEFAULT,//表示X 座標(OS に任せる)
		CW_USEDEFAULT,//表示Y 座標(OS に任せる)
		wrc.right - wrc.left,//ウィンドウ横幅
		wrc.bottom - wrc.top,//ウィンドウ縦幅
		nullptr,//親ウィンドウハンドル
		nullptr,//メニューハンドル
		wndClass.hInstance,//呼び出しアプリケーションハンドル
		nullptr);//オプション
		//ウィンドウ表示
	ShowWindow(hwnd, SW_SHOW);
}

bool WinApp::Update()
{
	//メッセージがある?
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg); //キー入力メッセージの処理
		DispatchMessage(&msg); //プロシージャにメッセージを送る
	}
	//終了メッセージが来たらループを抜ける
	if (msg.message == WM_QUIT) {
		return true;
	}
	return false;
}
