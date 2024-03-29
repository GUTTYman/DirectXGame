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
	Xinput(); //中身で勝手にコントローラーの番号を決めて生成
	Xinput(int ctrlerIndex); //2つ目以降のコントローラー生成
	~Xinput();
	void Update();
	//押されているか
	bool Push(XinputPadKey key);
	//1フレーム押されたか
	bool Trigger(XinputPadKey key);
	//スティックの倒した強さ取得
	float GetRStickX();
	float GetRStickY();
	float GetLStickX();
	float GetLStickY();
	//スティックを倒した時のトリガー
	bool RStickXTrigger();
	bool RStickYTrigger();
	bool LStickXTrigger();
	bool LStickYTrigger();
};

