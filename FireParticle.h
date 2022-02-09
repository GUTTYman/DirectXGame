#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Particle.h"

class FireParticle
{
private:

	static const int size = 20;
	std::vector<Particle*> object;
	int a;
	bool red;

public:
	FireParticle();
	~FireParticle();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	void Update(Vector3 p);
	void Draw(DirectXCommon* dxCommon);

	void SetPosition(Vector3 position);
	void SetLiveFlag(bool b);
	void SetRed(bool b) { red = b; };
};
