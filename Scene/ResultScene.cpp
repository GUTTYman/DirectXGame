#include "ResultScene.h"
ResultScene::~ResultScene()
{

}
//リザルトシーンの更新
void ResultScene::Update()
{
	if (scene == CLEAR_SCENE)//クリアの時
	{
		if (input->Trigger(DIK_SPACE) || pad->Trigger(XINPUT_A))
		{
			//タイトルに戻る
			scene = TITLE_SCENE;
		}
		sceneObject->ClearUpdate(Vector3(camera->GetEye().x, camera->GetEye().y, camera->GetEye().z));
	}
	else if (scene == GAMEOVER_SCENE)//ゲームオーバーの時
	{
		if (input->Trigger(DIK_SPACE) || pad->Trigger(XINPUT_A))
		{
			//セレクトに戻る
			scene = SELECT_SCENE;
		}
		sceneObject->GameOverUpdate(Vector3(camera->GetEye().x, camera->GetEye().y, camera->GetEye().z));
	}
}

//リザルトシーンの描画
void ResultScene::Draw()
{
	//クリアの時
	if (scene == CLEAR_SCENE)
	{
		sceneObject->ClearDraw(dxCommon);
	}
	//ゲームオーバーの時
	if (scene == GAMEOVER_SCENE)
	{
		sceneObject->GameOverDraw(dxCommon);
	}
}

