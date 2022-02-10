#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include "TailManager.h"
//�O�œ��͓��e���擾����p�֐�
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

	bool hitBlock;	//�ǂ⏰�ɓ����Ă��邩
	bool dead;		//LiveFlag��False�ɂȂ�O�̉��o�̃t���O
	float power;	//�����W��
	float powerCount;	//�����W�����Z
	float a;
	//�����ۂ̃I�u�W�F�N�g
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

