#include "Bomb.h"

std::vector<Player*> Bomb::player;

Bomb::Bomb()
{
	object = std::make_unique< Object3d>();
}
Bomb::~Bomb()
{
}

void Bomb::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(SPIKEBALL));
	int r = rand() % 50 + 20;
	scale = Vector3(r/10.0f,r / 10.0f,r / 10.0f);
	color = Vector3();
	a = 0.0f;
	waitTime = 0.0f;
	liveFlag = true;
	emitte = false;
	pCount = 0;
}

void Bomb::Update(float gameTime)
{
	if (liveFlag)
	{
#pragma region  Bomb����
		//�g�k�̕�
		static float range = 0.05f;
		if (a <6.62f)
		{
			//�X�P�[���ƃJ���[�Ōۓ���\��
			scale += Vector3(sin(a) * range, sin(a) * range, sin(a) * range);
			color += Vector3(sin(a) * range , 0.0f, 0.0f);
			a += 0.3f * gameTime;
		}
		else
		{
			waitTime+=1.0f * gameTime;
		}
		//���̊Ԋu
		if (waitTime > 60)
		{
			color = Vector3();
			waitTime = 0.0f;
			a = 0.0f;
		}
		if (!emitte)
		{
			//�v���C���[�Ƃ̓����蔻��
			for (int i = 0; i < player.size(); i++)
			{
				if (SphereAndSphere(position, player[i]->GetPosition(), scale.x, player[i]->GetScale().x, player[i]->GetLiveFlag(), liveFlag))
				{
					//�������Đ�
					soundManager->PlayWave(AudioIndex::EXPLOSION);

					for (int j = 0; j < player.size(); j++)
					{
						if (SphereAndSphere(position, player[j]->GetPosition(), scale.x * 3, player[j]->GetScale().x, player[i]->GetLiveFlag(), liveFlag))
						{
							//�t�߂ɂ���v���C���[�����˕Ԃ�
							Vector3 direction = Vector3(player[j]->GetPosition() - position).normalize();
							if (!player[i]->GetHitBlock())
							{
								//���ɐG��ĂȂ������畁�ʂɒ��˕Ԃ�
								player[j]->SetVelocity(direction * 3);
							}
							else
							{
								//���ɐG��Ă����珰�ɂ߂荞�܂Ȃ��悤�ɒ��˕Ԃ�
								player[j]->SetVelocity(Vector3(direction.x,0.4f,0));
							}
						}
					}
					//�t�F�[�X���΂�Flag
					emitte = true;
				}
			}
		}
#pragma endregion
	}

	if (emitte)
	{
		if (pCount < 120)
		{
			//�W�I���g���V�F�[�_�[�Ńt�F�[�X���΂�
			pCount+=2.0f * gameTime;
			object->SetNormalLength(Vector3(pCount, pCount, 0) * gameTime);
			color = Vector3(0.5f, 0.0f, 0.0f);
		}
		else
		{
			emitte = false;
			liveFlag = false;
		}
	}
	else
	{
		object->SetNormalLength(Vector3());
		pCount = 0;
	}
		object->Update();
		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);
		object->SetColor(color);
}

void Bomb::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
