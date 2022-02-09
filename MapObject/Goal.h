#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"ChargeParticle.h"
class Goal :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	static  std::vector<Player*> player;		//�v���C���[

	std::unique_ptr < ChargeParticle> particle;		//�p�[�e�B�N��

	float a;	//�z�o�����O�̈ʒu�isin�̊p�x�j
	bool goalFlag;	//�V�[���؂�ւ��t���O

public:
	Goal();
	~Goal();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	static void SetPlayer(std::vector<Player*> p) { player = p; }
	void SetGoalFlag(bool b) { goalFlag = b; }
	//Getter
	bool GetGoalFlag() { return goalFlag; }
};