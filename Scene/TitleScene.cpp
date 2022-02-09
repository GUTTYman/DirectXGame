#include "TitleScene.h"

TitleScene::~TitleScene()
{
}


//タイトルシーンの更新
void TitleScene::Update()
{
	titleCount++;
	//背景
	back->SelectUpdate();
	if (!start)
	{
		if (input->Trigger(DIK_SPACE) || pad->Trigger(XINPUT_A))
		{
			start = true;
			soundManager->PlayWave(AudioIndex::EXPLOSION2);
			titleCount = 0;
		}
		//ボタンUIオブジェクト
		sceneObject->ButtonUpdate(Vector3(0, -15, 0), Vector3(2, 3, 3));
	}
	else
	{
		if(titleCount>120)
		{
			//セレクトシーンに移動
			scene = SELECT_SCENE;
			//各加算した値をリセット
			titleCount = 120;
			start = false;
		}
	}
	//カウントとタイトルオブジェクトの頂点振動に反映させる条件
	if (!start || titleCount < 60)
	{
		sceneObject->SetCount(titleCount);
	}
	sceneObject->Update();
	//カメラ
	camera->SetEye(Vector3(0,0,-50));
	camera->SetTarget(Vector3(0,0,0));
}

//タイトルシーンの描画
void TitleScene::Draw()
{
	//背景
	back->SelectDraw(dxCommon);
	//Title
	sceneObject->Draw(dxCommon);
	
	if (!start)
	{
		//ボタンUI
		sceneObject->ButtonDraw(dxCommon);
	}

}

