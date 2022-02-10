#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"FireParticle.h"
#include"HitParticle.h"
//�G�̒e
class Bullet :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	int time;			//���˂���Ă���̃J�E���g
	std::unique_ptr< FireParticle> fire;	//���o
	std::unique_ptr < HitParticle> hitParticle;
public:
	Bullet();
	~Bullet();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update(float gameTime);
	void Draw(DirectXCommon* dxCommon)override;
	//Getter
	int GetTime() { return time; }
	FireParticle* GetFire() { return fire.get(); }
	HitParticle* GetHitParticle() { return hitParticle.get(); }
	//Setter
};