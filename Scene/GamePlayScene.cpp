#include "GamePlayScene.h"
GamePlayScene::~GamePlayScene()
{
	delete opening;
}
void GamePlayScene::Initialize()
{
	//GamePlayScene専用の開始時演出オブジェクト
	opening = new Opening();
	opening->Initialize(dxCommon,textureManager);
	//初期化したオブジェクトを一度だけ更新しておく
	opening->Update(map->GetPlayerPosition());

}
//ゲームプレイ中の更新
void GamePlayScene::Update()
{

	//開始時の演出の更新
	opening->Update(map->GetPlayerPosition());

	//開始時のフェードイン
	if (Fade(120.0f, count))
	{
		//Player操作待ちの間のUI
		if (opening->isWait())
		{
			sceneObject->ButtonUpdate(map->GetPlayerPosition() + Vector3(0, 5, 0), Vector3(1.5f,0.4f,1.5f));
		}
		//開始時の演出終了したら
		if (opening->GetStep()==OpenStep::OFF|| opening->GetStep() == OpenStep::SPAWN)
		{
			//プレイヤー
			player->Update();
			//シーンオブジェクト（UIなど）
			sceneObject->PlayUpdate(player->TopPosition(), false);
			//Playerが全部死んだらシーン切り替え
			if (!player->GetLiveFlag())
			{
				scene = GAMEOVER_SCENE;
			}
		}
		else
		{
			//卵から飛びだす
			player->GetPleyer()[player->TopPlayer()]->SetVelocity(Vector3(0.05f, 1, 0));
		}
		//マップ切り替え
		ChangeMap();
	}
	else
	{
		count++;
	}
#pragma region 各オブジェクトのUpdate呼び出し
	//ShootEnemy
	ShootEnemy::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetShootEnemy().size(); i++)
	{
		shootEnemy[i]->Update();
	}
	//のれんオブジェクト
	LinkObject::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetLinkObject().size(); i++)
	{
		linkObject[i]->Update();
	}
	//下方向のれんオブジェクト
	LinkObject::SetPlayer(player->GetPleyer());
	LinkObject::SetShootEnemy(shootEnemy);
	for (int i = 0; i < map->GetLinkObjectDown().size(); i++)
	{
		linkObjectD[i]->Update();
	}
	//キノコオブジェクト
	BoundObject::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetBoundObject().size(); i++)
	{
		boundObject[i]->Update();
	}
	//球体植物オブジェクト
	SpherePlant::SetPlayer(player->GetPleyer());
	SpherePlant::SetShootEnemy(shootEnemy);
	for (int i = 0; i < map->GetSpherePlant().size(); i++)
	{
		spherePlant[i]->Update();
	}
	//下方向球体植物オブジェクト
	for (int i = 0; i < map->GetSpherePlantDown().size(); i++)
	{
		spherePlantD[i]->Update();
	}
	//ブロックオブジェクト
	TileBlock::SetHitObject(player->GetPleyer(), ball, shootEnemy);
	for (int i = 0; i < map->GetBlock().size(); i++)
	{
		block[i]->Update();
	}
	//壁
	Wall::SetHitObject(player->GetPleyer(),ball,shootEnemy);
	for (int i = 0; i < map->GetWall().size(); i++)
	{
		wall[i]->Update();
	}
	//ボムオブジェクト
	Bomb::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetBomb().size(); i++)
	{
		bomb[i]->Update();
	}
	//草刈り機オブジェクト
	Cutter::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetCutter().size(); i++)
	{
		cutter[i]->Update();
	}
	//増殖オブジェクト
	RiseObject::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetRise().size(); i++)
	{
		rise[i]->Update();
		rise[i]->PlayerRise(player, 10, dxCommon, textureManager, 0);
	}
	
	//三角形オブジェクト
	Triangle::SetHitObject(player->GetPleyer(), ball, shootEnemy);
	for (int i = 0; i < map->GetTriangleA().size(); i++)
	{
		triangle[i]->Update();
	}
	//ゴール
	Goal::SetPlayer(player->GetPleyer());
	goal->Update();
	//ボール
	Ball::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetBall().size(); i++)
	{
		ball[i]->Update();
	}

	//背景
	back->Update();
	//マップごとに看板のテクスチャ切り替え
	switch (mapnum)
	{
	case 0:
		sceneObject->SetBoardTexture(9);
		break;
	case 1:
		sceneObject->SetBoardTexture(1);
		break;
	case 2:
		sceneObject->SetBoardTexture(17);
		break;
	case 3:
		sceneObject->SetBoardTexture(2);
		break;
	case 4:
		sceneObject->SetBoardTexture(18);
		break;
	case 5:
		sceneObject->SetBoardTexture(19);
		break;
	}
	//操作説明の看板
	sceneObject->BoradUpdate(Vector3(50, 0, 0), player->GetPleyer());

