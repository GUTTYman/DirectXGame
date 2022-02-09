#include "Particle.h"

Particle::Particle()
{
	object = new Object3d();
}
Particle::~Particle()
{
	delete object;
}

void Particle::StaticFinalize()
{
}
void Particle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(CUBE));
	color = Vector3();
	scale = Vector3(2, 2, 2);
	liveFlag = true;
	time = 0;
}

void Particle::Update()
{

	if (liveFlag)
	{

#pragma region  ParticleëÄçÏ
		

		position += velocity;
		if (scale.x < 0.0f)
		{
			liveFlag = false;
		}
		time++;
#pragma endregion
	}
	else
	{
		time = 0;
	}
	object->SetPosition(position);
	object->SetColor(color);
	object->SetRotation(rotation);
	object->SetScale(scale);
	object->Update();
}

void Particle::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
