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

	static std::vector<Player*> player;		//プレイヤー

	float a;								//動きの値
	float waitTime;							//鼓動の速さ
	bool emitte;							//パーティクルの放出フラグ
	float pCount;								//パーティクルのカウント

public:
	Bomb();
	~Bomb();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update(float gameTime);
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	static void SetPlayer(std::vector<Player*> p) { player = p; }
};

