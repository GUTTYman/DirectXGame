#include "ResultScene.h"
ResultScene::~ResultScene()
{

}
//���U���g�V�[���̍X�V
void ResultScene::Update()
{
	if (scene == CLEAR_SCENE)//�N���A�̎�
	{
		if (input->Trigger(DIK_SPACE) || pad->Trigger(XINPUT_A))
		{
			//�^�C�g���ɖ߂�
			scene = TITLE_SCENE;
		}
		sceneObject->ClearUpdate(Vector3(camera->GetEye().x, camera->GetEye().y, camera->GetEye().z));
	}
	else if (scene == GAMEOVER_SCENE)//�Q�[���I�[�o�[�̎�
	{
		if (input->Trigger(DIK_SPACE) || pad->Trigger(XINPUT_A))
		{
			//�Z���N�g�ɖ߂�
			scene = SELECT_SCENE;
		}
		sceneObject->GameOverUpdate(Vector3(camera->GetEye().x, camera->GetEye().y, camera->GetEye().z));
	}
}

//���U���g�V�[���̕`��
void ResultScene::Draw()
{
	//�N���A�̎�
	if (scene == CLEAR_SCENE)
	{
		sceneObject->ClearDraw(dxCommon);
	}
	//�Q�[���I�[�o�[�̎�
	if (scene == GAMEOVER_SCENE)
	{
		sceneObject->GameOverDraw(dxCommon);
	}
}

