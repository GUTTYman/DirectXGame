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

	float a;		//�z�o�����O�̈ʒu�isin�̊p�x�j
	bool goal;	//�S�[�����Ă���V�[���؂�ւ��܂ł̃C���^�[�o���t���O
	int goalCount;	//�S�[�����Ă���V�[���؂�ւ��܂ł̃J�E���g
	bool next;	//�V�[���؂�ւ��t���O
public:
	Goal();
	~Goal();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update(float gameTime);
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	static void SetPlayer(std::vector<Player*> p) { player = p; }
	void SetNextFlag(bool b) { next = b; }
	//Getter
	bool GetNextFlag() { return next; }
	bool GetGoalFlag() { return goal; }
};