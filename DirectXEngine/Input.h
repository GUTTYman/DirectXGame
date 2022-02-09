#pragma once
#define DIRECTINPUT_VERSION 0x0800 //DirectInput�̃o�[�W�����w��
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
	//�L�[�{�[�h�f�o�C�X�̐���
	IDirectInputDevice8* devkeyboard = nullptr;
	
	//�S�L�[�̓��͏�Ԃ��擾����
	BYTE key[256] = {};
	BYTE key2[256] = {};

};

