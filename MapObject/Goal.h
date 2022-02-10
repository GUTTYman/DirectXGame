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

	float a;		//ホバリングの位置（sinの角度）
	bool goal;	//ゴールしてからシーン切り替えまでのインターバルフラグ
	int goalCount;	//ゴールしてからシーン切り替えまでのカウント
	bool next;	//シーン切り替えフラグ
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