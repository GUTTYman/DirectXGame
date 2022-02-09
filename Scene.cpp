#include "Scene.h"
SoundManager* Scene::soundManager = nullptr;
Input* Scene::input = nullptr;
Xinput* Scene::pad = nullptr;
Camera* Scene::camera = nullptr;
SceneFlag Scene::scene = TITLE_SCENE;
DirectXCommon* Scene::dxCommon = nullptr;
TextureManager* Scene::textureManager = nullptr;
Map* Scene::map;
int Scene::mapnum = 0;
int Scene::initnum = 0;
float Scene::fade = 0.0f;
int Scene::count = 0;
 SceneObject* Scene::sceneObject = new SceneObject();
 SelectManager* Scene::select = new SelectManager();
 PlayerEmitter* Scene::player = new PlayerEmitter();
 Goal* Scene::goal = new Goal();
 Back* Scene::back = new Back();
 std::vector <Ball*> Scene::ball;
 std::vector <ShootEnemy*> Scene::shootEnemy;
 std::vector<LinkObjectManager*> Scene::linkObject;
 std::vector<LinkObjectManager*> Scene::linkObjectD;
 std::vector<BoundObjectManager*> Scene::boundObject;
 std::vector<SpherePlantManager*> Scene::spherePlant;
 std::vector<SpherePlantManager*> Scene::spherePlantD;
 std::vector<TileBlock*> Scene::block;
 std::vector<Wall*> Scene::wall;
 std::vector<Bomb*> Scene::bomb;
 std::vector<Cutter*> Scene::cutter;
 std::vector<RiseObject*> Scene::rise;
 std::vector<Triangle*> Scene::triangle;

Scene::Scene()
{
	//現在のマップ
	initnum = 0;
	//map
	map = new Map();
	map->Initialize();

	//各オブジェクトの個数指定
	linkObject.resize(map->GetLinkObjectMax());
	linkObjectD.resize(map->GetLinkObjectDownMax());
	boundObject.resize(map->GetBoundObjectMax());
	spherePlant.resize(map->GetSpherePlantMax());
	spherePlantD.resize(map->GetSpherePlantDownMax());
	block.resize(map->GetBlockMax());
	wall.resize(map->GetWallMax());
	bomb.resize(map->GetBombMax());
	cutter.resize(map->GetCutterMax());
	rise.resize(map->GetRiseMax());
	triangle.resize(map->GetTriangleAMax());
	ball.resize(map->GetBallMax());
	shootEnemy.resize(map->GetShootEnemyMax());

	//Ball
	for (int i = 0; i < ball.size(); i++){ball[i] = new Ball();}
	//のれんオブジェクト
	for (int i = 0; i < linkObject.size(); i++){linkObject[i] = new LinkObjectManager(rand() % 13 + 2);}
	//上方向のれんオブジェクト
	for (int i = 0; i < linkObjectD.size(); i++){linkObjectD[i] = new LinkObjectManager(rand() % 13 + 2);}
	//キノコオブジェクト
	for (int i = 0; i < boundObject.size(); i++){boundObject[i] = new BoundObjectManager();}
	//球体植物オブジェクト
	for (int i = 0; i < spherePlant.size(); i++)
	{
		float size = rand() % 10;
		spherePlant[i] = new SpherePlantManager(size + 5);
	}
	//下方向球体植物オブジェクト
	for (int i = 0; i < spherePlantD.size(); i++)
	{
		float size = rand() % 15;
		spherePlantD[i] = new SpherePlantManager(size + 5);
	}
	//ブロックオブジェクト
	for (int i = 0; i < block.size(); i++){block[i] = new TileBlock();}
	//壁オブジェクト
	for (int i = 0; i < wall.size(); i++){wall[i] = new Wall();}
	//ボムオブジェクト
	for (int i = 0; i < bomb.size(); i++){bomb[i] = new Bomb();}
	//草刈り機オブジェクト
	for (int i = 0; i < cutter.size(); i++){cutter[i] = new Cutter();}
	//増殖オブジェクト
	for (int i = 0; i < rise.size(); i++){rise[i] = new RiseObject();}
	//ShootEnemy
	for (int i = 0; i < shootEnemy.size(); i++){shootEnemy[i] = new ShootEnemy();}
	//三角形オブジェクト
	for (int i = 0; i < triangle.size(); i++){triangle[i] = new Triangle();}
}

