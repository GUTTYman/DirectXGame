#include "GameBase.h"

#pragma comment(lib,"winmm.lib")

std::unique_ptr < SoundManager> GameBase::soundManager;
std::unique_ptr<Loader> GameBase::modelLoad;

using namespace std;

void GameBase::Run()
{
	//������
	Initialize();

	while (true)
	{
		if (endFlag) {
			break;
		}
		if (input->Trigger(DIK_ESCAPE))
		{
			endFlag = true;
		}

		//�X�V
		Update();

		//�`��
		Draw();

		//�t���[��
		FrameRate();
	}
	Finalize();
}

void GameBase::Initialize()
{
	
	//WindowsAPI������
	winApp = make_unique< WinApp>();
	winApp->Initialize();

	//DirectX������������������
	dxCommon = make_unique<DirectXCommon>();
	dxCommon->Initialize(winApp.get());

	//TextureManager�̏�����
	textureManager = make_unique< TextureManager>();
	textureManager->Initialize(dxCommon.get());

	//SoundManager�̏�����:
	soundManager = make_unique< SoundManager>();
	soundManager->Initialize();

	//ModelLoad�̏�����
	modelLoad = make_unique< Loader>(textureManager.get(), soundManager.get());
	modelLoad->Initialize(dxCommon.get(), textureManager.get());

	//Input�̏�����
	input = make_unique< Input>();
	input->Initialize(winApp->GetHwnd());
	//XInput�̏�����
	pad = make_unique< Xinput>();

	//Camera�̏�����
	camera = make_unique< Camera>();
	camera->Initialize();

	//�X�v���C�g�̐ÓI������
	Sprite::StaticInitialize(dxCommon.get(), textureManager.get());
	//3D�I�u�W�F�N�g�̐ÓI������
	Object3d::StaticInitialize(dxCommon.get(), camera.get());
	//GPU�p�[�e�B�N���̐ÓI������
	GPUParticle::StaticInitialize(dxCommon.get(), camera.get());
	//���C�g�̐ÓI������
	Light::StaticInitialize(dxCommon->GetDevice());

	//���C�g�̐���
	light = Light::Create();
	//���C�g�̈ʒu��ݒ�
	light->SetLightDir({ 0,-1,1});
	

	//�X�v���C�g����
	/*sprite = make_unique< Sprite();
	sprite->Initialize(0);*/

	//�t���[�����[�g�̏�����
	QueryPerformanceFrequency(&freqTime);
	QueryPerformanceCounter(&startTime);
}

void GameBase::Update()
{

#pragma region �E�B���h�E���b�Z�[�W����
	if (winApp->Update()) {
		endFlag = true;
	}
#pragma endregion

	//3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLight(light.get());

	input->Update();
	pad->Update();
	camera->Update();
	light->Update();
}

void GameBase::Finalize()
{

}
//�t���[�����[�g�Œ�
void GameBase::FrameRate()
{
	if (count == MinFrameTime)
	{
		QueryPerformanceCounter(&endTime);
		fps = 1000.0f / (static_cast<float>((endTime.QuadPart - startTime.QuadPart) * 1000.0f / freqTime.QuadPart) / MinFrameTime);
		count = 0;
		startTime = endTime;
	}
	count++;
	QueryPerformanceCounter(&endTime);
	{
		//1�~���b
		//DWORD sleepTime = static_cast<DWORD>((MinFrameTime - frameTime) * 1000);
		DWORD sleepTime = static_cast<DWORD>((1000.0f / MinFrameTime) * count - (endTime.QuadPart - startTime.QuadPart) * 1000.0f / freqTime.QuadPart);

		if (sleepTime < 18 && sleepTime>0)
		{
			timeBeginPeriod(1);
			Sleep(sleepTime);
			timeEndPeriod(1);
		}
		else
		{
			timeBeginPeriod(1);
			Sleep(1);
			timeEndPeriod(1);
		}
	}
}
