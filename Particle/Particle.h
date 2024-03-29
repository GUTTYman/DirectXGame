#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"

class Particle :
	public GameObject
{
private:
	Object3d* object = nullptr;


	int time;			//発射されてからのカウント
public:
	Particle();
	~Particle();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update();
	void Draw(DirectXCommon* dxCommon)override;

	static void StaticFinalize();
	//void SetColor(Vector3 c) { object->SetColor(c); }

	//Getter
	inline int GetTime() { return time; }

};

