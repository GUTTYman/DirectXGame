#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"Ball.h"
#include"ShootEnemy.h"

class TileBlock :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	static  std::vector<Player*> player;	//�v���C���[
	static  std::vector<Ball*> ball;		//�{�[��
	static std::vector<ShootEnemy*> sEnemy;	//�_���G

public:
	TileBlock();
	~TileBlock();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	static void SetHitObject(std::vector<Player*> p, std::vector<Ball*>b, std::vector<ShootEnemy*>se);
};


