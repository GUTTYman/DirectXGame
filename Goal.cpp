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
	liveFlag = true;
	goalFlag = false;
}

void Goal::Update()
{
	if (liveFlag)
	{
		object->Update();
#pragma region
		//ホバリングの幅
		float range = 0.1f;
		//動き
		rotation.z += 1.0f;
		rotation.x += 1.0f;
		//色の変動
		color += Vector3(sin(a) * range * 2, sin(a) * range, sin(a) * range * 4);
		//サイズの変動
		scale += Vector3(sin(a) * range * 0.5f, sin(a) * range * 0.5f, sin(a) * range * 0.5f);
		//ホバリングの速さ
		a += 0.1f;

		bool hit = false;
		//プレイヤーとの当たり判定
		for (int i = 0; i < player.size(); i++)
		{
			if (SphereAndSphere(position, player[i]->GetPosition(), scale.x, 2, player[i]->GetLiveFlag(), liveFlag))
			{
				for (int i = 0; i < player.size(); i++)
				{
					player[i]->SetVelocity(Vector3());
				}
				//音再生
				GameObject::GetSoundManager()->PlayWave(AudioIndex::GOAL);
				//ゴール起動
				hit = true;
			}
		}
		particle->Update(position);
		//ゴールした時の演出
		if (hit)
		{
			goalFlag = true;
		}
		//大きさ初期化
		if (goalFlag)
		{
			a = 0.0f;
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
