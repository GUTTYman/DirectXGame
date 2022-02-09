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

	static  std::vector<Player*> player;		//プレイヤー

	std::unique_ptr < ChargeParticle> particle;		//パーティクル

	float a;	//ホバリングの位置（sinの角度）
	bool goalFlag;	//シーン切り替えフラグ

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