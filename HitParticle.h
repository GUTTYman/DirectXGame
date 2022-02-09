#pragma once
#include <DirectXMath.h>
#include "GPUParticle.h"
#include "Loader.h"

class HitParticle
{
private:
	GPUParticle* object = nullptr;

public:
	HitParticle();
	~HitParticle();
	void Initialize(Model*model);
	void Update(Vector3 p);
	void Draw(DirectXCommon* dxCommon);
	static void StaticFinalize();
	//Getter
	bool GetSpawn() { return spawn; }
	//Setter
	inline void SetTime(int time) { this->time = time; }
	inline void SetColor(Vector3 color) { this->color = color; }
	inline void SetSpawnFlag(bool spawn) { this->spawn = spawn; }
private:
	int time;
	int maxCount;
	Vector3 color;
	bool spawn;

};

