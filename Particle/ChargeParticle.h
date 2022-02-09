#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Particle.h"

class ChargeParticle
{
private:
	static const int size = 20;
	std::vector<Particle*> object;
	bool spawn;
	bool end;	//チャージ終了フラグ
	int a;
public:
	ChargeParticle();
	~ChargeParticle();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	void Update(Vector3 p);
	void Draw(DirectXCommon* dxCommon);

	//Getter
	bool EndCharge();
	//Setter
	void SetPosition(Vector3 position);
	void SetLiveFlag(bool b);
	void SetSpawnFlag(bool b) { spawn = b; }
};

