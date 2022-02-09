#include "HitParticle.h"

HitParticle::HitParticle()
{
	object = new GPUParticle();
}
HitParticle::~HitParticle()
{
	delete object;
}
void HitParticle::StaticFinalize()
{
}
void HitParticle::Initialize(Model* model)
{
	object->Initialize(model);
	color = Vector3(0,0.1f,0);
	time = 0;
	maxCount = 0;
	spawn = false;
}

void HitParticle::Update(Vector3 p)
{
#pragma region  HitParticle操作
	//パーティクル加算
	if (spawn)
	{
		time += 2;
	}
	else
	{
		time = 0;
		//描画されてない間はポジション更新
		object->SetPosition(p);
	}
	//寿命が尽きたら再セット
	if (time > 200)
	{
		spawn = false;
	}

#pragma endregion
	object->SetColor(color);
	object->SetTime(time);
	object->SetMaxCount(maxCount);
	object->Update();
}

void HitParticle::Draw(DirectXCommon* dxCommon)
{
	//spawがTUREの間描画
	if (spawn)
	{
		object->Draw(dxCommon->GetCommandList(), ParticleMode::HITPARTICLE, 50);
	}
}
