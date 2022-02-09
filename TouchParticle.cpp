#include "TouchParticle.h"

TouchParticle::TouchParticle()
{
	object = std::make_unique<GPUParticle>();
}

void TouchParticle::StaticFinalize()
{
}
void TouchParticle::Initialize(Model*model)
{
	object->Initialize(model);
	color = Vector3(0.1f,0.9f,0.1f);
	time = 0;
	maxCount = 0;
	spawn = false;
}

void TouchParticle::Update(Vector3 p)
{
#pragma region  TouchParticle����
	//�p�[�e�B�N�����Z
	if (spawn)
	{
		time++;
	}
	//�ăZ�b�g
	if (time > 200)
	{
		spawn = false;
		time = 0;
	}

#pragma endregion
	object->SetPosition(p);
	object->SetColor(color);
	object->SetTime(time);
	object->SetMaxCount(maxCount);
	object->Update();
}

void TouchParticle::Draw(DirectXCommon* dxCommon)
{
	//spaw��TURE�̊ԕ`��
	if (spawn)
	{
		object->PointDraw(dxCommon->GetCommandList(), ParticleMode::POINTPARTICLE, 30);
	}
}
