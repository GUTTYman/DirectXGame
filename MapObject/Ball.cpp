#include "Ball.h"

std::vector<Player*> Ball::player;
bool Ball::alldead = false;
Ball::Ball()
{
	object = std::make_unique< Object3d>();	for (int i = 0; i < size; i++)
	{
		sp.emplace_back(std::make_unique< SpherePlantManager>(10));
	}
}
Ball::~Ball()
{
}

void Ball::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(SPHERE));
	velocity = Vector3(-0.6f, 0, 0);
	scale = Vector3(8,8,8);
	color = Vector3(0,0,0);
	a = 0;
	hitBlock = 0;
	shake = Vector3();
	shakeVelocity = Vector2();
	for (auto& s : sp)
	{
		s->Initialize(dxCommon,textureManager,2);
		s->LarpColor(color, Vector3(0.0f, 1.0f, 0.0f));
	}
	liveFlag = true;
}

void Ball::Update(float gameTime)
{
	alldead = true;
	if (liveFlag)
	{
		//SpherePlantの配置の間隔
		static float division = (628.0f / size) / 100;
#pragma region  Ball操作
		rotation.z -= velocity.x * 3;
		//プレイヤーとの当たり判定
		for (int i = 0; i < player.size(); i++)
		{
			if (SphereAndSphere(position+velocity, player[i]->GetPosition() +player[i]->GetVelocity(), scale.x, player[i]->GetScale().x,player[i]->GetLiveFlag(),liveFlag))
			{
				Vector3 direction = Vector3(player[i]->GetPosition() - position).normalize();
				player[i]->SetVelocity(direction / 2);
				if (player[i]->GetHitBlock() && !player[i]->GetDead())
				{
					player[i]->SetDead(true);
				}
			}
		}
		//周りのSpherePlantの操作
		for (int i = 0; i < sp.size(); i++)
		{
			float angle = division * i - rotation.z / 50;
			sp[i]->SetAngle(angle);
			sp[i]->Update();
			sp[i]->SetTarget(position + Vector3(sinf(angle) * scale.x / 2.0f, cosf(angle) * scale.y / 2.0f, 0.0f));
		}

		velocity.y -= 0.01f;
		position += velocity;

#pragma region 壁床にぶつかったらカメラシェイク


		if (hitBlock == 1)
		{
			shakeVelocity = Vector2(30,0);
		}
		else if (hitBlock == 2)
		{
			shakeVelocity = Vector2(0,20);
		}
		//ランダムで移動量
		Vector2 randVel = Vector2(shakeVelocity.x > 0 ? rand() % (int)shakeVelocity.x - shakeVelocity.x / 2 : 0, shakeVelocity.y > 0 ? rand() % (int)shakeVelocity.y - shakeVelocity.y / 2 : 0);
		//移動量をセットする
		shake = Vector3(randVel.x/10.0f,randVel.y/10.0f, 0);
		//カメラシェイクの減衰
		shakeVelocity.x > 0 ? shakeVelocity.x -= 1.0f : shakeVelocity.x = 0.0f;
		shakeVelocity.y > 0 ? shakeVelocity.y -= 1.0f : shakeVelocity.y = 0.0f;

#pragma endregion
		alldead = false;
#pragma endregion
	}
	else
	{
		velocity = Vector3(-0.6f, 0, 0);
		shake = Vector3();
	}
	hitBlock = 0;
	object->Update();
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	object->SetColor(color);

}

void Ball::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());

		for (auto& s : sp)
		{
			s->Draw(dxCommon);
		}
	}
}
