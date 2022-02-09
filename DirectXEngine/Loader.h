#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include"Model.h"

enum ModelIndex
{
	PLAYER,
	SPHERE,
	CUBE,
	BALL1,
	BACK1,
	SPIKEBALL,
	CUTTER,
	RISE,
	TITLE,
	CLEAR,
	GAMEOVER,
	BUTTON,
	LSTICK,
	SELECTBOX1,
	SELECTBOX2,
	SELECTBOX3,
	SELECTBOX4,
	SELECTBOX5,
	SELECTBOX6,
	EYE,
	KINOKO,
	EGG,
	BOARD,
	POINTVERTEX,
	X3,

};

enum AudioIndex
{
	DONOT,
	SELECT,
	DEAD,
	EXPLOSION,
	EXPLOSION2,
	PICKUP,
	WALLHIT,
	RISEUP,
	GOAL,
	HEARTBEAT,
	SHOOT,
};

class Loader
{
private:
	
	std::vector<std::unique_ptr<Model>> model;
	TextureManager* textureManager;
	SoundManager* soundManager;

	void AddModel(ModelIndex m, std::string filename);
public:
	Loader(TextureManager* texture, SoundManager* sound);
	~Loader();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	Model* GetModel(int modelIndex);
	
};

