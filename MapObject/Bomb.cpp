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
#pragma region  Bomb操作
		//拡縮の幅
		static float range = 0.05f;
		if (a <6.62f)
		{
			//スケールとカラーで鼓動を表現
			scale += Vector3(sin(a) * range, sin(a) * range, sin(a) * range);
			color += Vector3(sin(a) * range , 0.0f, 0.0f);
			a += 0.3f * gameTime;
		}
		else
		{
			waitTime+=1.0f * gameTime;
		}
		//脈の間隔
		if (waitTime > 60)
		{
			color = Vector3();
			waitTime = 0.0f;
			a = 0.0f;
		}
		if (!emitte)
		{
			//プレイヤーとの当たり判定
			for (int i = 0; i < player.size(); i++)
			{
				if (SphereAndSphere(position, player[i]->GetPosition(), scale.x, player[i]->GetScale().x, player[i]->GetLiveFlag(), liveFlag))
				{
					//爆発音再生
					soundManager->PlayWave(AudioIndex::EXPLOSION);

					for (int j = 0; j < player.size(); j++)
					{
						if (SphereAndSphere(position, player[j]->GetPosition(), scale.x * 3, player[j]->GetScale().x, player[i]->GetLiveFlag(), liveFlag))
						{
							//付近にいるプレイヤーも跳ね返す
							Vector3 direction = Vector3(player[j]->GetPosition() - position).normalize();
							if (!player[i]->GetHitBlock())
							{
								//床に触れてなかったら普通に跳ね返す
								player[j]->SetVelocity(direction * 3);
							}
							else
							{
								//床に触れていたら床にめり込まないように跳ね返す
								player[j]->SetVelocity(Vector3(direction.x,0.4f,0));
							}
						}
					}
					//フェースを飛ばすFlag
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
			//ジオメトリシェーダーでフェースを飛ばす
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
