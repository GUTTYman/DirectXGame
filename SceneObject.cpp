#include "SceneObject.h"

SceneObject::SceneObject()
{
	titleObject = std::make_unique< Object3d>();
	clearObject = std::make_unique< Object3d>();
	goObject = std::make_unique< Object3d>();
	ButtonObject = std::make_unique< Object3d>();
	UIObject = std::make_unique< Object3d>();
	buttonBorad = std::make_unique< Object3d>();
	linkObject = std::make_unique< LinkObjectManager>(15);
}
SceneObject::~SceneObject()
{
}

//������
void SceneObject::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{

	//TITLE�̃��f�����Z�b�g
	titleObject->Initialize(modelLoader->GetModel(TITLE));
	titleObject->SetOBJType(NORMALCOLOR);
	//CLEAR�̃��f�����Z�b�g
	clearObject->Initialize(modelLoader->GetModel(CLEAR));
	clearObject->SetColor(Vector3(0,1,0));
	//GAMEOVER�̃��f�����Z�b�g
	goObject->Initialize(modelLoader->GetModel(GAMEOVER));
	goObject->SetColor(Vector3(1,0,0));
	//����L�[�̃��f�����Z�b�g
	ButtonObject->Initialize(modelLoader->GetModel(BUTTON));
	ButtonObject->SetScale(Vector3(3, 3, 3));
	ButtonObject->SetRotation(Vector3(60,180,0));
	ButtonObject->SetColor(Vector3(0.5f,0.5f,0.5f));
	//L�X�e�B�b�N�̃��f�����Z�b�g
	UIObject->Initialize(modelLoader->GetModel(LSTICK));
	UIObject->SetScale(Vector3(3,3,3));
	UIObject->SetColor(Vector3(0.5f,0.5f,0.5f));
	UIObject->SetRotation(Vector3(0,180,0));
	//�{�^���{�[�h�̃��f�����Z�b�g
	buttonBorad->Initialize(modelLoader->GetModel(BORAD_ABUTTON));
	boradScale = Vector3(10, 10, 20);
	boradRotation = Vector3();
	buttonBorad->SetScale(boradScale);
	linkObject->Initialize(dxCommon, textureManager);

	//�V�[���I�u�W�F�N�g�iTITLE�AGAMEOVER�ACLEAR�j�̕ϐ�
	position = Vector3(0,0,0);
	rotation = Vector3(0,180,0);
	scale = Vector3(1.0f,1.0f,1.0f);
	titleCount = 60;
	hobCount = 0;
}
//�X�V����
void SceneObject::Update()
{
#pragma region  SceneObject����
	randomVertex = easeOut(Vector3(-50, -50, -50),Vector3(), titleCount / 60.0f);
	position = Vector3();
#pragma endregion
	//Title
	titleObject->SetPosition(position);
	titleObject->SetRotation(rotation);
	titleObject->SetScale(scale);
	titleObject->SetRandomVertex(randomVertex);
	titleObject->Update();
}

void SceneObject::Draw(DirectXCommon* dxCommon)
{
	//Title�I�u�W�F�N�g
	titleObject->Draw(dxCommon->GetCommandList());
}

void SceneObject::PlayUpdate(Vector3 p, bool b)
{
	//�z�o�����O�̕�
	float range = 7.0f;
	//�z�o�����O�̑���
	hobCount += 0.2f;
	//L�X�e�B�b�N�I�u�W�F�N�g
	UIObject->SetPosition(p + Vector3(0, 5, 0));
	UIObject->SetRotation(Vector3(30, 180, sin(hobCount) * range));
	UIObject->Update();

}

void SceneObject::PlayDraw(DirectXCommon* dxCommon)
{
	//L�X�e�B�b�N�I�u�W�F�N�g
	UIObject->Draw(dxCommon->GetCommandList());

}

