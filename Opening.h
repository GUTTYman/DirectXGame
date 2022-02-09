#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
enum OpenStep
{
	OFF,
	START,
	ZOOMOUT,
	SHAKE,
	SPAWN,
};

class Opening:GameObject
{
private:
		//OpenStep�̊e���ڂ̒���
		int offCount;
		int startCount;
		int zoomCount;
		int shakeCount;
		int spawnCount;

	OpenStep step;
	int time;			//���Ԍo��
	float normalLength;	//���̖@����Ƀt�F�[�X���΂��J�E���g
	float heartbeat;	//���̌ۓ��̃J�E���g
	int waittime;		//�ۓ��̕p�x
	Vector3 shake;		//�����U������
	Vector3 cameraEye;	//�V�[���̃J�����ɓn���l
	Vector3 cameraTarget;

	std::unique_ptr < Object3d> spawnObject;
public:
	Opening();
	~Opening();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)override ;
	void Update(Vector3 position);
	void SpawnOBJUpdate(Vector3 position);
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	void Reset();		//������x���o���Z�b�g����
	//Getter
	Vector3 GetShake() { return shake; }
	Vector3 GetCameraEye() { return cameraEye; }
	Vector3 GetCameraTarget() { return cameraTarget; }
	OpenStep GetStep() { return step; }
	bool isWait();
	

};