#pragma region カメラ操作
	//カメラシェイクの値加算
	Vector3 cameraShake = Vector3();
	for (int i = 0; i < ball.size(); i++)
	{
		cameraShake += ball[i]->GetCameraShake();
	}
	//開始演出時のカメラ演出
	if (opening->GetStep() == OpenStep::OFF || opening->GetStep() == OpenStep::SPAWN)
	{
		//Playerが生きている間カメラが追う
		if (player->GetLiveFlag())
		{
			camera->SetEye(Vector3(player->PlayerCamera().x, -28.0f + cameraShake.y, -65.0f));
			camera->SetTarget(Vector3(player->PlayerCamera().x, -28.0f + cameraShake.y, 0.0f));
		}
	}
	else
	{
		//開始時のカメラ
		OpeningUpdate();
	}
#pragma endregion


#pragma endregion
}


void GamePlayScene::OpeningUpdate()
{
	//開始時カメラが卵から離れていく
	camera->SetEye(opening->GetCameraEye());
	camera->SetTarget(opening->GetCameraTarget());
}
void GamePlayScene::ChangeMap()
{
	//ゴールしたら
	if (goal->GetGoalFlag())
	{
		if (mapnum == map->GetMapCount() - 1)
		{
			scene = CLEAR_SCENE;
			//クリア情報をリセット
			opening->Reset();
			select->ResetClear();

		}
		else
		{
			count = 0;
			//ステージ選択に移る
			scene = SELECT_SCENE;
			//ステージ開放
			select->SetNext(true);
		}
		//マップを読み込みゴールフラグをfalseにする
		MapLoad();
		goal->SetGoalFlag(false);
	}
}
//ゲームプレイ中の描画
void GamePlayScene::Draw()
{
#pragma region Play中の描画
	
	for (int i = 0; i < map->GetLinkObject().size(); i++)
	{
		linkObject[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetLinkObjectDown().size(); i++)
	{
		linkObjectD[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetBoundObject().size(); i++)
	{
		boundObject[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetSpherePlant().size(); i++)
	{
		spherePlant[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetSpherePlantDown().size(); i++)
	{
		spherePlantD[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetBlock().size(); i++)
	{
		block[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetWall().size(); i++)
	{
		wall[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetBomb().size(); i++)
	{
		bomb[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetCutter().size(); i++)
	{
		cutter[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetRise().size(); i++)
	{
		rise[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetShootEnemy().size(); i++)
	{
		shootEnemy[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetTriangleA().size(); i++)
	{
		triangle[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetBall().size(); i++)
	{
		ball[i]->Draw(dxCommon);
	}
	//ゴール
	goal->Draw(dxCommon);
	//背景
	back->Draw(dxCommon);
	//操作説明の看板
	sceneObject->BroadDraw(dxCommon);

	//止まっている間だけUI表示
	if (player->GetRestTime() > 60)
	{
		sceneObject->PlayDraw(dxCommon);
	}
	//卵が割れたら描画する
	if (opening->GetStep() == OpenStep::OFF || opening->GetStep() == OpenStep::SPAWN)
	{
		player->Draw(dxCommon);
	}
	//Player操作待ちの間のUI
	if (opening->isWait())
	{
		sceneObject->ButtonDraw(dxCommon);
	}
	//開始時の卵オブジェクト
	opening->Draw(dxCommon);
#pragma endregion
}

