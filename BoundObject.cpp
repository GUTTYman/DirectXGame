#include "BoundObject.h"

std::vector<Player*> BoundObject::player;

BoundObject::BoundObject()
{
	object = std::make_unique< Object3d>();
	particle = std::make_unique< TouchParticle>();
}

BoundObject::~BoundObject()
{
	
}

void BoundObject::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(KINOKO));
	float randScale = rand() % 90;
	scale = Vector3(randScale / 100.0f + 0.2f, randScale / 100.0f + 0.5f, randScale / 100.0f + 0.5f);
	color = Vector3(0.0f,0.2f,0.0f);
	target = Vector3(10.0f, 0.0f, 0.0f);
	accel = 0.0f;
	//�p�[�e�B�N��
	particle->Initialize(modelLoader->GetModel(POINTVERTEX));
	liveFlag = true;
}

void BoundObject::Update()
{
	if (liveFlag)
	{
		object->Update();
		particle->Update(position + Vector3(0, 0, 3));

#pragma region  BoundObject����
		//�ł�
		float stiffness = 0.5f;
		//����
		float damping = 0.9f;
		//�d��
		float mass = 10.0f;

		float force = stiffness * (- rotation.z);
		accel = force/ mass;
		velocity.x = damping * (velocity.x + accel);

		//�J�v�Z���̒[����
		Vector3 end = Vector3(position.x, position.y + scale.y * 3, 0);
		for (int i = 0; i < player.size(); i++)
		{
			if (player[i]->GetLiveFlag())
			{
				//�v���C���[���G������o�E���h
				if (SphereAndCapsule(player[i]->GetPosition(), player[i]->GetScale().x, end, position, scale.x, player[i]->GetLiveFlag()))
				{
					if (player[i]->GetVelocity().x != 0)
					{
						particle->SetSpawnFlag(true);
					}
					//�p�x�ɉ��Z
					rotation.z -= player[i]->GetVelocity().x * 10;
				}
			}
		}

#pragma endregion

		rotation.z += velocity.x;
		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);
		object->SetColor(color);
	}
}
void BoundObject::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
		particle->Draw(dxCommon);
	}
}

void BoundObject::SetPlayer(std::vector<Player*> p)
{
	player = p;
}
