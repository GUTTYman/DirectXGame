#include "FireParticle.h"


FireParticle::FireParticle()
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Particle());
	}
}

FireParticle::~FireParticle()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void FireParticle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Initialize(dxCommon, textureManager);
		//サイズをランダムで設定
		float rs = rand() % 10 + 3;
		object[i]->SetScale(Vector3(rs / 10, rs / 10, rs / 10));
	}
	red = false;
	int a = 0;
}

void FireParticle::Update(Vector3 p)
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Update();
		if (object[i]->GetLiveFlag())
		{
			//サイズの縮小とカラーの移り変わり
			object[i]->SetScale(object[i]->GetScale() - Vector3(0.01f, 0.01f, 0.01f));
		}
		else
		{
			//サイズとポジション指定
			float rs = rand() % 20 + 5;
			object[i]->SetScale(Vector3(rs / 10, rs / 10, 0.1f));
			float rnd = rand() % 40 - 20;
			object[i]->SetPosition(p + Vector3(0, rnd / 10, 0));
		}
	}

	//順番に煙を出す
	if (a < object.size())
	{
		object[a]->SetLiveFlag(true);
	}
	else
	{
		a = 0;
	}

	a++;
}

void FireParticle::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}

void FireParticle::SetPosition(Vector3 position)
{
	for (int i = 0; i < object.size(); ++i)
	{
		object[i]->SetPosition(Vector3(position.x, position.y, position.z));
	}
}

void FireParticle::SetLiveFlag(bool b)
{
	for (auto& o : object)
	{
		o->SetLiveFlag(b);
	}
}


