#include "SpherePlant.h"

std::vector<Player*> SpherePlant::player;
std::vector<ShootEnemy*> SpherePlant::sEnemies;
SpherePlant::SpherePlant()
{
	object = std::make_unique< Object3d>();
}
SpherePlant::~SpherePlant()
{
}

void SpherePlant::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(SPIKEBALL));

	color = Vector3(1,1,1);
	scale = Vector3(1, 1, 1);
	target = Vector3(0.0f, 0.0f, 0.0f);
	nowangle = 0; 
	a = 0.0f;
	sinangle = 0.02f;
	radius = 1.5f;
	addangle = 0.0f;
	liveFlag = true;
	//�f�t�H���g��+�P���]��-�P
	reverse = 1;
}

void SpherePlant::Update()
{
	reverse = 1;
	//�A���̊p�x�ɂ���ĉ��Z���������ς���	
	if (addangle > 1.67f && addangle < 4.81f) { reverse = -1; }

	//liveFlag��True�̊Ԃ̂ݍX�V����������
	if (liveFlag)
	{
		object->Update();
#pragma region  SpherePlant����

		position = Vector3(target.x + (sinf(nowangle + addangle) * radius), target.y + (cosf(nowangle + addangle) * radius), target.z);


		float stiffness = 0.3f;	//�߂鋭��
		float damping = 0.9f;	//�����̌���
		float mass = 10.0f;		//�d��
		float force = stiffness * (-nowangle);
		float accel = force / mass;
		velocity.x = damping * (velocity.x + accel);

		//Player�̓����蔻��
		for (int i = 0; i < player.size(); i++)
		{
			//�v���C���[���G������o�E���h
			if (player[i]->GetLiveFlag())
			{
				if (SphereAndSphere(position, player[i]->GetPosition(), scale.x, player[i]->GetScale().x))
				{
					if (player[i]->GetVelocity().x == 0.0f)
					{
						return;
					}
					else
					{
						nowangle += (player[i]->GetVelocity().x * reverse);
					}
				}
			}
		}
		//�_���G�̓����蔻��
		for (int i = 0; i < sEnemies.size(); i++)
		{
			if (sEnemies[i]->GetLiveFlag())
			{
				if (SphereAndSphere(position, sEnemies[i]->GetPosition(), scale.x, sEnemies[i]->GetScale().x * 3))
				{
					nowangle -= sEnemies[i]->GetVelocity().x;
				}
			}
		}

		//���R�ȗh��
		velocity.x += (sin(a) * 0.01f);
		a += sinangle;
		//�������p�x�ɉ��Z
		nowangle += velocity.x;
#pragma endregion
#pragma endregion
		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);
		object->SetColor(color);
	}
}
void SpherePlant::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}

void SpherePlant::SetPlayer(std::vector<Player*> p)
{
	player = p;
}

void SpherePlant::SetShootEnemy(std::vector<ShootEnemy*> e)
{
	sEnemies = e;
}
