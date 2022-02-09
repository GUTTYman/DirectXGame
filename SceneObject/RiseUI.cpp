#include "RiseUI.h"

RiseUI::RiseUI()
{
	object = std::make_unique< Object3d>();
}
RiseUI::~RiseUI()
{
}

void RiseUI::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{

	object->Initialize(modelLoader->GetModel(X3));
	liveFlag = true;
	scale = Vector3(10,10,10);
	color = Vector3(0,1,0);
	rotation = Vector3(0,-90,0);
	object->SetColor(color);
	object->SetScale(scale);
	object->SetRotation(rotation);

}

void RiseUI::Update()
{

	object->SetAlpha(alpha);
	object->SetPosition(position);
	object->Update();
}

void RiseUI::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
