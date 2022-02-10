#include "Bullet.h"

Bullet::Bullet()
{
	object = std::make_unique< Object3d>();
	fire = std::make_unique< FireParticle>();
	hitParticle = std::make_unique< HitParticle>();

}
Bullet::~Bullet()
{
}

void Bullet::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{

	object->Initialize(modelLoader->GetModel(CUBE));
	//噴出particle
	fire->Initialize(dxCommon, textureManager);
	//衝突particle
	hitParticle->Initialize(modelLoader->GetModel(ModelIndex::CUBE));

	scale = Vector3(2,2,2);
	color = Vector3();
	object->SetColor(color);
	liveFlag = false;
	time = 0;
}

void Bullet::Update(float gameTime)
{
	if (liveFlag)
	{
#pragma region

		//発射されてからのカウント
		time++;
#pragma endregion
		position += velocity * gameTime;
		rotation.z = time * 3;
	}
	else
	{
		//hitParticle->SetSpawnFlag(true);
		time = 0;
	}
	fire->Update(position);
	hitParticle->Update(position);
	object->Update();
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
}
void Bullet::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
		fire->Draw(dxCommon);
	}
	hitParticle->Draw(dxCommon);
}
