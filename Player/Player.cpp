#include "Player.h"
Player::Player()
{
	object = std::make_unique< Object3d>();
	tail = std::make_unique< TailManager>(8);
}
Player::~Player()
{
}

void Player::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	//�I�u�W�F�N�g�̏�����
	object->Initialize(modelLoader->GetModel(PLAYER));
	//�K���̏�����
	tail->Initialize(dxCommon, textureManager, 1.5f);
	tail->LerpColor(Vector3(),Vector3(0,1,0));

	//�p�����[�^�[�����l
	scale = Vector3(3, 3, 3);
	color = Vector3(1,1,1);
	object->SetColor(color);
	rotation = Vector3();
	liveFlag = false;
	hitBlock = false;
	dead = false;
	a = 0;
	power = 1.0f;
	powerCount = 0.0f;
}

void Player::Update(float gameTime)
{
	if (liveFlag)
	{
		tail->SetScale(scale);
		//Player����
		Control(gameTime);

		hitBlock = false;	//�ǂȂǂɂ��������Ă����ꍇ������聪���̍s��true	�����̍s��false�ƂȂ�
#pragma region �����W���v�Z
		static float maxCount = 500.0f;
		power = lerp(Vector3(1.0f, 0.0f, 0.0f), Vector3(2.0f, 0.0f, 0.0f), powerCount / maxCount).x;
		if (powerCount < maxCount)
		{
			powerCount++;
		}
#pragma endregion

		//�̂̌�����Velocity���狁�߂�
		float direction = atan2f(velocity.y * gameTime, velocity.x * gameTime);
		//�����ۊp�x�Z�b�g
		tail->SetAngle(-direction - 1.57f);
		if (velocity.x * gameTime >= 0.0f)
		{
			rotation = Vector3(0, 0, direction * 57.32484076433121f);
		}
		else if (velocity.x * gameTime < 0.0f)
		{
			rotation = Vector3(180, 0, atan2f(-velocity.y * gameTime, velocity.x * gameTime) * 57.32484076433121f);
		}

		//���񂾂�(60�t���[���̊�)
		if (dead)
		{
			a += 2;
			//�J�E���g���Ă��玀�S����ɂȂ�
			if (a > 60)
			{
				liveFlag = false;
				dead = false;
			}
		}
		else
		{
			position += velocity * gameTime;
			a = 0;
		}
		//�W�I���g���V�F�[�_�[�Ńt�F�[�X���U�点��
		object->SetNormalLength(Vector3(a, a, 0) * gameTime);
		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);
	}
		object->Update();

	//�����ۂ̍X�V
	tail->SetTarget(position);
	tail->Update(gameTime);
}



void Player::Control(float gameTime)
{
	//�R���g���[���[����
	velocity.x += pad->GetLStickX() * 0.015f;
	//������̑���
	if (input->Push(DIK_UP) || pad->Push(XINPUT_A))
	{
		velocity.y += 0.02f;
	}
	else
	{
		if (!hitBlock)
		{
			velocity.y -= 0.03f * gameTime;
		}
	}
	//�L�[�{�[�h���͂ł̍��E�ړ�
	if (input->Push(DIK_LEFT) || input->Push(DIK_RIGHT))
	{
		if (input->Push(DIK_LEFT))
		{
			velocity.x -= 0.005f;
		}
		if (input->Push(DIK_RIGHT))
		{
			velocity.x += 0.005f;
		}
	}
	else if (pad->GetLStickX() == 0.0f)	//���E�ړ��̑��삪����Ă��Ȃ��Ƃ�
	{
		//����
		if (abs(velocity.x) > 0.1f)
		{
			if (velocity.x > 0.1f)
			{
				velocity.x -= 0.001f;
			}
			if (velocity.x < -0.1f)
			{
				velocity.x += 0.001f;
			}
		}
	}
}

void Player::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
		
		if (!dead)
		{
			tail->Draw(dxCommon);
		}
	}
}

InputNum Player::GetInput()
{
	if (input->Push(DIK_LEFT) || pad->GetLStickX() < 0.0f)
	{
		return LEFT;
	}
	if (input->Push(DIK_RIGHT) || pad->GetLStickX() > 0.0f)
	{
		return RIGHT;
	}
	if (input->Push(DIK_UP) || pad->Push(XINPUT_A))
	{
		return UP;
	}
		return NONE;
}

void Player::SetDead(bool b)
{
	dead = b;
	if (b)
	{
		soundManager->PlayWave(AudioIndex::DEAD);
	}
}
