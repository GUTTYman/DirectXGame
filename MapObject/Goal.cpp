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
		//ホバリングの幅
		float range = 0.1f;
		//動き
		rotation += Vector3(1.0f,0.0f,1.0f) * gameTime;
		//色の変動
		color += Vector3(sin(a) * range * 2, sin(a) * range, sin(a) * range * 4);
		//サイズの変動
		scale += Vector3(sin(a) * range * 0.5f, sin(a) * range * 0.5f, sin(a) * range * 0.5f);
		//ホバリングの速さ
		a += 0.1f * gameTime;
		if (!goal)
		{
			//プレイヤーとの当たり判定
			for (int i = 0; i < player.size(); i++)
			{
				if (SphereAndSphere(position, player[i]->GetPosition(), scale.x * 2, 2, player[i]->GetLiveFlag(), liveFlag))
				{
					for (int i = 0; i < player.size(); i++)
					{
						player[i]->SetVelocity(Vector3());
					}
					//音再生
					GameObject::GetSoundManager()->PlayWave(AudioIndex::GOAL);
					//ゴール起動
					goal = true;
				}
			}
			particle->Update(position);
		}
		//ゴールしてからシーン切り替えまでのインターバル
		if (goal)
		{
			goalCount++;
			//スケール変更(大→小)
			scale = lerp(Vector3(5.0f, 5.0f, 5.0f), Vector3(), goalCount / 60.0f);

			if (goalCount > 60)
			{
				next = true;
			}
		}
		

		//値初期化
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
