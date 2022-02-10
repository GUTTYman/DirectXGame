#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"

class Bomb :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	static std::vector<Player*> player;		//�v���C���[

	float a;								//�����̒l
	float waitTime;							//�ۓ��̑���
	bool emitte;							//�p�[�e�B�N���̕��o�t���O
	float pCount;								//�p�[�e�B�N���̃J�E���g

public:
	Bomb();
	~Bomb();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update(float gameTime);
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	static void SetPlayer(std::vector<Player*> p) { player = p; }
};

