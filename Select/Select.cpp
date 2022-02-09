#include "Select.h"

float Select::t = 60.0f;

Select::Select()
{
	object = std::make_unique< Object3d>();
}
Select::~Select()
{
}

void Select::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{

}
void Select::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, ModelIndex m)
{
	modelIndex = m;
	object->Initialize(modelLoader->GetModel(m));
	position = Vector3();
	color = Vector3(1,1,1);
	scale = Vector3(1.5f, 2, 2);
	shake = Vector3();
	shakeVelocity = Vector2();
	randomVertex = Vector3();
	a = 0.0f;
	count = t;
	liveFlag = true;
	moving = false;
	isRota = false;
	open = false;

}

void Select::Update()
{
	if (liveFlag)
	{
#pragma region  Select操作
		//ステージ解除
		if (open)
		{
			//ホバリング
			if (moving )
			{
				//ホバリングの幅
				float range = 0.025f;
				//ホバリングの速さ
				a += 0.05f;
				position += Vector3(0, sin(a) * range, 0);
				//ホバリング中の回転
				if (isRota && randomVertex.x == 0.0f)
				{
					if (rotation.y < 360)
					{
						rotation.y += 12;
					}
					if (position.y < 0.5f)
					{
						rotation.y = 0.0f;
					}
				}
			}
			else
			{
				rotation.y = 0.0f;
				position.y = 0.0f;
				a = 0.0f;
			}
		}
#pragma region シェイク加算

		//ランダムで移動量
		Vector2 randVel = Vector2(shakeVelocity.x > 0 ? rand() % (int)shakeVelocity.x - shakeVelocity.x / 2 : 0, shakeVelocity.y > 0 ? rand() % (int)shakeVelocity.y - shakeVelocity.y / 2 : 0);
		//移動量をセットする
		shake = Vector3(randVel.x / 10.0f, randVel.y / 10.0f, 0);
		//カメラシェイクの減衰
		shakeVelocity.x > 0 ? shakeVelocity.x -= 1.0f : shakeVelocity.x = 0.0f;
		shakeVelocity.y > 0 ? shakeVelocity.y -= 1.0f : shakeVelocity.y = 0.0f;

#pragma endregion

#pragma region ランダム頂点計算
		//ジオメトリシェーダーで頂点を振動させるカウント
		if (count < t)
		{
			count++;
		}
		randomVertex = easeOut(Vector3(60.0f, 0.0f, 0.0f), Vector3(), count / t);
#pragma endregion


#pragma endregion
		object->SetPosition(position);
		object->SetRandomVertex(randomVertex);
		object->SetRotation(rotation);
		object->SetScale(scale);
		object->SetColor(color);
		object->Update();

	}
}

void Select::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}