Scene::~Scene()
{
	
}
void Scene::Finalize()
{
	delete sceneObject;
	delete select;
	delete player;
	delete goal;
	delete back;
	for (auto b : ball) { delete b; }
	for (auto b : shootEnemy) { delete b; }
	for (auto b : linkObject) { delete b; }
	for (auto b : linkObjectD) { delete b; }
	for (auto b : boundObject) { delete b; }
	for (auto b : spherePlant) { delete b; }
	for (auto b : spherePlantD) { delete b; }
	for (auto b : block) { delete b; }
	for (auto b : wall) { delete b; }
	for (auto b : bomb) { delete b; }
	for (auto b : cutter) { delete b; }
	for (auto b : rise) { delete b; }
	for (auto b : triangle) { delete b; }
	delete map;

}
void Scene::Initialize()
{
	select->Initialize(dxCommon, textureManager);

	//Title
	sceneObject->Initialize(dxCommon, textureManager);

	//Player
	player->Initialize(dxCommon, textureManager);
	player->SetPosition(map->GetPlayerPosition());

	//Goal
	goal->Initialize(dxCommon, textureManager);
	goal->SetPosition(map->GetGoalPosition());

	//Back
	back->Initialize(dxCommon, textureManager);

	//Ball
	for (int i = 0; i < ball.size(); i++)
	{
		ball[i]->Initialize(dxCommon, textureManager);
	}

	//のれんオブジェクト
	for (int i = 0; i < linkObject.size(); i++)
	{
		linkObject[i]->Initialize(dxCommon, textureManager);
	}
	//上方向のれんオブジェクト
	for (int i = 0; i < linkObjectD.size(); i++)
	{
		linkObjectD[i]->Initialize(dxCommon, textureManager);
		linkObjectD[i]->IsReverse(true);
	}
	//キノコオブジェクト
	for (int i = 0; i < boundObject.size(); i++)
	{
		boundObject[i]->Initialize(dxCommon, textureManager);
	}
	//球体植物オブジェクト
	for (int i = 0; i < spherePlant.size(); i++)
	{
		float size = rand() % 10;
		spherePlant[i]->Initialize(dxCommon, textureManager, size / 10.0f + 1.5f);
	}
	//下方向球体植物オブジェクト
	for (int i = 0; i < spherePlantD.size(); i++)
	{
		float size = rand() % 20;
		spherePlantD[i]->Initialize(dxCommon, textureManager, size / 10.0f + 1.5f);
		spherePlantD[i]->SetAngle(3.14f);
	}
	//ブロックオブジェクト
	for (int i = 0; i < block.size(); i++)
	{
		block[i]->Initialize(dxCommon, textureManager);
	}
	//壁オブジェクト
	for (int i = 0; i < wall.size(); i++)
	{
		wall[i]->Initialize(dxCommon, textureManager);
	}
	//ボムオブジェクト
	for (int i = 0; i < bomb.size(); i++)
	{
		bomb[i]->Initialize(dxCommon, textureManager);
	}
	//草刈り機オブジェクト
	for (int i = 0; i < cutter.size(); i++)
	{
		cutter[i]->Initialize(dxCommon, textureManager);
	}
	//増殖オブジェクト
	for (int i = 0; i < rise.size(); i++)
	{
		rise[i]->Initialize(dxCommon, textureManager);
	}
	//ShootEnemy
	for (int i = 0; i < shootEnemy.size(); i++)
	{
		shootEnemy[i]->Initialize(dxCommon, textureManager);
	}
}
//マップ切り替えごとの再配置
void Scene::MapLoad()
{
	map->SetNowmap(mapnum);
#pragma region ポジション指定
	//Player
	player->SetVelocity(Vector3());
	player->PlayerReset();
	player->SetPosition(map->GetPlayerPosition());
	player->Update();
	//ゴール再配置
	goal->SetPosition(map->GetGoalPosition());
	//ボール再配置
	for (int i = 0; i < map->GetBall().size(); i++)
	{
		ball[i]->SetPosition(map->GetBall()[i]);
		ball[i]->SetVelocity(Vector3(-0.6f, 0, 0));
	}

	//のれんオブジェクト
	//配置再指定

	for (int i = 0; i < map->GetLinkObject().size(); i++)
	{
		linkObject[i]->SetTarget(map->GetLinkObject()[i]);
	}
	//下方向のれんオブジェクト
	//配置再指定
	for (int i = 0; i < map->GetLinkObjectDown().size(); i++)
	{
		linkObjectD[i]->SetTarget(map->GetLinkObjectDown()[i]);
	}

	//キノコオブジェクト
	//配置再指定
	for (int i = 0; i < map->GetBoundObject().size(); i++)
	{
		boundObject[i]->SetPosition(map->GetBoundObject()[i]);
	}
	//球体植物オブジェクト
	//配置再指定
	for (int i = 0; i < map->GetSpherePlant().size(); i++)
	{
		spherePlant[i]->SetTarget(map->GetSpherePlant()[i]);
	}
	//下方向球体植物オブジェクト
	//配置再指定
	for (int i = 0; i < map->GetSpherePlantDown().size(); i++)
	{
		spherePlantD[i]->SetTarget(map->GetSpherePlantDown()[i]);
	}
	//ブロックオブジェクト
	//配置再指定
	for (int i = 0; i < map->GetBlock().size(); i++)
	{
		block[i]->SetPosition(map->GetBlock()[i]);
	}
	//壁オブジェクト
	//配置再指定
	for (int i = 0; i < map->GetWall().size(); i++)
	{
		wall[i]->SetPosition(map->GetWall()[i]);
	}
	//ボムオブジェクト
	//配置再指定
	for (int i = 0; i < map->GetBomb().size(); i++)
	{
		bomb[i]->SetLiveFlag(true);
		bomb[i]->SetPosition(map->GetBomb()[i]);
	}
	//草刈り機オブジェクト
	//配置再指定
	for (int i = 0; i < map->GetCutter().size(); i++)
	{
		cutter[i]->SetLiveFlag(true);
		cutter[i]->SetPosition(map->GetCutter()[i]);
	}
	//増殖オブジェクト
	//配置再指定
	for (int i = 0; i < map->GetRise().size(); i++)
	{
		rise[i]->SetLiveFlag(true);
		rise[i]->SetPosition(map->GetRise()[i]);
	}
	//使わない敵を消す
	for (int i = 0; i < shootEnemy.size(); i++)
	{
		shootEnemy[i]->GetBullet()->GetHitParticle()->SetSpawnFlag(false);
		shootEnemy[i]->SetLiveFlag(false);
	}
	//ShootEnemy再配置
	for (int i = 0; i < map->GetShootEnemy().size(); i++)
	{
		shootEnemy[i]->SetLiveFlag(true);
		shootEnemy[i]->SetPosition(map->GetShootEnemy()[i]);
		shootEnemy[i]->GetBullet()->SetLiveFlag(false);
	}
	//三角形
	//配置再指定
	for (int i = 0; i < map->GetTriangleA().size(); i++)
	{
		triangle[i]->SetTrianglePosition(map->GetTriangleA()[i], map->GetTriangleB()[i], map->GetTriangleC()[i]);
		triangle[i]->Initialize(dxCommon, textureManager);
	}
#pragma endregion
}
void Scene::SetAssets(DirectXCommon* d, TextureManager* t, SoundManager* s, Input* i, Xinput* x, Camera* c)
{
	dxCommon = d;
	textureManager = t;
	soundManager = s;
	input = i;
	pad = x;
	camera = c;
}


bool Scene::Fade(float time, float count)
{
	if (time >= count) {
		fade = easeIn(Vector3(), Vector3(1.0f,0,0), count / time).x;
		return false;
	}
	return true;
}