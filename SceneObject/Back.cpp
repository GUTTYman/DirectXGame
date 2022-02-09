#include "Back.h"

Back::Back()
{
	object = std::make_unique< Object3d>();
	
	for (int i = 0; i < 20; i++){	selectBackLeft.emplace_back(std::make_unique<Object3d>());}
	for (int i = 0; i < 20; i++){	selectBackRight.emplace_back(std::make_unique<Object3d>());}
}
Back::~Back()
{
}

void Back::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	rotaZ = 0.0f;
	selectVecl.resize(selectBackLeft.size());
	//Play���w�i������
	object->Initialize(modelLoader->GetModel(BACK1));
	liveFlag = true;
	position = Vector3(0, -130, 500);
	rotation = Vector3(0, 180, 0);
	color = Vector3(0.6f,0.7f,0.6f);
	scale = Vector3(40, 40, 40);
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetColor(color);
	object->SetScale(scale);
	
	//�Z���N�g���̔w�i������
	for (int i = 0; i < selectBackLeft.size(); i++)
	{
		selectBackLeft[i]->Initialize(modelLoader->GetModel(SPIKEBALL));
		//�e��`�悵�Ȃ�
		selectBackLeft[i]->SetOBJType(NONE_SHADOW);
		//�J���[�Z�b�g
		selectBackLeft[i]->SetColor(Vector3(0.8f, 0.9f, 0.8f));
		//�X�P�[�������_��
		float r = rand() % 20;
		selectBackLeft[i]->SetScale(Vector3(r, r, r) + Vector3(6, 6, 6));
		selectVecl[i] = Vector3((20 - r) / 10.0f, 0, 0);
		//�����ʒu
		selectBackLeft[i]->SetPosition(Vector3(rand() % 190-190, rand() % 150 - 75, 100));

	}
	for (int i = 0; i < selectBackRight.size(); i++)
	{
		selectBackRight[i]->Initialize(modelLoader->GetModel(SPIKEBALL));
		//�e��`�悵�Ȃ�
		selectBackRight[i]->SetOBJType(NONE_SHADOW);
		//�J���[�Z�b�g
		selectBackRight[i]->SetColor(Vector3(0.8f, 0.9f, 0.8f));
		//�X�P�[�������_��
		float r = rand() % 20;
		selectBackRight[i]->SetScale(Vector3(r, r, r) + Vector3(6, 6, 6));
		//�����ʒu
		selectBackRight[i]->SetPosition(Vector3(rand() % 190, rand() % 150 - 75, 100));

	}

}

void Back::Update()
{
	if (liveFlag)
	{
		object->Update();
	}
}
void Back::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}

void Back::SelectUpdate()
{
	//������E��
	for (int i = 0; i < selectBackLeft.size(); i++)
	{
		//��ʓ����[�v
		if (selectBackLeft[i]->GetPosition().x > 190)
		{
			selectBackLeft[i]->SetPosition(Vector3(-190, selectBackLeft[i]->GetPosition().y, 100));
		}
		//���[�u
		selectBackLeft[i]->SetPosition(selectBackLeft[i]->GetPosition() + selectVecl[i]);
		selectBackLeft[i]->SetRotation(Vector3(0, 0, -rotaZ/ selectBackLeft[i]->GetScale().x));
		selectBackLeft[i]->Update();
	}
	//�E���獶��
	for (int i = 0; i < selectBackRight.size(); i++)
	{
		//��ʓ����[�v
		if (selectBackRight[i]->GetPosition().x < -190)
		{
			selectBackRight[i]->SetPosition(Vector3(190, selectBackRight[i]->GetPosition().y, 100));
		}
		//���[�u
		selectBackRight[i]->SetPosition(selectBackRight[i]->GetPosition() - selectVecl[i]);
		selectBackRight[i]->SetRotation(Vector3(0, 0, rotaZ / selectBackRight[i]->GetScale().x));
		selectBackRight[i]->Update();
	}
	rotaZ+=20.0f;
}

void Back::SelectDraw(DirectXCommon* dxCommon)
{
	for (auto& obj : selectBackLeft)
	{
		obj->Draw(dxCommon->GetCommandList());
	}
	for (auto& obj : selectBackRight)
	{
		obj->Draw(dxCommon->GetCommandList());
	}
}
