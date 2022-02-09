#pragma once

#include"WinApp.h"
#include"DirectXCommon.h"
#include"Input.h"
#include"Xinput.h"
#include"TextureManager.h"
#include"Sprite.h"
#include"SoundManager.h"
#include"Loader.h"
#include"GPUParticle.h"
#include"Object3d.h"
#include"Camera.h"
#include"Light.h"

#include<mmsystem.h>
#include<memory.h>
class GameBase
{
public:

	virtual void Run();
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �㏈��
	/// </summary>
	virtual void Finalize();

private:
	/// <summary>
	/// �t���[�����[�g�̌Œ�
	/// </summary>
	void FrameRate();

	//�Œ�t���[��
	const float MinFrameTime = 60;
	float frameTime = 0;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	LARGE_INTEGER freqTime;
	int count = 0;
	float fps = 0;

protected:
	//�I���t���O
	bool endFlag = false;


	std::unique_ptr < WinApp> winApp;
	//DirectX���
	std::unique_ptr<DirectXCommon> dxCommon;
	//�L�[�{�[�h����
	std::unique_ptr < Input> input;
	//�p�b�h����
	std::unique_ptr<Xinput> pad;
	//�e�N�X�`���[�}�l�[�W���[
	std::unique_ptr <TextureManager> textureManager;
	//�X�v���C�g
	std::unique_ptr<Sprite> sprite;
	//�J����
	std::unique_ptr<Camera> camera;
	//���C�g
	std::unique_ptr<Light> light;

	//�T�E���h�}�l�[�W���[
	static std::unique_ptr < SoundManager> soundManager;
	//���f�����[�_�[
	static std::unique_ptr < Loader> modelLoad;
};