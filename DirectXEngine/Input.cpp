#include "Input.h"
Input::Input()
{

}
Input::~Input()
{

}
void Input::Initialize(HWND hwnd)
{
	HRESULT result;
	//DirectInput オブジェクトの生成
	IDirectInput8* dinput = nullptr;
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	//入力データ形式のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	//排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{
	HRESULT result;
	//キーボード情報の取得開始
	result = devkeyboard->Acquire();

	//前回の入力情報をコピー
	for (int i = 0; i < 256; i++)
	{
		key2[i] = key[i];
	}

	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::Push(int keyNum)
{
	if (keyNum < 0x00)return false;
	if (keyNum > 0xff)return false;

	if (key[keyNum])
	{
		return true;
	}
	return false;
}

bool Input::Trigger(int keyNum)
{
	if (keyNum < 0x00)return false;
	if (keyNum > 0xff)return false;
	//前回押されていない、かつ今押されている
	if (!key2[keyNum]&&key[keyNum])
	{
		return true;
	}
	return false;
}
