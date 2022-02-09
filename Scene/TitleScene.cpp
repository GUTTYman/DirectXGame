#include "TitleScene.h"

TitleScene::~TitleScene()
{
}


//�^�C�g���V�[���̍X�V
void TitleScene::Update()
{
	titleCount++;
	//�w�i
	back->SelectUpdate();
	if (!start)
	{
		if (input->Trigger(DIK_SPACE) || pad->Trigger(XINPUT_A))
		{
			start = true;
			soundManager->PlayWave(AudioIndex::EXPLOSION2);
			titleCount = 0;
		}
		//�{�^��UI�I�u�W�F�N�g
		sceneObject->ButtonUpdate(Vector3(0, -15, 0), Vector3(2, 3, 3));
	}
	else
	{
		if(titleCount>120)
		{
			//�Z���N�g�V�[���Ɉړ�
			scene = SELECT_SCENE;
			//�e���Z�����l�����Z�b�g
			titleCount = 120;
			start = false;
		}
	}
	//�J�E���g�ƃ^�C�g���I�u�W�F�N�g�̒��_�U���ɔ��f���������
	if (!start || titleCount < 60)
	{
		sceneObject->SetCount(titleCount);
	}
	sceneObject->Update();
	//�J����
	camera->SetEye(Vector3(0,0,-50));
	camera->SetTarget(Vector3(0,0,0));
}

//�^�C�g���V�[���̕`��
void TitleScene::Draw()
{
	//�w�i
	back->SelectDraw(dxCommon);
	//Title
	sceneObject->Draw(dxCommon);
	
	if (!start)
	{
		//�{�^��UI
		sceneObject->ButtonDraw(dxCommon);
	}

}

