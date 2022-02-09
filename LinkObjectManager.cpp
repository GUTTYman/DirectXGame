#include "LinkObjectManager.h"

LinkObjectManager::LinkObjectManager(int size)
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new LinkObject());
	}
}

LinkObjectManager::~LinkObjectManager()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void LinkObjectManager::Initialize(DirectXCommon* dxCommon, TextureManager*textureManager)
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Initialize(dxCommon,textureManager);
		object[i]->SetScale(object[i]->GetScale() + Vector3(i * 0.03f, i * 0.03f, 1));
	}
}

void LinkObjectManager::Update()
{
	object[0]->Update();
	for (int i = 1; i < object.size(); i++)
	{
		object[i]->SetTarget(object[i - 1]->GetPosition());
		object[i]->Update();
	}

	for (int i = 1; i < object.size(); i++)
	{
		object[i - 1]->SetVelocity(object[i]->GetVelocity() / 2);
	}
	object[object.size() - 2]->SetVelocity(object[object.size()-1]->GetVelocity() / 2);
}

void LinkObjectManager::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}

void LinkObjectManager::SetTarget(Vector3 aPos)
{
	object[0]->SetTarget(aPos);
}
void LinkObjectManager::IsReverse(bool r)
{
	for (auto& o : object)
	{
		o->IsReverse(r);
	}
}
