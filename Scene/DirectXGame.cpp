#include "DirectXGame.h"
using namespace DirectX;
using namespace Microsoft::WRL;
void DirectXGame::Initialize()
{
	//���N���X�̏�����
	GameBase::Initialize();
	//�|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	textureManager->LoadTexture(100, L"Resources/white.png");
	//�|�X�g�G�t�F�N�g�̏�����
	postEffect = std::make_unique< PostEffect>();
	postEffect->Initialize();
	gaussian = std::make_unique< Gaussian>();
	gaussian->Initialize();
	gaussian->SetShift(0.01f);

	//���f�����[�_�[�̃N���X��݂�
	GameObject::SetModelLoad(modelLoad.get());
	//�V�[���̊��N���X�ɑ݂�
	Scene::SetAssets(dxCommon.get(), textureManager.get(), soundManager.get(), input.get(), pad.get(), camera.get());

	//�e�V�[���̏�����
	titleScene = std::make_unique< TitleScene>();
	selectScene = std::make_unique< SelectScene>();	
	gameplayScene = std::make_unique< GamePlayScene>();
	gameplayScene->Initialize();
	resultScene = std::make_unique< ResultScene>();
	Scene::Initialize();
	

}

void DirectXGame::Update()
{
	//���N���X�̍X�V����
	GameBase::Update();
	//GameObject�ɑ݂�
	GameObject::SetAssets(soundManager.get(),input.get(),pad.get());
	//�V�[���̊��N���X�ɑ݂�
	Scene::SetAssets(dxCommon.get(),textureManager.get(),soundManager.get(),input.get(),pad.get(),camera.get());

	//�e�V�[���̍X�V����
	switch (Scene::GetScene())
	{
	case SceneFlag::TITLE_SCENE:
		//�p�Ȃ̋����ݒ�
		postEffect->SetShift(0.5f);
		postEffect->SetRGBShift(0.0f);
		gaussian->SetShift(0.0f);
		Scene::SetFade(1.0f);
		titleScene->Update();
		break;
	case SceneFlag::SELECT_SCENE:
		//�p�Ȃ̋����ݒ�
		postEffect->SetShift(0.1f);
		postEffect->SetRGBShift(selectScene->GetSelectManagerObject()->GetRGBShift());
		gaussian->SetShift(0.0f);
		selectScene->Update();
		break;
	case SceneFlag::PLAY_SCENE:
		//�p�Ȃ̋����ݒ�
		postEffect->SetShift(0.4f);
		postEffect->SetRGBShift(0.0f);
		gaussian->SetShift(0.0f);
		gameplayScene->Update();
		break;
	case SceneFlag::GAMEOVER_SCENE:
		//�p�Ȃ̋����ݒ�
		postEffect->SetShift(0.4f);
		gaussian->SetShift(0.02f);
		//�Q�[���I�[�o�[�̌��ɃX�e�[�W�𓮂����Ă���
		gameplayScene->Update();
		resultScene->Update();
	default:
		//�p�Ȃ̋����ݒ�
		postEffect->SetShift(0.4f);
		gaussian->SetShift(0.02f);
		resultScene->Update();
		break;
	}
}

void DirectXGame::Draw()
{
	//�|�X�g�G�t�F�N�g�̑O�`��
	postEffect->PreDrawScene(dxCommon->GetCommandList());
	//�t�F�[�h�C���̒l�Z�b�g
	postEffect->SetFade(Scene::GetFade());

	//�e�V�[���̕`��؂�ւ�
	switch (Scene::GetScene())
	{
	case SceneFlag::TITLE_SCENE:
		titleScene->Draw();
		break;
	case SceneFlag::SELECT_SCENE:
		selectScene->Draw();
		break;
	case SceneFlag::PLAY_SCENE:
		gameplayScene->Draw();
		break;
	default:
		//���ɃQ�[����ʂ�\�������܂�
		gameplayScene->Draw();
		resultScene->Draw();
		break;
	}
	//�X�v���C�g
	Sprite::SetPiepelineState(dxCommon->GetCommandList());
	
	//�|�X�g�G�t�F�N�g�̌�`��
	postEffect->PostDrawScene(dxCommon->GetCommandList());

	gaussian->PreDrawScene(dxCommon->GetCommandList());
	postEffect->Draw(dxCommon->GetCommandList());
	gaussian->PostDrawScene(dxCommon->GetCommandList());

#pragma region postEffect

	dxCommon->BeginDraw();
	
	gaussian->Draw(dxCommon->GetCommandList());

	dxCommon->EndDraw();
}
#pragma endregion

void DirectXGame::Finalize()
{
	Scene::Finalize();
}
