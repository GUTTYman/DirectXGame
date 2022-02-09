#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
//セレクトボックス単体
class Select :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object = nullptr;
	ModelIndex modelIndex;
	
	Vector3 shake;			//オブジェクトを振動させる
	Vector2 shakeVelocity;	//振動の移動量
	float a;				//sinのθの値
	bool moving;			//ホバリングのフラグ
	bool isRota;			//回転のフラグ
	bool open;				//マップ開放のフラグ
	static float t;			//カウントの制限
	float count;			//カウント

public:
	Select();
	~Select();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, ModelIndex m) ;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	//Getter
	inline bool GetIsRota() { return isRota; }
	inline bool GetOpen() { return open; }
	inline Vector3 GetShake() { return shake; }
	//Setter
	inline void SetMoving(bool b) { moving = b; }
	inline void SetisRota(bool b) { isRota = b; }
	inline void SetCount(float i) { count = i; }
	inline void SetOpen(bool b) { open = b; }
	inline void SetShakeVelosity(Vector2 v) { shakeVelocity = v; }
	//セットするテクスチャとどのモデルにセットするかを指定
	inline void SetTexture(UINT i) { modelLoader->GetModel(modelIndex)->SetTexNumber(i); }
};

