#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"TouchParticle.h"
//�L�m�R�I�u�W�F�N�g
class BoundObject :
	public GameObject
{
private:
	std::unique_ptr<Object3d> object;

	static std::vector<Player*> player;		//�v���C���[

	std::unique_ptr<TouchParticle> particle;	//�p�[�e�B�N��

	float accel;			//�����x
	Vector3 target;			//�n�_
public:
	BoundObject();
	~BoundObject();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update();
	void Draw(DirectXCommon* dxCommon)override;
	
	void SetInput(Input* input) { this->input = input; }
	static void SetPlayer(std::vector<Player*> p);
};

