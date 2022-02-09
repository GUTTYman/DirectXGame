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
	//DirectInput �I�u�W�F�N�g�̐���
	IDirectInput8* dinput = nullptr;
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	//�r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{
	HRESULT result;
	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();

	//�O��̓��͏����R�s�[
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
	//�O�񉟂���Ă��Ȃ��A����������Ă���
	if (!key2[keyNum]&&key[keyNum])
	{
		return true;
	}
	return false;
}
