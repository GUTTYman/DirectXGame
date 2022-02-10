#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"FireParticle.h"
#include"Bullet.h"
//�e��ł��Ă���G
class ShootEnemy :
	public GameObject
{
private:
	std::unique_ptr < Object3d> eye;

	const static int cubesize = 10;
	float cubeCount;//cubeOBJ�p�J�E���g�ϐ�
	std::unique_ptr<GPUParticle> cubeOBJ;

	static  std::vector<Player*> player;		//�v���C���[
	std::unique_ptr<FireParticle> fire;		//�p�[�e�B�N��
	std::unique_ptr<Bullet> bullet;

	float a;	//
	bool dead;	//���S���̉��o�t���O

public:
	ShootEnemy();
	~ShootEnemy();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update(float gameTime);
	void CubeOBJUpdate(float gameTime);
	void Draw(DirectXCommon* dxCommon)override;
	//Getter
	Bullet* GetBullet() { return bullet.get(); }
	//Setter
	static void SetPlayer(std::vector<Player*> p) { player = p; }
};