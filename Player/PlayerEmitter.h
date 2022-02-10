#pragma once
#include"Player.h"
#include "Collision.h"

class PlayerEmitter
{
private:
	//�v���C���[�̏�����
	int size = 20;
	//��̂ł������c���Ă邩
	bool liveFlag;
	//���u����Ă���J�E���g
	int rest;
	std::vector<Player*> object;

public:
	PlayerEmitter();
	~PlayerEmitter();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	void Update(float gameTime);
	void Draw(DirectXCommon* dxCommon);
	//1�̂����c���đ��͏���
	void PlayerReset();
	//�����鐔�w��
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
	//�擪�̃v���C���[�̍��W
	Vector3 TopPosition();
};

