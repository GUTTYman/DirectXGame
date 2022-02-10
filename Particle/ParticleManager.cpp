#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Particle());
	}
}

ParticleManager::~ParticleManager()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void ParticleManager::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Initialize(dxCommon, textureManager);
		float b = 360.0f / size * i;
		Vector3 a = Vector3(sin(b), cos(b), 0);
		object[i]->SetVelocity(a);
	}
}

void ParticleManager::Update(Vector3 p)
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Update();
		if (object[i]->GetLiveFlag())
		{
			object[i]->SetScale(object[i]->GetScale() - Vector3(0.05f, 0.05f, 0.05f));
		}
		else
		{
			object[i]->SetPosition(p);
			float b = 360.0f / size * i;
			Vector3 a = Vector3(sin(b/2.0f), cos(b/2.0f), 0);
			object[i]->SetVelocity(a);
		}
	}
}

void ParticleManager::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}

void ParticleManager::SetPosition(Vector3 position)
{
	for (int i = 0; i < object.size(); ++i)
	{
		object[i]->SetPosition(Vector3(position.x, position.y, position.z));
	}
}

void ParticleManager::SetLiveFlag(bool b)
{
	for (auto& o : object)
	{
		o->SetLiveFlag(b);
	}
}


