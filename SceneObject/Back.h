#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
class Back :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;
	std::vector<std::unique_ptr < Object3d>> selectBackLeft;
	std::vector<std::unique_ptr < Object3d>> selectBackRight;
	std::vector<Vector3>selectVecl;
	float rotaZ;
public:
	Back();
	~Back();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update();
	void Draw(DirectXCommon* dxCommon)override;
	void SelectUpdate();
	void SelectDraw(DirectXCommon*dxCommon);
};