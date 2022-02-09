#include "Wall.h"

std::vector<Player*> Wall::player;
std::vector<Ball*> Wall::ball;
std::vector<ShootEnemy*> Wall::sEnemy;

Wall::Wall()
{
	object = std::make_unique< Object3d>();
}
Wall::~Wall()
{
}

void Wall::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(CUBE));
	color = Vector3(0.0f, 0.05f, 0.0f);
	position = Vector3();
	scale = Vector3(6, 72, 10);
	object->SetColor(color);
	object->SetScale(scale);
	liveFlag = true;

}

void Wall::Update()
{
	if (liveFlag)
	{
		object->Update();
#pragma region  Block操作

		//Player
		for (int i = 0; i < player.size(); i++)
		{
			if (RectangleAndSphere2D(position - scale / 2, position + scale / 2, player[i]->GetPosition() + player[i]->GetVelocity(), player[i]->GetScale().z))
			{
				//バウンド
				player[i]->SetHitBlock(true);
				//めり込んだ分押し返してから反発させる
				player[i]->SetPosition(Vector3(player[i]->GetPosition().x - player[i]->GetVelocity().x, player[i]->GetPosition().y, 0.0f));
				player[i]->SetVelocity(Vector3(-player[i]->GetVelocity().x / 3.0f, player[i]->GetVelocity().y, player[i]->GetVelocity().z));
			}
		}
		//Ball
		for (int i = 0; i < ball.size(); i++)
		{
			if (RectangleAndSphere2D(position - scale / 2, position + scale / 2, ball[i]->GetPosition() + ball[i]->GetVelocity(), ball[i]->GetScale().z))
			{
				//バウンド
				ball[i]->SetVelocity(Vector3(-ball[i]->GetVelocity().x, ball[i]->GetVelocity().y, ball[i]->GetVelocity().z));
				ball[i]->SetHitBlock(1);
			}
		}
		//ShootEnemy
		for (int i = 0; i < sEnemy.size(); i++)
		{
			if (RectangleAndSphere2D(position - scale / 2, position + scale / 2, sEnemy[i]->GetBullet()->GetPosition(), sEnemy[i]->GetBullet()->GetScale().x))
			{
				sEnemy[i]->GetBullet()->SetLiveFlag(false);
				sEnemy[i]->GetBullet()->GetHitParticle()->SetSpawnFlag(true);

			}
		}
#pragma endregion
		object->SetPosition(position);
		object->SetRotation(rotation);
	}
}
void Wall::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
//干渉するオブジェクトをセット
void Wall::SetHitObject(std::vector<Player*> p, std::vector<Ball*> b, std::vector<ShootEnemy*> se)
{
	player = p;
	ball = b;
	sEnemy = se;
}
