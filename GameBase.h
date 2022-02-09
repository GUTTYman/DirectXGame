#pragma once

#include"WinApp.h"
#include"DirectXCommon.h"
#include"Input.h"
#include"Xinput.h"
#include"TextureManager.h"
#include"Sprite.h"
#include"SoundManager.h"
#include"Loader.h"
#include"GPUParticle.h"
#include"Object3d.h"
#include"Camera.h"
#include"Light.h"

#include<mmsystem.h>
#include<memory.h>
class GameBase
{
public:

	virtual void Run();
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 後処理
	/// </summary>
	virtual void Finalize();

private:
	/// <summary>
	/// フレームレートの固定
	/// </summary>
	void FrameRate();

	//固定フレーム
	const float MinFrameTime = 60;
	float frameTime = 0;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	LARGE_INTEGER freqTime;
	int count = 0;
	float fps = 0;

protected:
	//終了フラグ
	bool endFlag = false;


	std::unique_ptr < WinApp> winApp;
	//DirectX基盤
	std::unique_ptr<DirectXCommon> dxCommon;
	//キーボード入力
	std::unique_ptr < Input> input;
	//パッド入力
	std::unique_ptr<Xinput> pad;
	//テクスチャーマネージャー
	std::unique_ptr <TextureManager> textureManager;
	//スプライト
	std::unique_ptr<Sprite> sprite;
	//カメラ
	std::unique_ptr<Camera> camera;
	//ライト
	std::unique_ptr<Light> light;

	//サウンドマネージャー
	static std::unique_ptr < SoundManager> soundManager;
	//モデルローダー
	static std::unique_ptr < Loader> modelLoad;
};