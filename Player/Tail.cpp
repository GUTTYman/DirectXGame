#include "Tail.h"

Tail::Tail()
{
	object = std::make_unique< Object3d>();
}
Tail::~Tail()
{
}
void Tail::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	object->Initialize(modelLoader->GetModel(BALL1));
	color = Vector3(1, 1, 1);
	scale = Vector3(1, 1, 1);
	target = Vector3(0.0f, 0.0f, 0.0f);
	normalLength = Vector3();
	nowangle = 0; 
	a = 0.0f;
	sinangle = 0.1f;
	radius = 1.5f;
	addangle = 0.0f;
	liveFlag = true;
}

void Tail::Update(float gameTime)
{
	//liveFlag��True�̊Ԃ̂ݍX�V����������
	if (liveFlag)
	{
#pragma region  Tail����

		position = Vector3(target.x + (sinf(nowangle + addangle) * radius), target.y + (cosf(nowangle + addangle) * radius), target.z);

		float stiffness = 0.1f;	//�߂鋭��
		float damping = 0.9f;	//�����̌���
		float mass = 8.0f;		//�d��

		float force = stiffness * (-nowangle);
		float accel = force / mass;
		velocity.x = damping * (velocity.x + accel);

		//���R�ȗh��
		velocity.x += (sin(a) * 0.005f);
		a += sinangle * gameTime;
		//�������p�x�ɉ��Z
		nowangle += velocity.x;
#pragma endregion
	}

	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	object->SetColor(color);
	object->Update();

}
void Tail::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
