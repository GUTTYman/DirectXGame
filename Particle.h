#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"

class Particle :
	public GameObject
{
private:
	Object3d* object = nullptr;


	int time;			//”­ŽË‚³‚ê‚Ä‚©‚ç‚ÌƒJƒEƒ“ƒg
public:
	Particle();
	~Particle();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;

	static void StaticFinalize();
	//void SetColor(Vector3 c) { object->SetColor(c); }

	//Getter
	inline int GetTime() { return time; }

};

