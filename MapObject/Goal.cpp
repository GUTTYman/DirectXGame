#include "Goal.h"

std::vector<Player*> Goal::player;
Goal::Goal()
{
	object = std::make_unique< Object3d>();
	particle = std::make_unique< ChargeParticle>();
}
Goal::~Goal()
{
}

void Goal::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(CUBE));

	particle->Initialize(dxCommon, textureManager);
	color = Vector3(0.5f, 0.2f, 0.3f);
	scale = Vector3(1, 1, 1);
	a = 0.0f;
	goalCount = 0;
	liveFlag = true;
	next = false;
	goal = false;
}

void Goal::Update(float gameTime)
{
	if (liveFlag)
	{
		object->Update();
#pragma region
		//�z�o�����O�̕�
		float range = 0.1f;
		//����
		rotation += Vector3(1.0f,0.0f,1.0f) * gameTime;
		//�F�̕ϓ�
		color += Vector3(sin(a) * range * 2, sin(a) * range, sin(a) * range * 4);
		//�T�C�Y�̕ϓ�
		scale += Vector3(sin(a) * range * 0.5f, sin(a) * range * 0.5f, sin(a) * range * 0.5f);
		//�z�o�����O�̑���
		a += 0.1f * gameTime;
		if (!goal)
		{
			//�v���C���[�Ƃ̓����蔻��
			for (int i = 0; i < player.size(); i++)
			{
				if (SphereAndSphere(position, player[i]->GetPosition(), scale.x * 2, 2, player[i]->GetLiveFlag(), liveFlag))
				{
					for (int i = 0; i < player.size(); i++)
					{
						player[i]->SetVelocity(Vector3());
					}
					//���Đ�
					GameObject::GetSoundManager()->PlayWave(AudioIndex::GOAL);
					//�S�[���N��
					goal = true;
				}
			}
			particle->Update(position);
		}
		//�S�[�����Ă���V�[���؂�ւ��܂ł̃C���^�[�o��
		if (goal)
		{
			goalCount++;
			//�X�P�[���ύX(�偨��)
			scale = lerp(Vector3(5.0f, 5.0f, 5.0f), Vector3(), goalCount / 60.0f);

			if (goalCount > 60)
			{
				next = true;
			}
		}
		

		//�l������
		if (next)
		{
			a = 0.0f;
			scale = Vector3(1, 1, 1);
			goalCount = 0;
			goal = false;
		}

#pragma endregion
		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetColor(color);
		object->SetScale(scale);
	}
}
void Goal::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
		particle->Draw(dxCommon);
	}
}
