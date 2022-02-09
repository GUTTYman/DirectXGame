#include "SpherePlantManager.h"
SpherePlantManager::SpherePlantManager(int a)
{
	size = a;
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new SpherePlant());
	}
}

SpherePlantManager::~SpherePlantManager()
{
	for (const auto& x : object)
	{
		delete x;
	}
}
//DxCommonセット、テクスチャーマネージャーセット、テクスチャの番号指定、オブジェクトの根元（0番目）のサイズ指定
void SpherePlantManager::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, float firstSize)
{
	for (int i = 0; i < size; i++)
	{
		object[i]->Initialize(dxCommon, textureManager);
		object[i]->SetScale(easeOut(Vector3(firstSize + 1.5f , firstSize + 1.5f, firstSize + 1.5f), Vector3(0.3f, 0.3f, 0.3f), (float)i / size));
		object[i]->SetSinAngle(0-i);
		LarpColor(Vector3(), Vector3( 0.2f, 1.0f, 0.2f));

	}
}

void SpherePlantManager::Update()
{
		//一個目のオブジェクトのみ半径指定
		object[0]->SetRadius(0.1f);
		object[0]->Update();
	for (int i = 1; i < size; i++)
	{
		object[i]->SetTarget(object[i-1]->GetPosition());
		//植物の球同士の間は半径分開ける
		object[i]->SetRadius(object[i]->GetScale().x);
		object[i]->Update();
	}
}

void SpherePlantManager::Draw(DirectXCommon* dxCommon)
{
	for (int i = 1; i < size; i++)
	{
		object[i]->Draw(dxCommon);
	}
}

void SpherePlantManager::SetPosition(Vector3 position)
{
	for (int i = 0; i < size; ++i)
	{
		//object[i]->SetPosition(Vector3(position.x + sinf(i) * 2, position.y + cosf(i) * 2, position.z));
	}
}

void SpherePlantManager::SetTarget(Vector3 tPos)
{
		object[0]->SetTarget(tPos);
}

void SpherePlantManager::SetAngle(float a)
{
	for (auto& o : object)
	{
		o->SetAngle(a);
	}
}

void SpherePlantManager::LarpColor(Vector3 s,Vector3 e)
{
	for (int i = 0; i < size; ++i)
	{
		Vector3 c = easeIn(s, e, (float)i / size + 1.0f / size);
		object[i]->SetColor(c);
	}
}
