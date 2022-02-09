#include "RiseObject.h"

std::vector<Player*> RiseObject::player;

RiseObject::RiseObject()
{
	object = std::make_unique< Object3d>();
	UI = std::make_unique< RiseUI>();
}
RiseObject::~RiseObject()
{
}

void RiseObject::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(ModelIndex::RISE));
	rotation = Vector3(0, -90, 0);
	scale = Vector3(2.5f, 2.5f, 2);
	a = 0.0f;
	waitTime = 0;
	liveFlag = true;
	//UIの初期化
	UI->Initialize(dxCommon,textureManager);
	uiCount = 0;
}
void RiseObject::Update()
{

	if (liveFlag)
	{

#pragma region  RiseObject操作
		//拡縮の幅
		static float range = 0.07f;
		if (a < 6.31f)
		{
			//鼓動
			scale += Vector3(sin(a) * range, sin(a) * range, sin(a) * range);
			a += 0.3f;
		}
		else
		{
			waitTime++;
		}
		//脈の間隔
		if (waitTime > 7)
		{
			waitTime = 0;
			a = 0.0f;
		}
#pragma endregion
		//UICountセット
		uiCount = 0;
	}
	else
	{
		uiCount++;
		if (uiCount < 60)
		{
			//UIの更新
			UI->SetPosition(position + Vector3(0,uiCount/10.0f,-3));
			UI->SetAlpha(lerp(1.0f, 0.0f, uiCount / 60.0f));
			UI->Update();
		}
	}
	object->Update();
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
}

void RiseObject::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
	else
	{
		//UIが60フレームだけ描画される
		if (uiCount < 60)
		{
			UI->Draw(dxCommon);
		}
	}
}

void RiseObject::PlayerRise(PlayerEmitter* p, int a,DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	if (liveFlag)
	{
		//プレイヤーとの当たり判定
		for (int i = 0; i < player.size(); i++)
		{
			if (SphereAndSphere(position, player[i]->GetPosition(), scale.x, player[i]->GetScale().x, player[i]->GetLiveFlag(), liveFlag))
			{
				for (int i = 0; i < 3; i++)
				{
					p->Rise(position, dxCommon, textureManager, texNum);
				}
				GameObject::GetSoundManager()->PlayWave(AudioIndex::RISEUP);
				liveFlag = false;
			}
		}
	}
}
