#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"FireParticle.h"
#include"Bullet.h"
//弾を打ってくる敵
class ShootEnemy :
	public GameObject
{
private:
	std::unique_ptr < Object3d> eye;

	const static int cubesize = 10;
	float cubeCount;//cubeOBJ用カウント変数
	std::unique_ptr<GPUParticle> cubeOBJ;

	static  std::vector<Player*> player;		//プレイヤー
	std::unique_ptr<FireParticle> fire;		//パーティクル
	std::unique_ptr<Bullet> bullet;

	float a;	//
	bool dead;	//死亡時の演出フラグ

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