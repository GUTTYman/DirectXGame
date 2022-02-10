#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include "LinkObjectManager.h"
//シーンごとに設置されるUI等のオブジェクトまとめクラス
class SceneObject :
	public GameObject
{
private:
	//Title
	std::unique_ptr < Object3d> titleObject;
	//Clear
	std::unique_ptr < Object3d> clearObject;
	//GameOver
	std::unique_ptr < Object3d> goObject;
	//決定キー
	std::unique_ptr < Object3d> ButtonObject;
	//Lスティックオブジェクト
	std::unique_ptr < Object3d> stickUI;
	//操作説明看板(A Button)
	std::unique_ptr < Object3d> buttonBorad;
	//看板を吊るす連結オブジェクト
	std::unique_ptr < LinkObjectManager> linkObject;
	//タイトルの頂点振動のカウント
	int titleCount;
	//
	float time;
	//ホバリングのカウント
	float hobCount;
	//看板のばねの加速度
	Vector3 accel;
	//看板のスケール
	Vector3 boradScale;
	//看板の角度
	Vector3 boradRotation;
public:
	SceneObject();
	~SceneObject();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update();
	void Draw(DirectXCommon* dxCommon)override;
	//titleの頂点振動カウウントセット	
	inline void SetCount(int a) { titleCount = a; }

	//Play
	void PlayUpdate(Vector3 p,bool b);
	void PlayDraw(DirectXCommon* dxCommon);
	//Clear
	void ClearUpdate(Vector3 p);
	void ClearDraw(DirectXCommon* dxCommon);
	//GameOver
	void GameOverUpdate(Vector3 p);
	void GameOverDraw(DirectXCommon* dxCommon);
	//ButtonUI
	void ButtonUpdate(Vector3 p, Vector3 scale);
	void ButtonDraw(DirectXCommon* dxCommon);
	//ButtonBorad
	void BoradUpdate(Vector3 p,std::vector<Player*>player);
	void BroadDraw(DirectXCommon* dxCommon);
	//セットするテクスチャとどのモデルにセットするかを指定
	inline void SetBoardTexture(UINT i) { modelLoader->GetModel(BOARD)->SetTexNumber(i); }

};

