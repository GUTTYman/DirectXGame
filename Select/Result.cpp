#include "Result.h"
Result::Result()
{
	size = 2;
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Select());
	}
}

Result::~Result()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void Result::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	num = 0;
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Initialize(dxCommon, textureManager, SELECTBOX1);
		object[i]->SetPosition(Vector3(-5 + 10 * i, -5, -30));
	}
}

void Result::Update()
{
	////操作取得
	//if (Select::GetIsInput() == 1 || Select::GetIsInput() == -1)
	//{
	//	if (Select::GetIsInput() == 1)
	//	{
	//		num = 1;
	//		printf("Go Title\n");
	//	}
	//	if (Select::GetIsInput() == -1)
	//	{
	//		num = 0;
	//		printf("Go StageSelect\n");
	//	}
	//}
	//ステージ決定

	for (int i = 0; i < object.size(); i++)
	{
		//if (num == i)
		//{
		//	object[i]->SetScale(Vector3(8, 4, 4));
		//	object[i]->SetMoving(true);
		//}
		//else
		//{
		//	object[i]->SetScale(Vector3(4, 2, 2));
		//	object[i]->SetMoving(false);
		//}
		object[i]->Update();
	}
}

void Result::Draw(DirectXCommon* dxCommon)
{
	//for (auto& o : object)
	//{
	//	o->Draw(dxCommon);
	//}
}

int Result::GetSelect()
{
	return num;
}

