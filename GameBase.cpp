#include "GameBase.h"

#pragma comment(lib,"winmm.lib")

std::unique_ptr < SoundManager> GameBase::soundManager;
std::unique_ptr<Loader> GameBase::modelLoad;

using namespace std;

void GameBase::Run()
{
	//初期化
	Initialize();

	while (true)
	{
		if (endFlag) {
			break;
		}
		if (input->Trigger(DIK_ESCAPE))
		{
			endFlag = true;
		}

		//更新
		Update();

		//描画
		Draw();

		//フレーム
		FrameRate();
	}
	Finalize();
}

void GameBase::Initialize()
{
	
	//WindowsAPI初期化
	winApp = make_unique< WinApp>();
	winApp->Initialize();

	//DirectX初期化処理ここから
	dxCommon = make_unique<DirectXCommon>();
	dxCommon->Initialize(winApp.get());

	//TextureManagerの初期化
	textureManager = make_unique< TextureManager>();
	textureManager->Initialize(dxCommon.get());

	//SoundManagerの初期化:
	soundManager = make_unique< SoundManager>();
	soundManager->Initialize();

	//ModelLoadの初期化
	modelLoad = make_unique< Loader>(textureManager.get(), soundManager.get());
	modelLoad->Initialize(dxCommon.get(), textureManager.get());

	//Inputの初期化
	input = make_unique< Input>();
	input->Initialize(winApp->GetHwnd());
	//XInputの初期化
	pad = make_unique< Xinput>();

	//Cameraの初期化
	camera = make_unique< Camera>();
	camera->Initialize();

	//スプライトの静的初期化
	Sprite::StaticInitialize(dxCommon.get(), textureManager.get());
	//3Dオブジェクトの静的初期化
	Object3d::StaticInitialize(dxCommon.get(), camera.get());
	//GPUパーティクルの静的初期化
	GPUParticle::StaticInitialize(dxCommon.get(), camera.get());
	//ライトの静的初期化
	Light::StaticInitialize(dxCommon->GetDevice());

	//ライトの生成
	light = Light::Create();
	//ライトの位置を設定
	light->SetLightDir({ 0,-1,1});
	

	//スプライト生成
	/*sprite = make_unique< Sprite();
	sprite->Initialize(0);*/

	//フレームレートの初期化
	QueryPerformanceFrequency(&freqTime);
	QueryPerformanceCounter(&startTime);
}

void GameBase::Update()
{

#pragma region ウィンドウメッセージ処理
	if (winApp->Update()) {
		endFlag = true;
	}
#pragma endregion

	//3Dオブジェクトにライトをセット
	Object3d::SetLight(light.get());

	input->Update();
	pad->Update();
	camera->Update();
	light->Update();
}

void GameBase::Finalize()
{

}
//フレームレート固定
void GameBase::FrameRate()
{
	if (count == MinFrameTime)
	{
		QueryPerformanceCounter(&endTime);
		fps = 1000.0f / (static_cast<float>((endTime.QuadPart - startTime.QuadPart) * 1000.0f / freqTime.QuadPart) / MinFrameTime);
		count = 0;
		startTime = endTime;
	}
	count++;
	QueryPerformanceCounter(&endTime);
	{
		//1ミリ秒
		//DWORD sleepTime = static_cast<DWORD>((MinFrameTime - frameTime) * 1000);
		DWORD sleepTime = static_cast<DWORD>((1000.0f / MinFrameTime) * count - (endTime.QuadPart - startTime.QuadPart) * 1000.0f / freqTime.QuadPart);

		if (sleepTime < 18 && sleepTime>0)
		{
			timeBeginPeriod(1);
			Sleep(sleepTime);
			timeEndPeriod(1);
		}
		else
		{
			timeBeginPeriod(1);
			Sleep(1);
			timeEndPeriod(1);
		}
	}
}
