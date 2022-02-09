#pragma once
#include "GameObject.h"
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"Ball.h"
#include"ShootEnemy.h"

class Triangle :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	std::unique_ptr < Model> model;//モデル

	static  std::vector<Player*> player;	//プレイヤー
	static  std::vector<Ball*> ball;		//ボール
	static std::vector<ShootEnemy*> sEnemy;	//狙撃敵

	Vector3 pos1, pos2, pos3;

public:
	Triangle();
	~Triangle();
	void SetTrianglePosition(Vector3 pos1, Vector3 pos2, Vector3 pos3);
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	static void StaticFinalize();
	static void SetHitObject(std::vector<Player*> p, std::vector<Ball*>b, std::vector<ShootEnemy*>se);
};


