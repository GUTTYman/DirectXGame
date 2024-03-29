#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"LinkObject.h"
//ばね植物をを連結させて管理するクラス
class LinkObjectManager
{
private:
	std::vector<LinkObject*> object;

public:
	LinkObjectManager(int size);
	~LinkObjectManager();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	void Update();
	void Draw(DirectXCommon* dxCommon);
	//Getter
	int GetLinkSize() { return int(object.size()); }
	std::vector<LinkObject*>GetLinkObject() { return object; }
	//Setter
	void SetTarget(Vector3 aPos);
	void IsReverse(bool r);
};

