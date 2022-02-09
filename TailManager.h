#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Tail.h"

class TailManager
{
private:
	int size;
	std::vector<Tail*> object;

public:
	TailManager(int a);
	~TailManager();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager,float firstSize);
	void Update();
	void Draw(DirectXCommon* dxCommon);
	//Getter
	inline Vector3 GetFirstTarget() { return object[0]->GetTarget(); }
	
	//Setter
	void SetPosition(Vector3 position);
	void SetScale(Vector3 scale);
	void SetTarget(Vector3 tPos);
	void SetNormalLength(Vector3 v);
	inline void SetObjectNumber(int i) { size = i; }
	//A•¨‚ÌŒü‚«w’èMAX’l : 6.28
	void SetAngle(float a);
	void LerpColor(Vector3 s,Vector3 e);
};

