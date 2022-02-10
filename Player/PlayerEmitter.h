#pragma once
#include"Player.h"
#include "Collision.h"

class PlayerEmitter
{
private:
	//プレイヤーの初期数
	int size = 20;
	//一体でも生き残ってるか
	bool liveFlag;
	//放置されているカウント
	int rest;
	std::vector<Player*> object;

public:
	PlayerEmitter();
	~PlayerEmitter();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	void Update(float gameTime);
	void Draw(DirectXCommon* dxCommon);
	//1体だけ残して他は消す
	void PlayerReset();
	//増える数指定
	void Rise(Vector3 position, DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);
	//Setter
	void SetPosition(Vector3 position);
	void SetVelocity(Vector3 velocity);
	inline void SetAllLiveFlag(bool b) { liveFlag = b; }
	//Getter
	inline bool GetLiveFlag() { return liveFlag; }
	inline int GetRestTime() { return rest; }
	inline std::vector<Player*>GetPleyer() { return object; }
	//
	int TopPlayer();

	Vector3 PlayerCamera();
	//先頭のプレイヤーの座標
	Vector3 TopPosition();
};

