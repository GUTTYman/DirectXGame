#pragma once
#include "GameObject.h"
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"PlayerEmitter.h"
#include"SpherePlantManager.h"

class Ball :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;
	static std::vector<Player*> player;		//ƒvƒŒƒCƒ„[

	static bool alldead;;
	static const int size = 10;
	std::vector< std::unique_ptr<SpherePlantManager>> sp;	//‹…‘ÌA•¨
	int a;
	float time;
	Vector3 shake;
	int hitBlock;
	Vector2 shakeVelocity;
public:
	Ball();
	~Ball();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update(float gameTime);
	void Draw(DirectXCommon* dxCommon)override;

	//Getter
	inline Vector3 GetCameraShake() { return shake; }
	inline static bool GetAllDead() { return alldead; }
	//Setter
	inline static void SetPlayer(std::vector<Player*> p) { player = p; }
	inline void SetHitBlock(int hitBlock) { this->hitBlock = hitBlock; }
};

