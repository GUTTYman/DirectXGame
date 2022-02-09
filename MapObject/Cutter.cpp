#include "Cutter.h"

std::vector<Player*> Cutter::player;

Cutter::Cutter()
{
	object = std::make_unique< Object3d>();
}
Cutter::~Cutter()
{
}

void Cutter::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{

	object->Initialize(modelLoader->GetModel(CUTTER));

	float rScale= rand() % 5 + 3;
	liveFlag = true;
	scale = Vector3(rScale, rScale, rScale); 
	color = Vector3();
	object->SetColor(color);
	object->SetScale(scale);

}

void Cutter::Update()
{

	if (liveFlag)
	{
#pragma region  Cutter‘€ì
		//ƒvƒŒƒCƒ„[‚Æ‚Ì“–‚½‚è”»’è
		for (int i = 0; i < player.size(); i++)
		{
			if (SphereAndSphere(position, player[i]->GetPosition(), scale.x, player[i]->GetScale().x, player[i]->GetLiveFlag(), !player[i]->GetDead()))
			{
				player[i]->SetDead(true);
			}

		}
		rotation.z += 8;


#pragma endregion
	}
	object->Update();
	object->SetPosition(position);
	object->SetRotation(rotation);
}

void Cutter::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
