#include "ChargeParticle.h"

ChargeParticle::ChargeParticle()
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Particle());
	}
}

ChargeParticle::~ChargeParticle()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void ChargeParticle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Initialize(dxCommon, textureManager);
		object[i]->SetScale(Vector3(0.3f, 0.3f, 0.3f));
		object[i]->SetRotation(Vector3(0, 0, 45));
		object[i]->SetLiveFlag(true);
		//カラーをランダムでセット
		float rR = rand() % 10;
		float rG = rand() % 10;
		float rB = rand() % 10;
		object[i]->SetColor(Vector3(rR, rG, rB) / 10.0f);
	}
	a = 0;
	spawn = false;
	end = false;
}

void ChargeParticle::Update(Vector3 p)
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Update();
		if (object[i]->GetLiveFlag())
		{
			Vector3 dir = p - object[i]->GetPosition();
			object[i]->SetVelocity(dir / 10);
		}
		else
		{
			//湧くポジションをランダムでセット	
			float rx = rand() % 20 - 10;
			float ry = rand() % 20 - 10;
			Vector3 b = Vector3(rx, ry, 0);
			object[i]->SetPosition(p + b);
		}
		if (object[i]->GetTime() > 10)
		{
			object[i]->SetLiveFlag(false);
		}
	}
		//順番に粒子を出す
	if (a < object.size())
	{
		object[a]->SetLiveFlag(true);
	}
	else
	{
		spawn = false;
		end = true;
		a = 0;
	}
	a++;
}

void ChargeParticle::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}

void ChargeParticle::SetPosition(Vector3 position)
{
	for (int i = 0; i < object.size(); ++i)
	{
		object[i]->SetPosition(Vector3(position.x, position.y, position.z));
	}
}

void ChargeParticle::SetLiveFlag(bool b)
{
	for (auto& o : object)
	{
		o->SetLiveFlag(b);
	}
}

bool ChargeParticle::EndCharge()
{
	if (end)
	{
		end = false;
		return true;
	}
	else
	{
		return false;
	}
}



