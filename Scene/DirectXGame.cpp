#include "DirectXGame.h"
using namespace DirectX;
using namespace Microsoft::WRL;
void DirectXGame::Initialize()
{
	//基底クラスの初期化
	GameBase::Initialize();
	//ポストエフェクト用テクスチャの読み込み
	textureManager->LoadTexture(100, L"Resources/white.png");
	//ポストエフェクトの初期化
	postEffect = std::make_unique< PostEffect>();
	postEffect->Initialize();
	gaussian = std::make_unique< Gaussian>();
	gaussian->Initialize();
	gaussian->SetShift(0.01f);

	//モデルローダーのクラスを貸す
	GameObject::SetModelLoad(modelLoad.get());
	//シーンの基底クラスに貸す
	Scene::SetAssets(dxCommon.get(), textureManager.get(), soundManager.get(), input.get(), pad.get(), camera.get());

	//各シーンの初期化
	titleScene = std::make_unique< TitleScene>();
	selectScene = std::make_unique< SelectScene>();	
	gameplayScene = std::make_unique< GamePlayScene>();
	gameplayScene->Initialize();
	resultScene = std::make_unique< ResultScene>();
	Scene::Initialize();
	

}

void DirectXGame::Update()
{
	//基底クラスの更新処理
	GameBase::Update();
	//GameObjectに貸す
	GameObject::SetAssets(soundManager.get(),input.get(),pad.get());
	//シーンの基底クラスに貸す
	Scene::SetAssets(dxCommon.get(),textureManager.get(),soundManager.get(),input.get(),pad.get(),camera.get());

	//各シーンの更新処理
	switch (Scene::GetScene())
	{
	case SceneFlag::TITLE_SCENE:
		//湾曲の強さ設定
		postEffect->SetShift(0.5f);
		postEffect->SetRGBShift(0.0f);
		gaussian->SetShift(0.0f);
		Scene::SetFade(1.0f);
		titleScene->Update();
		break;
	case SceneFlag::SELECT_SCENE:
		//湾曲の強さ設定
		postEffect->SetShift(0.1f);
		postEffect->SetRGBShift(selectScene->GetSelectManagerObject()->GetRGBShift());
		gaussian->SetShift(0.0f);
		selectScene->Update();
		break;
	case SceneFlag::PLAY_SCENE:
		//湾曲の強さ設定
		postEffect->SetShift(0.4f);
		postEffect->SetRGBShift(0.0f);
		gaussian->SetShift(0.0f);
		gameplayScene->Update();
		break;
	case SceneFlag::GAMEOVER_SCENE:
		//湾曲の強さ設定
		postEffect->SetShift(0.4f);
		gaussian->SetShift(0.02f);
		//ゲームオーバーの後ろにステージを動かしておく
		gameplayScene->Update();
		resultScene->Update();
	default:
		//湾曲の強さ設定
		postEffect->SetShift(0.4f);
		gaussian->SetShift(0.02f);
		resultScene->Update();
		break;
	}
}

void DirectXGame::Draw()
{
	//ポストエフェクトの前描画
	postEffect->PreDrawScene(dxCommon->GetCommandList());
	//フェードインの値セット
	postEffect->SetFade(Scene::GetFade());

	//各シーンの描画切り替え
	switch (Scene::GetScene())
	{
	case SceneFlag::TITLE_SCENE:
		titleScene->Draw();
		break;
	case SceneFlag::SELECT_SCENE:
		selectScene->Draw();
		break;
	case SceneFlag::PLAY_SCENE:
		gameplayScene->Draw();
		break;
	default:
		//後ろにゲーム画面を表示したまま
		gameplayScene->Draw();
		resultScene->Draw();
		break;
	}
	//スプライト
	Sprite::SetPiepelineState(dxCommon->GetCommandList());
	
	//ポストエフェクトの後描画
	postEffect->PostDrawScene(dxCommon->GetCommandList());

	gaussian->PreDrawScene(dxCommon->GetCommandList());
	postEffect->Draw(dxCommon->GetCommandList());
	gaussian->PostDrawScene(dxCommon->GetCommandList());

#pragma region postEffect

	dxCommon->BeginDraw();
	
	gaussian->Draw(dxCommon->GetCommandList());

	dxCommon->EndDraw();
}
#pragma endregion

void DirectXGame::Finalize()
{
	Scene::Finalize();
}
