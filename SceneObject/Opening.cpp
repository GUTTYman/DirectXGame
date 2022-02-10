#include "Opening.h"

Opening::Opening()
{
	spawnObject = std::make_unique< Object3d>();
}
Opening::~Opening()
{
}

//初期化
void Opening::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	time = 0;
	normalLength = 0.0f;
	step = OpenStep::START;
	cameraEye = Vector3();
	cameraTarget = Vector3();
	shake = Vector3();
	waittime = 0;
	heartbeat = 0.0f;
	spawnObject->Initialize(modelLoader->GetModel(EGG));
	spawnObject->SetRotation(Vector3(0,-90,0));
	scale = Vector3(3, 3, 3);
	spawnObject->SetScale(scale);
	//OpenStepの各項目の長さ
	offCount = 330;
	startCount = 30;
	zoomCount = 150;
	shakeCount = 210;
	spawnCount = 270;

}
//更新処理
void Opening::Update(Vector3 position)
{
	if (step != OpenStep::OFF)
	{
		//ZOOMOUTで一度止まって操作を待つ
		if (!isWait())
		{
			time++;
		}
		//カウントとフラグの移り変わり
		if (time < startCount)
		{
			step = OpenStep::START;
		}
		else if (time < zoomCount)
		{
			step = OpenStep::ZOOMOUT;
		}
		else if (time < shakeCount)
		{
			step = OpenStep::SHAKE;
		}
		else if (time < spawnCount)
		{
			step = OpenStep::SPAWN;
		}
		else if (time < offCount)
		{
			step = OpenStep::OFF;
		}
		spawnObject->Update();
	}

	Vector3 shakeVelocity;
	Vector2 randVel;

	switch (step)
	{
	case OpenStep::OFF:
		time = 0;
		normalLength = 0.0f;
		break;
	case OpenStep::START:
		//カメラ初期値
		cameraEye = Vector3(position.x, position.y, -20);
		cameraTarget = position;
		break;
	case OpenStep::ZOOMOUT:
		//カメラがズームアウトする
		cameraEye = lerp(Vector3(position.x, position.y, -20), Vector3(53.0f, -28.0f, -65.0f), (time - 30) / 120.0f);
		cameraTarget = lerp(position, Vector3(53.0f, -28.0f, 0.0f), (time - 30) / 120.0f);
		if (time == 149)
		{
			if (input->Trigger(DIK_SPACE) || pad->Trigger(XINPUT_A))
			{
				time++;
			}
		}
		break;
	case OpenStep::SHAKE:
		//オブジェクトが振動する
		shakeVelocity = Vector3(5, 0, 0);
		randVel = Vector2(shakeVelocity.x > 0 ? rand() % (int)shakeVelocity.x - shakeVelocity.x / 2 : 0, shakeVelocity.y > 0 ? rand() % (int)shakeVelocity.y - shakeVelocity.y / 2 : 0);
		//移動量をセットする
		shake = Vector3(randVel.x / 10.0f, randVel.y / 10.0f, 0);
		break;
	case OpenStep::SPAWN:
		//オブジェクトが破裂してPlayer誕生
		normalLength += 1.0f;
		//振動を止める
		shake = Vector3();
		break;
	default:
		break;
	}
	//オブジェクトの破裂する音
	if (time == 209) { soundManager->PlayWave(AudioIndex::EXPLOSION); }
	//オブジェクトの処理
	SpawnOBJUpdate(position);

}

void Opening::SpawnOBJUpdate(Vector3 position)
{
	//心臓のような鼓動
	if (step == OpenStep::START || step == OpenStep::ZOOMOUT)
	{
		//拡縮の幅
		static float range = 0.05f;
		if (heartbeat < 6.62f)
		{
			//スケールで鼓動を表現
			scale += Vector3(sin(heartbeat) * range, sin(heartbeat) * range, sin(heartbeat) * range);
			heartbeat += 0.4f;
		}
		else
		{
			waittime++;
		}
		//脈の間隔
		if (waittime > 10)
		{
			//鼓動音
			soundManager->PlayWave(AudioIndex::HEARTBEAT);
			//カウント初期化
			waittime = 0;
			heartbeat = 0.0f;
		}
	}
	spawnObject->SetScale(scale);
	spawnObject->SetPosition(position + shake);
	spawnObject->SetNormalLength(Vector3(normalLength, normalLength, normalLength));
}

void Opening::Update()
{
}

void Opening::Draw(DirectXCommon* dxCommon)
{
	if (step != OpenStep::OFF)
	{
		spawnObject->Draw(dxCommon->GetCommandList());
	}
}

void Opening::Reset()
{
	time = 0;
	spawnCount = 0;
	step = OpenStep::START;
	normalLength = 0.0f;
}

bool Opening::isWait()
{
	if (time != (zoomCount - 1))
	{
		return false;
	}
	return true;
}
