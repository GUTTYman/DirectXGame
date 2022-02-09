#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"ShootEnemy.h"
//�΂˂̘A���A���i�_�̂悤�Ȍ����ځj
class LinkObject :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;
	static  std::vector<Player*> player;		//�v���C���[
	static std::vector<ShootEnemy*> sEnemies;	//�_���G

	Vector3 accel;			//�����x
	Vector3 target;	//�΂˂̎n�_
	int reverse;		//�㉺���]


public:
	LinkObject();
	~LinkObject();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;

	void SetInput(Input* input) { this->input = input; }
	void SetTarget(Vector3 aPos);
	void IsReverse(bool r);

	static void SetPlayer(std::vector<Player*> p);
	static void SetShootEnemy(std::vector<ShootEnemy*> e);

};