void SceneObject::ClearUpdate(Vector3 p)
{
	//CLEAR�I�u�W�F�N�g
	clearObject->SetPosition(p + Vector3(0, 0, 20));
	clearObject->SetScale(Vector3(30, 30, 1));
	clearObject->Update();
	//�{�^��UI�I�u�W�F�N�g
	ButtonUpdate(p+Vector3(0,-5,20),Vector3(1,1,1));

}

void SceneObject::ClearDraw(DirectXCommon* dxCommon)
{
	//CLEAR�I�u�W�F�N�g
	clearObject->Draw(dxCommon->GetCommandList());
	ButtonDraw(dxCommon);
}

void SceneObject::GameOverUpdate(Vector3 p)
{
	//GameOver�I�u�W�F�N�g
	goObject->Update();
	goObject->SetPosition(p + Vector3(0, 0, 20));
	goObject->SetScale(Vector3(30,30,1));

	//�{�^��UI�I�u�W�F�N�g
	ButtonUpdate(p + Vector3(0, -5, 20),Vector3(1,1,1));

}

void SceneObject::GameOverDraw(DirectXCommon* dxCommon)
{
	//GameOver�I�u�W�F�N�g
	goObject->Draw(dxCommon->GetCommandList());
	//�{�^��UI�I�u�W�F�N�g
	ButtonDraw(dxCommon);
}

void SceneObject::ButtonUpdate(Vector3 p,Vector3 scale)
{
	//�z�o�����O�̕�
	float range = 0.1f;
	//�z�o�����O�̑���
	hobCount += 0.3f;
	//�{�^��UI�I�u�W�F�N�g
	ButtonObject->SetPosition(p);
	ButtonObject->SetScale(scale + Vector3(sin(hobCount) * range, sin(hobCount) * range, sin(hobCount) * range));
	ButtonObject->Update();
}

void SceneObject::ButtonDraw(DirectXCommon* dxCommon)
{
	//�{�^��UI�I�u�W�F�N�g
	ButtonObject->Draw(dxCommon->GetCommandList());
}

void SceneObject::BoradUpdate(Vector3 p, std::vector<Player*>player)
{
	//�����N�I�u�W�F�N�g
	linkObject->SetTarget(p);
	linkObject->Update();
	//�{�^��UI�I�u�W�F�N�g
	buttonBorad->SetPosition(linkObject->GetLinkObject()[linkObject->GetLinkSize() - 1]->GetPosition());
	for (int i = 0; i < player.size(); i++)
	{
		//Player���ŔɐG�ꂽ��
		if (SphereAndCapsule(player[i]->GetPosition(), player[i]->GetScale().x,
			buttonBorad->GetPosition() + Vector3(-5, 0, 0), buttonBorad->GetPosition() + Vector3(5, 0, 0), scale.x*2, player[i]->GetLiveFlag()))
		{
			//�Ŕ��Ȃт�
			linkObject->GetLinkObject()[linkObject->GetLinkSize() - 1]->SetVelocity(player[i]->GetVelocity());
			//�Ŕp�x���Z
			boradRotation -= player[i]->GetVelocity() * 10.0f;
		}
	}
#pragma region �Ŕ̊p�x����


	float stiffness = 0.3f;	//�߂鋭��
	float damping = 0.95f;	//�����̌���
	float mass = 10.0f;		//�d��

	Vector3 force = Vector3(stiffness * (-boradRotation.x), stiffness * (-boradRotation.y), 0.0f);
	accel = force / mass;
	//�ړ���
	velocity = damping * (velocity + accel);
	boradRotation += velocity;
#pragma endregion
	buttonBorad->SetRotation(boradRotation);
	buttonBorad->Update();
}

void SceneObject::BroadDraw(DirectXCommon* dxCommon)
{
	//�����N�I�u�W�F�N�g�̕`��
	linkObject->Draw(dxCommon);
	//�{�[�h�I�u�W�F�N�g�`��
	buttonBorad->Draw(dxCommon->GetCommandList());
}
