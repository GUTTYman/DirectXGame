#include "Loader.h"
Loader::Loader(TextureManager* texture,SoundManager* sound)
{
	this->textureManager = texture;
	this->soundManager = sound;
	//モデル読み込み
	AddModel(ModelIndex::PLAYER, "p2");
	AddModel(ModelIndex::SPHERE, "sphere");
	AddModel(ModelIndex::CUBE, "cube");
	AddModel(ModelIndex::BALL1, "ball1");
	AddModel(ModelIndex::BACK1, "back1");
	AddModel(ModelIndex::SPIKEBALL, "hummer");
	AddModel(ModelIndex::CUTTER, "cutter");
	AddModel(ModelIndex::RISE, "rise2");
	AddModel(ModelIndex::TITLE, "title");
	AddModel(ModelIndex::CLEAR, "clear");
	AddModel(ModelIndex::GAMEOVER, "gameover");
	AddModel(ModelIndex::BUTTON, "button");
	AddModel(ModelIndex::LSTICK, "padstick");
	AddModel(ModelIndex::SELECTBOX1, "select");
	AddModel(ModelIndex::SELECTBOX2, "select");
	AddModel(ModelIndex::SELECTBOX3, "select");
	AddModel(ModelIndex::SELECTBOX4, "select");
	AddModel(ModelIndex::SELECTBOX5, "select");
	AddModel(ModelIndex::SELECTBOX6, "select");
	AddModel(ModelIndex::EYE, "sphere");
	AddModel(ModelIndex::KINOKO, "kinoko");
	AddModel(ModelIndex::EGG, "rise");
	AddModel(ModelIndex::BOARD, "board");
	//パーティクル用モデル読み込み
	model.emplace_back(new Model);
	model[ModelIndex::POINTVERTEX]->PointVertex();
	AddModel(ModelIndex::X3, "x3");

	//テクスチャーのロード
	textureManager->LoadTexture(0, L"Resources/white.png");
	textureManager->LoadTexture(1, L"Resources/EnemyBoard.png");
	textureManager->LoadTexture(2, L"Resources/BallBoard.png");
	textureManager->LoadTexture(3, L"Resources/p2.png");
	textureManager->LoadTexture(4, L"Resources/stickL.png");
	textureManager->LoadTexture(5, L"Resources/rise.png");
	textureManager->LoadTexture(6, L"Resources/keyUI.png");
	textureManager->LoadTexture(7, L"Resources/eye.png");
	textureManager->LoadTexture(8, L"Resources/buttonA.png");
	textureManager->LoadTexture(9, L"Resources/AbuttonBoard.png");
	textureManager->LoadTexture(10, L"Resources/close.png");
	textureManager->LoadTexture(11, L"Resources/stage1.png");
	textureManager->LoadTexture(12, L"Resources/stage2.png");
	textureManager->LoadTexture(13, L"Resources/stage3.png");
	textureManager->LoadTexture(14, L"Resources/stage4.png");
	textureManager->LoadTexture(15, L"Resources/stage5.png");
	textureManager->LoadTexture(16, L"Resources/stage6.png");
	textureManager->LoadTexture(17, L"Resources/CutterBoard.png");
	textureManager->LoadTexture(18, L"Resources/ManyEnemyBoard.png");
	textureManager->LoadTexture(19, L"Resources/TwoBallBoard.png");
	

	//サウンドのロード
	soundManager->LoadWave(AudioIndex::DONOT, "Resources/Sound/donot.wav");
	soundManager->LoadWave(AudioIndex::SELECT, "Resources/Sound/select.wav");
	soundManager->LoadWave(AudioIndex::DEAD, "Resources/Sound/dead.wav");
	soundManager->LoadWave(AudioIndex::EXPLOSION, "Resources/Sound/expl.wav");
	soundManager->LoadWave(AudioIndex::PICKUP, "Resources/Sound/pickup.wav");
	soundManager->LoadWave(AudioIndex::WALLHIT, "Resources/Sound/wallHit.wav");
	soundManager->LoadWave(AudioIndex::EXPLOSION2, "Resources/Sound/expl2.wav");
	soundManager->LoadWave(AudioIndex::RISEUP, "Resources/Sound/rise.wav");
	soundManager->LoadWave(AudioIndex::GOAL, "Resources/Sound/goal.wav");
	soundManager->LoadWave(AudioIndex::HEARTBEAT, "Resources/Sound/heartbeat.wav");
	soundManager->LoadWave(AudioIndex::SHOOT, "Resources/Sound/shoot.wav");

}

Loader::~Loader()
{
}

void Loader::AddModel(ModelIndex m, std::string filename)
{
	model.emplace_back(std::make_unique< Model>());
	model[m]->LoadModel(filename, false);
}

void Loader::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	model[ModelIndex::PLAYER]->Initialize(dxCommon, textureManager, 3);
	model[ModelIndex::SPHERE]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::CUBE]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::BALL1]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::BACK1]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::SPIKEBALL]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::CUTTER]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::RISE]->Initialize(dxCommon, textureManager, 5);
	model[ModelIndex::TITLE]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::CLEAR]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::GAMEOVER]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::BUTTON]->Initialize(dxCommon, textureManager, 8);
	model[ModelIndex::LSTICK]->Initialize(dxCommon, textureManager, 4);
	model[ModelIndex::SELECTBOX1]->Initialize(dxCommon, textureManager, 10);
	model[ModelIndex::SELECTBOX2]->Initialize(dxCommon, textureManager, 10);
	model[ModelIndex::SELECTBOX3]->Initialize(dxCommon, textureManager, 10);
	model[ModelIndex::SELECTBOX4]->Initialize(dxCommon, textureManager, 10);
	model[ModelIndex::SELECTBOX5]->Initialize(dxCommon, textureManager, 10);
	model[ModelIndex::SELECTBOX6]->Initialize(dxCommon, textureManager, 10);
	model[ModelIndex::EYE]->Initialize(dxCommon, textureManager, 7);
	model[ModelIndex::KINOKO]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::EGG]->Initialize(dxCommon, textureManager, 5);
	model[ModelIndex::BOARD]->Initialize(dxCommon, textureManager, 9);
	model[ModelIndex::POINTVERTEX]->Initialize(dxCommon, textureManager, 0);
	model[ModelIndex::X3]->Initialize(dxCommon, textureManager, 0);
}

Model* Loader::GetModel(int modelIndex)
{
	return model[modelIndex].get();
}
