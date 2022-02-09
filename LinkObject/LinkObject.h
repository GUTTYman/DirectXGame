#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"ShootEnemy.h"
//ばねの連結植物（棒のような見た目）
class LinkObject :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;
	static  std::vector<Player*> player;		//プレイヤー
	static std::vector<ShootEnemy*> sEnemies;	//狙撃敵

	Vector3 accel;			//加速度
	Vector3 target;	//ばねの始点
	int reverse;		//上下反転


public:
	LinkObject();
	~LinkObject();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;

	void SetInput(Input* input) { this->input = input; }
	void SetTarget(Vector3 aPos);
	void IsReverse(bool r);

	static void SetPlayer(std::vector<Player*> p);
	static void SetShootEnemy(std::vector<ShootEnemy*> e);

};

