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
#pragma region  HitParticle����
	//�p�[�e�B�N�����Z
	if (spawn)
	{
		time += 2;
	}
	else
	{
		time = 0;
		//�`�悳��ĂȂ��Ԃ̓|�W�V�����X�V
		object->SetPosition(p);
	}
	//�������s������ăZ�b�g
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
	//spaw��TURE�̊ԕ`��
	if (spawn)
	{
		object->Draw(dxCommon->GetCommandList(), ParticleMode::HITPARTICLE, 50);
	}
}
