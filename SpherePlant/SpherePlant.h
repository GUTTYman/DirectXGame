#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"ShootEnemy.h"
//連結植物（スパイクボール単体）
class SpherePlant :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	static std::vector<Player*> player;			//プレイヤー
	static std::vector<ShootEnemy*> sEnemies;	//狙撃敵

	Vector3 target;		//始点
	float radius;		//ターゲットとポジションの半径
	float nowangle;		//押されているときの角度
	float addangle;		//初期の角度を設定する値
	int reverse;		//角度加算される方向反転（上下判定）

	float a;			//単振動の変動する値
	float sinangle;		//単振動の速さ
public:
	SpherePlant();
	~SpherePlant();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update();
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	inline void SetInput(Input* input) { this->input = input; }
	inline void SetTarget(Vector3 target) { this->target = target; }
	inline void SetSinAngle(float a) { this->a = a; }
	inline void SetRadius(float a) { radius = a; }
	//植物の向き指定MAX値 : 6.28
	inline void SetAngle(float a) { addangle = a; }

	static void SetPlayer(std::vector<Player*> p);
	static void SetShootEnemy(std::vector<ShootEnemy*> e);
	//Getter
	inline Vector3 GetTarget() { return target; }
};

