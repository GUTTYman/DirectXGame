#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"

class RiseObject :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	static std::vector<Player*> player;		//プレイヤー

	float a;								//動きの値
	int waitTime;							//鼓動の速さ

public:
	RiseObject();
	~RiseObject();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;

	void PlayerRise(PlayerEmitter* p, int a,DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);

	//Setter
	static void SetPlayer(std::vector<Player*> p) { player = p; }
};

