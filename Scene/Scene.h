#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include <DirectXMath.h>
#include <random>
#include"Input.h"
#include"Vector.h"
#include"SoundManager.h"
#include"GamePad.h"
#include"Camera.h"
#include"Map.h"

#include"SceneObject.h"
#include"SelectManager.h"
#include"PlayerEmitter.h"
#include"ShootEnemy.h"
#include"LinkObjectManager.h"
#include"BoundObjectManager.h"
#include"SpherePlantManager.h"
#include"TileBlock.h"
#include"Wall.h"
#include"Triangle.h"
#include"Bomb.h"
#include"RiseObject.h"
#include"Goal.h"
#include"Cutter.h"
#include"Ball.h"
#include"Back.h"

enum SceneFlag
{
	TITLE_SCENE,
	SELECT_SCENE,
	PLAY_SCENE,
	CLEAR_SCENE,
	GAMEOVER_SCENE
};

class Scene
{
protected:
	static DirectXCommon* dxCommon;
	static TextureManager* textureManager;

	static SoundManager* soundManager;
	static Input* input;
	static Xinput* pad;
	static Camera* camera;
	static SceneFlag scene;
	static Map* map;
	//オブジェクト
	static SelectManager* select;
	static SceneObject* sceneObject;
	static PlayerEmitter* player;
	static Goal* goal;
	static Back* back;
	static std::vector <Ball*> ball;
	static std::vector <ShootEnemy*> shootEnemy;
	static std::vector<LinkObjectManager*> linkObject;
	static std::vector<LinkObjectManager*> linkObjectD;
	static std::vector<BoundObjectManager*> boundObject;
	static std::vector<SpherePlantManager*> spherePlant;
	static std::vector<SpherePlantManager*> spherePlantD;
	static std::vector<TileBlock*> block;
	static std::vector<Wall*> wall;
	static std::vector<Bomb*> bomb;
	static std::vector<Cutter*> cutter;
	static std::vector<RiseObject*> rise;
	static std::vector<Triangle*> triangle;


	static int mapnum;	//現在のマップ番号
	static int initnum;
	static int count;			//カウント
private:
	static float fade; //シーン切り替え時のフェードカウント

public: // メンバ関数
	Scene();
	virtual ~Scene() = 0;

	static void Finalize();
	static void Initialize();
	static bool Fade(float time, float count);


	virtual void Update() = 0;
	virtual void Draw() = 0;

	void MapLoad();
	//Setter
	static void SetAssets(DirectXCommon* d, TextureManager* t,SoundManager* s, Input* i, Xinput* x, Camera* c);
	static void SetScene(SceneFlag s) { scene = s; }
	static void SetFade(float a) { fade = a; }
	//Getter
	inline static SoundManager* GetSoundManager() { return soundManager; }
	inline static Input* GetInput() { return input; }
	inline static Xinput* GetPad() { return pad; }
	inline static SceneFlag GetScene() { return scene; }
	inline static float GetFade() { return fade; }
};

