#include "BoundObjectManager.h"

BoundObjectManager::BoundObjectManager()
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(std::make_unique<BoundObject>());
	}
}

void BoundObjectManager::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	for (int i = 0; i < size; i++)
	{
		object[i]->Initialize(dxCommon, textureManager);
	}
}

void BoundObjectManager::Update()
{
	for (auto& o : object)
	{
		o->Update();
	}
}

void BoundObjectManager::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}

void BoundObjectManager::SetPosition(Vector3 position)
{
	for (int i = 0; i < size; ++i)
	{
		object[i]->SetPosition(Vector3(position.x, position.y, position.z));
	}
}


