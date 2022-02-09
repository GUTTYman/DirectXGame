#pragma once
#include <DirectXMath.h>
#include "GPUParticle.h"

class TouchParticle
{
private:
	std::unique_ptr<GPUParticle> object;

public:
	TouchParticle();
	void Initialize(Model* model);
	void Update(Vector3 p);
	void Draw(DirectXCommon* dxCommon);
	static void StaticFinalize();
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

