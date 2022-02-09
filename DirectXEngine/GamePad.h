#pragma once
#include<Windows.h>
#include<Xinput.h>
#include<stdio.h>

#pragma comment (lib, "xinput.lib")
enum XinputPadKey
{
	XINPUT_UP = 0x0001,    //0
	XINPUT_DOWN = 0x0002,	//1
	XINPUT_LEFT = 0x0004,	//2
	XINPUT_RIGHT = 0x0008,	//3
	XINPUT_START = 0x0010,	//4
	XINPUT_BACK = 0x0020,	//5
	XINPUT_PUSHLSTICK = 0x0040,//6
	XINPUT_PUSHRSTICK = 0x0080,//7
	XINPUT_LB = 0x0100,	//8
	XINPUT_RB = 0x0200,	//9
	XINPUT_A = 0x1000,		//10
	XINPUT_B = 0x2000,		//11
	XINPUT_X = 0x4000,		//12
	XINPUT_Y = 0x8000,		//13
	XINPUT_LT = -1,		//14
	XINPUT_RT = -2,		//15
};

struct CheckKey
{
	bool flag;
	XinputPadKey key;
};

class Xinput
{
private:
	int mIndex;
	XINPUT_STATE ctrlState;
	CheckKey oldKey[16];
	bool stickTrigger[4];
public:
	Xinput(); //���g�ŏ���ɃR���g���[���[�̔ԍ������߂Đ���
	Xinput(int ctrlerIndex); //2�ڈȍ~�̃R���g���[���[����
	~Xinput();
	void Update();
	//������Ă��邩
	bool Push(XinputPadKey key);
	//1�t���[�������ꂽ��
	bool Trigger(XinputPadKey key);
	//�X�e�B�b�N�̓|���������擾
	float GetRStickX();
	float GetRStickY();
	float GetLStickX();
	float GetLStickY();
	//�X�e�B�b�N��|�������̃g���K�[
	bool RStickXTrigger();
	bool RStickYTrigger();
	bool LStickXTrigger();
	bool LStickYTrigger();
};

