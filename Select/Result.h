#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Select.h"

class Result
{
private:
	
	int size;	//‘I‘ğ€–Ú‚ÌŒÂ”
	int num;		//‘I‘ğ”Ô†

	std::vector<Select*> object;

public:
	Result();
	~Result();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	void Update();
	void Draw(DirectXCommon* dxCommon);

	//Getter
	int GetSelect();
};

