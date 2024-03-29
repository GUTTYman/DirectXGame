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
	//デフォルトは+１反転時-１
	reverse = 1;
}

void SpherePlant::Update()
{
	reverse = 1;
	//植物の角度によって加算する方向を変える	
	if (addangle > 1.67f && addangle < 4.81f) { reverse = -1; }

	//liveFlagがTrueの間のみ更新処理をする
	if (liveFlag)
	{
		object->Update();
#pragma region  SpherePlant操作

		position = Vector3(target.x + (sinf(nowangle + addangle) * radius), target.y + (cosf(nowangle + addangle) * radius), target.z);


		float stiffness = 0.3f;	//戻る強さ
		float damping = 0.9f;	//反動の減衰
		float mass = 10.0f;		//重さ
		float force = stiffness * (-nowangle);
		float accel = force / mass;
		velocity.x = damping * (velocity.x + accel);

		//Playerの当たり判定
		for (int i = 0; i < player.size(); i++)
		{
			//プレイヤーが触ったらバウンド
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
		//狙撃敵の当たり判定
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

		//自然な揺れ
		velocity.x += (sin(a) * 0.01f);
		a += sinangle;
		//動きを角度に加算
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
