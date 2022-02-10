#include "TailManager.h"
TailManager::TailManager(int a)
{
	size = a;
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Tail());
	}
}

TailManager::~TailManager()
{
	for (const auto& x : object)
	{
		delete x;
	}
}
//DxCommonセット、テクスチャーマネージャーセット、テクスチャの番号指定、オブジェクトの根元（0番目）のサイズ指定
void TailManager::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, float firstSize)
{
	for (int i = 0; i < size; i++)
	{
		object[i]->Initialize(dxCommon, textureManager);
		object[i]->SetSinAngle(0-i);
		LerpColor(Vector3(0.2f, 1.0f, 0.2f), Vector3(0.2f, 0.2f, 1));
	}
	SetScale(Vector3(firstSize, firstSize, firstSize));
}

void TailManager::Update(float gameTime)
{
	//一個目のオブジェクトのみ半径指定
	object[0]->SetRadius(0.1f);
	object[0]->Update(gameTime);
	for (int i = 1; i < size; i++)
	{
		object[i]->SetTarget(object[i - 1]->GetPosition());
		//植物の球同士の間は半径分開ける
		object[i]->SetRadius(object[i]->GetScale().x);
		object[i]->Update(gameTime);
	}
}

void TailManager::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}

void TailManager::SetPosition(Vector3 position)
{
	for (int i = 0; i < size; ++i)
	{
		//object[i]->SetPosition(Vector3(position.x + sinf(i) * 2, position.y + cosf(i) * 2, position.z));
	}
}

void TailManager::SetScale(Vector3 scale)
{
	for (int i = 0; i < size; ++i)
	{
		object[i]->SetScale(easeOut(Vector3(scale.x, scale.y, scale.z), Vector3(scale.x / 10.0f, scale.y / 10.0f, scale.z / 10.0f), (float)i / size));
	}
}

void TailManager::SetTarget(Vector3 tPos)
{
		object[0]->SetTarget(tPos);
}

void TailManager::SetNormalLength(Vector3 v)
{
	for (auto& o : object)
	{
		o->SetNormalLength(v);
	}

}

void TailManager::SetAngle(float a)
{
	for (auto& o : object)
	{
		o->SetAngle(a);
	}
}

void TailManager::LerpColor(Vector3 s,Vector3 e)
{
	for (int i = 0; i < size; ++i)
	{
		Vector3 c = easeIn(s, e, (float)i / size + 1.0f / size);
		object[i]->SetColor(c);
	}
}
