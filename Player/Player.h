#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include "TailManager.h"
//外で入力内容を取得する用関数
enum InputNum
{
	RIGHT,
	LEFT,
	UP,
	NONE
};
//Payer
class Player :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

	bool hitBlock;	//壁や床に当たているか
	bool dead;		//LiveFlagがFalseになる前の演出のフラグ
	float power;	//反発係数
	float powerCount;	//反発係数加算
	float a;
	//しっぽのオブジェクト
	std::unique_ptr < TailManager> tail;

public:
	Player();
	~Player();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update(float gameTime);
	void Control(float gameTime);
	void Draw(DirectXCommon*dxCommon)override;
	
	//Getter
	static InputNum GetInput();
	inline bool GetHitBlock() { return hitBlock; }
	inline bool GetDead() { return dead; }
	inline float GetPowerCount() { return powerCount; }
	inline float GetPower() { return power; }
	inline TailManager* GetTailManager() { return tail.get(); }
	//Setter
	inline void SetHitBlock(bool b) { hitBlock = b; }
	void SetDead(bool b);
	inline void SetPowerCount(float f) { powerCount = f; }
};

