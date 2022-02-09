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
	//���݂̃}�b�v
	initnum = 0;
	//map
	map = new Map();
	map->Initialize();

	//�e�I�u�W�F�N�g�̌��w��
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
	//�̂��I�u�W�F�N�g
	for (int i = 0; i < linkObject.size(); i++){linkObject[i] = new LinkObjectManager(rand() % 13 + 2);}
	//������̂��I�u�W�F�N�g
	for (int i = 0; i < linkObjectD.size(); i++){linkObjectD[i] = new LinkObjectManager(rand() % 13 + 2);}
	//�L�m�R�I�u�W�F�N�g
	for (int i = 0; i < boundObject.size(); i++){boundObject[i] = new BoundObjectManager();}
	//���̐A���I�u�W�F�N�g
	for (int i = 0; i < spherePlant.size(); i++)
	{
		float size = rand() % 10;
		spherePlant[i] = new SpherePlantManager(size + 5);
	}
	//���������̐A���I�u�W�F�N�g
	for (int i = 0; i < spherePlantD.size(); i++)
	{
		float size = rand() % 15;
		spherePlantD[i] = new SpherePlantManager(size + 5);
	}
	//�u���b�N�I�u�W�F�N�g
	for (int i = 0; i < block.size(); i++){block[i] = new TileBlock();}
	//�ǃI�u�W�F�N�g
	for (int i = 0; i < wall.size(); i++){wall[i] = new Wall();}
	//�{���I�u�W�F�N�g
	for (int i = 0; i < bomb.size(); i++){bomb[i] = new Bomb();}
	//������@�I�u�W�F�N�g
	for (int i = 0; i < cutter.size(); i++){cutter[i] = new Cutter();}
	//���B�I�u�W�F�N�g
	for (int i = 0; i < rise.size(); i++){rise[i] = new RiseObject();}
	//ShootEnemy
	for (int i = 0; i < shootEnemy.size(); i++){shootEnemy[i] = new ShootEnemy();}
	//�O�p�`�I�u�W�F�N�g
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

	//�̂��I�u�W�F�N�g
	for (int i = 0; i < linkObject.size(); i++)
	{
		linkObject[i]->Initialize(dxCommon, textureManager);
	}
	//������̂��I�u�W�F�N�g
	for (int i = 0; i < linkObjectD.size(); i++)
	{
		linkObjectD[i]->Initialize(dxCommon, textureManager);
		linkObjectD[i]->IsReverse(true);
	}
	//�L�m�R�I�u�W�F�N�g
	for (int i = 0; i < boundObject.size(); i++)
	{
		boundObject[i]->Initialize(dxCommon, textureManager);
	}
	//���̐A���I�u�W�F�N�g
	for (int i = 0; i < spherePlant.size(); i++)
	{
		float size = rand() % 10;
		spherePlant[i]->Initialize(dxCommon, textureManager, size / 10.0f + 1.5f);
	}
	//���������̐A���I�u�W�F�N�g
	for (int i = 0; i < spherePlantD.size(); i++)
	{
		float size = rand() % 20;
		spherePlantD[i]->Initialize(dxCommon, textureManager, size / 10.0f + 1.5f);
		spherePlantD[i]->SetAngle(3.14f);
	}
	//�u���b�N�I�u�W�F�N�g
	for (int i = 0; i < block.size(); i++)
	{
		block[i]->Initialize(dxCommon, textureManager);
	}
	//�ǃI�u�W�F�N�g
	for (int i = 0; i < wall.size(); i++)
	{
		wall[i]->Initialize(dxCommon, textureManager);
	}
	//�{���I�u�W�F�N�g
	for (int i = 0; i < bomb.size(); i++)
	{
		bomb[i]->Initialize(dxCommon, textureManager);
	}
	//������@�I�u�W�F�N�g
	for (int i = 0; i < cutter.size(); i++)
	{
		cutter[i]->Initialize(dxCommon, textureManager);
	}
	//���B�I�u�W�F�N�g
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
//�}�b�v�؂�ւ����Ƃ̍Ĕz�u
void Scene::MapLoad()
{
	map->SetNowmap(mapnum);
#pragma region �|�W�V�����w��
	//Player
	player->SetVelocity(Vector3());
	player->PlayerReset();
	player->SetPosition(map->GetPlayerPosition());
	player->Update();
	//�S�[���Ĕz�u
	goal->SetPosition(map->GetGoalPosition());
	//�{�[���Ĕz�u
	for (int i = 0; i < map->GetBall().size(); i++)
	{
		ball[i]->SetPosition(map->GetBall()[i]);
		ball[i]->SetVelocity(Vector3(-0.6f, 0, 0));
	}

	//�̂��I�u�W�F�N�g
	//�z�u�Ďw��

	for (int i = 0; i < map->GetLinkObject().size(); i++)
	{
		linkObject[i]->SetTarget(map->GetLinkObject()[i]);
	}
	//�������̂��I�u�W�F�N�g
	//�z�u�Ďw��
	for (int i = 0; i < map->GetLinkObjectDown().size(); i++)
	{
		linkObjectD[i]->SetTarget(map->GetLinkObjectDown()[i]);
	}

	//�L�m�R�I�u�W�F�N�g
	//�z�u�Ďw��
	for (int i = 0; i < map->GetBoundObject().size(); i++)
	{
		boundObject[i]->SetPosition(map->GetBoundObject()[i]);
	}
	//���̐A���I�u�W�F�N�g
	//�z�u�Ďw��
	for (int i = 0; i < map->GetSpherePlant().size(); i++)
	{
		spherePlant[i]->SetTarget(map->GetSpherePlant()[i]);
	}
	//���������̐A���I�u�W�F�N�g
	//�z�u�Ďw��
	for (int i = 0; i < map->GetSpherePlantDown().size(); i++)
	{
		spherePlantD[i]->SetTarget(map->GetSpherePlantDown()[i]);
	}
	//�u���b�N�I�u�W�F�N�g
	//�z�u�Ďw��
	for (int i = 0; i < map->GetBlock().size(); i++)
	{
		block[i]->SetPosition(map->GetBlock()[i]);
	}
	//�ǃI�u�W�F�N�g
	//�z�u�Ďw��
	for (int i = 0; i < map->GetWall().size(); i++)
	{
		wall[i]->SetPosition(map->GetWall()[i]);
	}
	//�{���I�u�W�F�N�g
	//�z�u�Ďw��
	for (int i = 0; i < map->GetBomb().size(); i++)
	{
		bomb[i]->SetLiveFlag(true);
		bomb[i]->SetPosition(map->GetBomb()[i]);
	}
	//������@�I�u�W�F�N�g
	//�z�u�Ďw��
	for (int i = 0; i < map->GetCutter().size(); i++)
	{
		cutter[i]->SetLiveFlag(true);
		cutter[i]->SetPosition(map->GetCutter()[i]);
	}
	//���B�I�u�W�F�N�g
	//�z�u�Ďw��
	for (int i = 0; i < map->GetRise().size(); i++)
	{
		rise[i]->SetLiveFlag(true);
		rise[i]->SetPosition(map->GetRise()[i]);
	}
	//�g��Ȃ��G������
	for (int i = 0; i < shootEnemy.size(); i++)
	{
		shootEnemy[i]->GetBullet()->GetHitParticle()->SetSpawnFlag(false);
		shootEnemy[i]->SetLiveFlag(false);
	}
	//ShootEnemy�Ĕz�u
	for (int i = 0; i < map->GetShootEnemy().size(); i++)
	{
		shootEnemy[i]->SetLiveFlag(true);
		shootEnemy[i]->SetPosition(map->GetShootEnemy()[i]);
		shootEnemy[i]->GetBullet()->SetLiveFlag(false);
	}
	//�O�p�`
	//�z�u�Ďw��
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