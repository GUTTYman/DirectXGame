#pragma once
#define DIRECTINPUT_VERSION 0x0800 //DirectInputのバージョン指定
#include <dinput.h>
#include<Windows.h>

#pragma comment(lib, "dinput8.lib")
class Input
{
public:
	Input();
	~Input();

	void Initialize(HWND hwnd);

	void Update();

	bool Push(int keyNum);

	bool Trigger(int keyNum);
private:
	//キーボードデバイスの生成
	IDirectInputDevice8* devkeyboard = nullptr;
	
	//全キーの入力状態を取得する
	BYTE key[256] = {};
	BYTE key2[256] = {};

};

