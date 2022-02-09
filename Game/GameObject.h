#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include <DirectXMath.h>
#include <random>
#include"Input.h"
#include"Vector.h"
#include"SoundManager.h"
#include"GamePad.h"
#include"Loader.h"

class GameObject
{
protected:
	Vector3 position = Vector3();		//座標
	Vector3 rotation = Vector3();		//回転
	Vector3 scale = Vector3(1, 1, 1);	//スケール
	Vector3 velocity = Vector3();		//加速度
	Vector3 color = Vector3(1, 1, 1);	//カラー
	float alpha = 1.0f;					//カラー透過値
	Vector3 normalLength = Vector3();	//ジオメトリシェーダーでフェースを法線上に飛ばす距離
	Vector3 randomVertex = Vector3();	//ジオメトリで頂点を振動させる
	bool liveFlag = true;				//表示フラグ

	static SoundManager* soundManager;
	static Input* input;
	static Xinput* pad;
	static Loader* modelLoader;

public: // メンバ関数
	GameObject();
	virtual ~GameObject();

	virtual void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) = 0;
	virtual void Update() = 0;
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	//Setter・Getter
	static void SetAssets(SoundManager* s, Input* i, Xinput* x);

	inline static void SetModelLoad(Loader* m)
	{
		modelLoader = m;
	}
	inline void SetPosition(Vector3 p)
	{
		position = p;
	}
	inline void SetVelocity(Vector3 p)
	{
		velocity = p;
	}
	inline void SetRotation(Vector3 p)
	{
		rotation = p;
	}
	inline void SetScale(Vector3 p)
	{
		scale = p;
	}
	inline void SetColor(Vector3 p)
	{
		color = p;
	}
	inline void SetAlpha(float a)
	{
		alpha = a;
	}
	inline void SetLiveFlag(bool b)
	{
		liveFlag = b;
	}
	inline void SetRandomVertex(Vector3 v)
	{
		randomVertex = v;
	}
	inline void SetNormalLength(Vector3 v)
	{
		normalLength = v;
	}
	inline Vector3 GetPosition()
	{
		return position;
	}
	inline Vector3 GetVelocity()
	{
		return velocity;
	}
	inline Vector3 GetRotation()
	{
		return rotation;
	}
	inline Vector3 GetScale()
	{
		return scale;
	}
	inline Vector3 GetColor()
	{
		return color;
	}
	inline Vector3 GetRandomVertex()
	{
		return randomVertex;
	}
	inline bool GetLiveFlag()
	{
		return liveFlag;
	}
	inline static SoundManager* GetSoundManager()
	{
		return soundManager;
	}
	inline static Input* GetInput()
	{
		return input;
	}
	inline static Xinput* GetPad()
	{
		return pad;
	}
	inline static Loader* GetModelLoad()
	{
		return modelLoader;
	}
};

