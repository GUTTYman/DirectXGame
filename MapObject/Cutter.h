#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"

class Cutter :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	static std::vector<Player*> player;		//ÉvÉåÉCÉÑÅ[

public:
	Cutter();
	~Cutter();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update(float gameTime);
	void Draw(DirectXCommon* dxCommon)override;

	//Setter
	inline static void SetPlayer(std::vector<Player*> p) { player = p; }
};

