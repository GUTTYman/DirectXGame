#include "RiseObject.h"

std::vector<Player*> RiseObject::player;

RiseObject::RiseObject()
{
	object = std::make_unique< Object3d>();
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

}
void RiseObject::Update()
{

	if (liveFlag)
	{

#pragma region  RiseObject‘€ì
		//Šgk‚Ì•
		static float range = 0.07f;
		if (a < 6.31f)
		{
			//ŒÛ“®
			scale += Vector3(sin(a) * range, sin(a) * range, sin(a) * range);
			a += 0.3f;
		}
		else
		{
			waitTime++;
		}
		//–¬‚ÌŠÔŠu
		if (waitTime > 7)
		{
			waitTime = 0;
			a = 0.0f;
		}
#pragma endregion
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
}

void RiseObject::PlayerRise(PlayerEmitter* p, int a,DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	if (liveFlag)
	{
		//ƒvƒŒƒCƒ„[‚Æ‚Ì“–‚½‚è”»’è
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
