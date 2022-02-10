#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"ShootEnemy.h"
//�A���A���i�X�p�C�N�{�[���P�́j
class SpherePlant :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	static std::vector<Player*> player;			//�v���C���[
	static std::vector<ShootEnemy*> sEnemies;	//�_���G

	Vector3 target;		//�n�_
	float radius;		//�^�[�Q�b�g�ƃ|�W�V�����̔��a
	float nowangle;		//������Ă���Ƃ��̊p�x
	float addangle;		//�����̊p�x��ݒ肷��l
	int reverse;		//�p�x���Z�����������]�i�㉺����j

	float a;			//�P�U���̕ϓ�����l
	float sinangle;		//�P�U���̑���
public:
	SpherePlant();
	~SpherePlant();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update();
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	inline void SetInput(Input* input) { this->input = input; }
	inline void SetTarget(Vector3 target) { this->target = target; }
	inline void SetSinAngle(float a) { this->a = a; }
	inline void SetRadius(float a) { radius = a; }
	//�A���̌����w��MAX�l : 6.28
	inline void SetAngle(float a) { addangle = a; }

	static void SetPlayer(std::vector<Player*> p);
	static void SetShootEnemy(std::vector<ShootEnemy*> e);
	//Getter
	inline Vector3 GetTarget() { return target; }
};

