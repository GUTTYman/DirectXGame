#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include "LinkObjectManager.h"
//�V�[�����Ƃɐݒu�����UI���̃I�u�W�F�N�g�܂Ƃ߃N���X
class SceneObject :
	public GameObject
{
private:
	//Title
	std::unique_ptr < Object3d> titleObject;
	//Clear
	std::unique_ptr < Object3d> clearObject;
	//GameOver
	std::unique_ptr < Object3d> goObject;
	//����L�[
	std::unique_ptr < Object3d> ButtonObject;
	//L�X�e�B�b�N�I�u�W�F�N�g
	std::unique_ptr < Object3d> stickUI;
	//��������Ŕ�(A Button)
	std::unique_ptr < Object3d> buttonBorad;
	//�Ŕ�݂邷�A���I�u�W�F�N�g
	std::unique_ptr < LinkObjectManager> linkObject;
	//�^�C�g���̒��_�U���̃J�E���g
	int titleCount;
	//
	float time;
	//�z�o�����O�̃J�E���g
	float hobCount;
	//�Ŕ̂΂˂̉����x
	Vector3 accel;
	//�Ŕ̃X�P�[��
	Vector3 boradScale;
	//�Ŕ̊p�x
	Vector3 boradRotation;
public:
	SceneObject();
	~SceneObject();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update();
	void Draw(DirectXCommon* dxCommon)override;
	//title�̒��_�U���J�E�E���g�Z�b�g	
	inline void SetCount(int a) { titleCount = a; }

	//Play
	void PlayUpdate(Vector3 p,bool b);
	void PlayDraw(DirectXCommon* dxCommon);
	//Clear
	void ClearUpdate(Vector3 p);
	void ClearDraw(DirectXCommon* dxCommon);
	//GameOver
	void GameOverUpdate(Vector3 p);
	void GameOverDraw(DirectXCommon* dxCommon);
	//ButtonUI
	void ButtonUpdate(Vector3 p, Vector3 scale);
	void ButtonDraw(DirectXCommon* dxCommon);
	//ButtonBorad
	void BoradUpdate(Vector3 p,std::vector<Player*>player);
	void BroadDraw(DirectXCommon* dxCommon);
	//�Z�b�g����e�N�X�`���Ƃǂ̃��f���ɃZ�b�g���邩���w��
	inline void SetBoardTexture(UINT i) { modelLoader->GetModel(BOARD)->SetTexNumber(i); }

};

