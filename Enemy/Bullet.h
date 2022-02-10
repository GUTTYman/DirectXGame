#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"FireParticle.h"
#include"HitParticle.h"
//敵の弾
class Bullet :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	int time;			//発射されてからのカウント
	std::unique_ptr< FireParticle> fire;	//噴出
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