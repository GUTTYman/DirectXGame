#include "GamePad.h"

Xinput::Xinput()
{
	static int index = 0;
	ctrlState = {};
	mIndex = index;
	for (int i = 0; i < 4; i++)
	{
		stickTrigger[i] = true;
	}
	DWORD result = XInputGetState(index, &ctrlState);
	oldKey[0].key = XINPUT_UP;
	oldKey[1].key = XINPUT_DOWN;
	oldKey[2].key = XINPUT_LEFT;
	oldKey[3].key = XINPUT_RIGHT;
	oldKey[4].key = XINPUT_START;
	oldKey[5].key = XINPUT_BACK;
	oldKey[6].key = XINPUT_PUSHLSTICK;
	oldKey[7].key = XINPUT_PUSHRSTICK;
	oldKey[8].key = XINPUT_LB;
	oldKey[9].key = XINPUT_RB;
	oldKey[10].key = XINPUT_A;
	oldKey[11].key = XINPUT_B;
	oldKey[12].key = XINPUT_X;
	oldKey[13].key = XINPUT_Y;
	oldKey[14].key = XINPUT_LT;
	oldKey[15].key = XINPUT_RT;
	for (int i = 0; i < 16; ++i)
	{
		oldKey[i].flag = false;
	}
	++index;
}

Xinput::Xinput(int ctrlerIndex)
{
	mIndex = ctrlerIndex;
	XInputGetState(ctrlerIndex, &ctrlState);
	oldKey[0].key = XINPUT_UP;
	oldKey[1].key = XINPUT_DOWN;
	oldKey[2].key = XINPUT_LEFT;
	oldKey[3].key = XINPUT_RIGHT;
	oldKey[4].key = XINPUT_START;
	oldKey[5].key = XINPUT_BACK;
	oldKey[6].key = XINPUT_PUSHLSTICK;
	oldKey[7].key = XINPUT_PUSHRSTICK;
	oldKey[8].key = XINPUT_LB;
	oldKey[9].key = XINPUT_RB;
	oldKey[10].key = XINPUT_A;
	oldKey[11].key = XINPUT_B;
	oldKey[12].key = XINPUT_X;
	oldKey[13].key = XINPUT_Y;
	oldKey[14].key = XINPUT_LT;
	oldKey[15].key = XINPUT_RT;
	for (int i = 0; i < 16; ++i)
	{
		oldKey[i].flag = false;
	}
}

Xinput::~Xinput()
{
}

void Xinput::Update()
{
	for (int i = 0; i < 14; ++i)
	{
		if (ctrlState.Gamepad.wButtons & oldKey[i].key)
		{
			oldKey[i].flag = true;
		}
		else
		{
			oldKey[i].flag = false;
		}
	}
	if (ctrlState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)oldKey[14].flag = true;
	else oldKey[14].flag = false;
	if (ctrlState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)oldKey[15].flag = true;
	else oldKey[15].flag = false;
	//���̃t���[�����ł̃R���g���[���[�̏�Ԃ��擾
	DWORD result = XInputGetState(mIndex, &ctrlState);
}

bool Xinput::Push(XinputPadKey key)
{
	if (key != XINPUT_LT && key != XINPUT_RT)
	{
		if (ctrlState.Gamepad.wButtons & key)return true;
	}
	if (key == XINPUT_LT)
	{
		if (ctrlState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)return true;
	}
	else if (key == XINPUT_RT)
	{
		if (ctrlState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)return true;
	}
	return false;
}

bool Xinput::Trigger(XinputPadKey key)
{
	for (int i = 0; i < 14; ++i)
	{
		if (oldKey[i].key == key)
		{
			if (!oldKey[i].flag)
			{
				if (ctrlState.Gamepad.wButtons & key)
				{
					oldKey[i].flag = true;
					return true;
				}
			}
		}
	}
	if (key == oldKey[14].key && !oldKey[14].flag)
	{
		if (ctrlState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			oldKey[14].flag = true;
			return true;
		}
	}
	if (key == oldKey[15].key && !oldKey[15].flag)
	{
		if (ctrlState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			oldKey[15].flag = true;
			return true;
		}
	}
	return false;
}



float Xinput::GetRStickX()
{
	return ctrlState.Gamepad.sThumbRX / 32767.0f;
}

float Xinput::GetRStickY()
{
	return ctrlState.Gamepad.sThumbRY / -32767.0f;
}

float Xinput::GetLStickX()
{
	return ctrlState.Gamepad.sThumbLX / 32767.0f;
}

float Xinput::GetLStickY()
{
	return ctrlState.Gamepad.sThumbLY / -32767.0f;
}

bool Xinput::RStickXTrigger()
{
	if (stickTrigger[0])
	{
		if (GetRStickX() != 0.0f)
		{
			return true;
			stickTrigger[0] = false;
		}
		else
		{
			stickTrigger[0] = true;
			return false;
		}
	}
	return false;
}
bool Xinput::RStickYTrigger()
{
	if (stickTrigger[2])
	{
		if (GetRStickX() != 0.0f)
		{
			return true;
			stickTrigger[2] = false;
		}
		else
		{
			stickTrigger[2] = true;
			return false;
		}
	}
	return false;
}
bool Xinput::LStickXTrigger()
{

	if (stickTrigger[1])
	{
		if (GetLStickX() != 0.0f)
		{
			stickTrigger[1] = false;
			return true;
		}
	}
	else
	{
		if (GetLStickX() == 0.0f)
		{
			stickTrigger[1] = true;
			return false;
		}
	}
	return false;
}bool Xinput::LStickYTrigger()
{

	if (stickTrigger[3])
	{
		if (GetLStickX() != 0.0f)
		{
			stickTrigger[3] = false;
			return true;
		}
	}
	else
	{
		if (GetLStickX() == 0.0f)
		{
			stickTrigger[3] = true;
			return false;
		}
	}
	return false;
}