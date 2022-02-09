#include "SelectScene.h"
SelectScene::~SelectScene()
{

}
//�}�b�v�I���̍X�V
void SelectScene::Update()
{
	//�w�i
	back->SelectUpdate();
	//�Z���N�g�{�b�N�X
	select->Update();
	//�{�^��UI
	sceneObject->ButtonUpdate(Vector3(0, -15, 0), Vector3(3, 3, 3));
	//�J����
	camera->SetEye(Vector3(0, 0, -50));
	camera->SetTarget(Vector3(0, 0, 0));

	//�X�e�[�W�����肵����Play�ɐ؂�ւ��
	if (select->GetEnter() == 2)
	{
		//�I�񂾃}�b�v�ԍ����Z�b�g
		mapnum = select->GetMapSelect();
		//�V�[����Play�ɐ؂�ւ�
		scene = PLAY_SCENE;
		//�I�񂾃}�b�v���쐬
		MapLoad();
		//�t�F�[�h�C���l������
		Scene::SetFade(0.0f);
		count = 0;
		//�J����������
		camera->SetTarget(Vector3(53.0f, -28.0f, 0.0f));
		camera->SetEye(Vector3(53.0f, -28.0f, -65.0f));
	}
}

//�}�b�v�I���̕`��
void SelectScene::Draw()
{
	//�w�i
	back->SelectDraw(dxCommon);
	//�{�^��UI
	sceneObject->ButtonDraw(dxCommon);
	//�X�e�[�W�̃Z���N�g�{�b�N�X
	select->Draw(dxCommon);
}