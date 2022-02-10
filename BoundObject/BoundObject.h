#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"TouchParticle.h"
//キノコオブジェクト
class BoundObject :
	public GameObject
{
private:
	std::unique_ptr<Object3d> object;

	static std::vector<Player*> player;		//プレイヤー

	std::unique_ptr<TouchParticle> particle;	//パーティクル

	float accel;			//加速度
	Vector3 target;			//始点
public:
	BoundObject();
	~BoundObject();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update();
	void Draw(DirectXCommon* dxCommon)override;
	
	void SetInput(Input* input) { this->input = input; }
	static void SetPlayer(std::vector<Player*> p);
};

