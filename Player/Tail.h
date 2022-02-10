#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
class Tail :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;


	Vector3 target;		//�n�_
	float radius;		//�^�[�Q�b�g�ƃ|�W�V�����̔��a
	float nowangle;		//������Ă���Ƃ��̊p�x
	float addangle;		//�����̊p�x��ݒ肷��l

	float a;			//�P�U���̕ϓ�����l
	float sinangle;		//�P�U���̑���
public:
	Tail();
	~Tail();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update(float gameTime);
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	inline void SetInput(Input* input) { this->input = input; }
	inline void SetTarget(Vector3 target) { this->target = target; }
	inline void SetSinAngle(float a) { this->a = a; }
	inline void SetRadius(float a) { radius = a; }
	//�A���̌����w��MAX�l : 6.28
	inline void SetAngle(float a) { addangle = a; }

	//Getter
	inline Vector3 GetTarget() { return target; }
};

