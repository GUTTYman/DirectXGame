#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
//�Z���N�g�{�b�N�X�P��
class Select :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object = nullptr;
	ModelIndex modelIndex;
	
	Vector3 shake;			//�I�u�W�F�N�g��U��������
	Vector2 shakeVelocity;	//�U���̈ړ���
	float a;				//sin�̃Ƃ̒l
	bool moving;			//�z�o�����O�̃t���O
	bool isRota;			//��]�̃t���O
	bool open;				//�}�b�v�J���̃t���O
	static float t;			//�J�E���g�̐���
	float count;			//�J�E���g

public:
	Select();
	~Select();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, ModelIndex m) ;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	//Getter
	inline bool GetIsRota() { return isRota; }
	inline bool GetOpen() { return open; }
	inline Vector3 GetShake() { return shake; }
	//Setter
	inline void SetMoving(bool b) { moving = b; }
	inline void SetisRota(bool b) { isRota = b; }
	inline void SetCount(float i) { count = i; }
	inline void SetOpen(bool b) { open = b; }
	inline void SetShakeVelosity(Vector2 v) { shakeVelocity = v; }
	//�Z�b�g����e�N�X�`���Ƃǂ̃��f���ɃZ�b�g���邩���w��
	inline void SetTexture(UINT i) { modelLoader->GetModel(modelIndex)->SetTexNumber(i); }
};

