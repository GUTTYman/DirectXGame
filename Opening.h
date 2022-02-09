#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
enum OpenStep
{
	OFF,
	START,
	ZOOMOUT,
	SHAKE,
	SPAWN,
};

class Opening:GameObject
{
private:
		//OpenStepの各項目の長さ
		int offCount;
		int startCount;
		int zoomCount;
		int shakeCount;
		int spawnCount;

	OpenStep step;
	int time;			//時間経過
	float normalLength;	//卵の法線状にフェースを飛ばすカウント
	float heartbeat;	//卵の鼓動のカウント
	int waittime;		//鼓動の頻度
	Vector3 shake;		//卵が振動する
	Vector3 cameraEye;	//シーンのカメラに渡す値
	Vector3 cameraTarget;

	std::unique_ptr < Object3d> spawnObject;
public:
	Opening();
	~Opening();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)override ;
	void Update(Vector3 position);
	void SpawnOBJUpdate(Vector3 position);
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	void Reset();		//もう一度演出をセットする
	//Getter
	Vector3 GetShake() { return shake; }
	Vector3 GetCameraEye() { return cameraEye; }
	Vector3 GetCameraTarget() { return cameraTarget; }
	OpenStep GetStep() { return step; }
	bool isWait();
	

};

