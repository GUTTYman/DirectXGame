#include "Back.h"

Back::Back()
{
	object = std::make_unique< Object3d>();
}
Back::~Back()
{
}

void Back::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(BACK1));
	
	liveFlag = true;
	position = Vector3(0, -130, 500);
	rotation = Vector3(0, 180, 0);
	color = Vector3(0.4f,0.45f,0.4f);
	scale = Vector3(40, 40, 40);
}

void Back::Update()
{
	if (liveFlag)
	{
		object->Update();
#pragma region

#pragma endregion
		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetColor(color);
		object->SetScale(scale);
	}
}
void Back::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
