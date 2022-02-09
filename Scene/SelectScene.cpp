#include "SelectScene.h"
SelectScene::~SelectScene()
{

}
//マップ選択の更新
void SelectScene::Update()
{
	//背景
	back->SelectUpdate();
	//セレクトボックス
	select->Update();
	//ボタンUI
	sceneObject->ButtonUpdate(Vector3(0, -15, 0), Vector3(3, 3, 3));
	//カメラ
	camera->SetEye(Vector3(0, 0, -50));
	camera->SetTarget(Vector3(0, 0, 0));

	//ステージを決定したらPlayに切り替わる
	if (select->GetEnter() == 2)
	{
		//選んだマップ番号をセット
		mapnum = select->GetMapSelect();
		//シーンをPlayに切り替え
		scene = PLAY_SCENE;
		//選んだマップを作成
		MapLoad();
		//フェードイン値初期化
		Scene::SetFade(0.0f);
		count = 0;
		//カメラ初期化
		camera->SetTarget(Vector3(53.0f, -28.0f, 0.0f));
		camera->SetEye(Vector3(53.0f, -28.0f, -65.0f));
	}
}

//マップ選択の描画
void SelectScene::Draw()
{
	//背景
	back->SelectDraw(dxCommon);
	//ボタンUI
	sceneObject->ButtonDraw(dxCommon);
	//ステージのセレクトボックス
	select->Draw(dxCommon);
}