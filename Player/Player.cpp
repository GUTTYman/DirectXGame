#include "Player.h"
Player::Player()
{
	object = std::make_unique< Object3d>();
	tail = std::make_unique< TailManager>(8);
}
Player::~Player()
{
}

void Player::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	//オブジェクトの初期化
	object->Initialize(modelLoader->GetModel(PLAYER));
	//尻尾の初期化
	tail->Initialize(dxCommon, textureManager, 1.5f);
	tail->LerpColor(Vector3(),Vector3(0,1,0));

	//パラメーター初期値
	scale = Vector3(3, 3, 3);
	color = Vector3(1,1,1);
	object->SetColor(color);
	rotation = Vector3();
	liveFlag = false;
	hitBlock = false;
	dead = false;
	a = 0;
	power = 1.0f;
	powerCount = 0.0f;
}

void Player::Update(float gameTime)
{
	if (liveFlag)
	{
		tail->SetScale(scale);
		//Player操作
		Control(gameTime);

		hitBlock = false;	//壁などにあったっていた場合ここより↑↑の行がtrue	↓↓の行がfalseとなる
#pragma region 反発係数計算
		static float maxCount = 500.0f;
		power = lerp(Vector3(1.0f, 0.0f, 0.0f), Vector3(2.0f, 0.0f, 0.0f), powerCount / maxCount).x;
		if (powerCount < maxCount)
		{
			powerCount++;
		}
#pragma endregion

		//体の向きをVelocityから求める
		float direction = atan2f(velocity.y * gameTime, velocity.x * gameTime);
		//しっぽ角度セット
		tail->SetAngle(-direction - 1.57f);
		if (velocity.x * gameTime >= 0.0f)
		{
			rotation = Vector3(0, 0, direction * 57.32484076433121f);
		}
		else if (velocity.x * gameTime < 0.0f)
		{
			rotation = Vector3(180, 0, atan2f(-velocity.y * gameTime, velocity.x * gameTime) * 57.32484076433121f);
		}

		//死んだら(60フレームの間)
		if (dead)
		{
			a += 2;
			//カウントしてから死亡判定になる
			if (a > 60)
			{
				liveFlag = false;
				dead = false;
			}
		}
		else
		{
			position += velocity * gameTime;
			a = 0;
		}
		//ジオメトリシェーダーでフェースを散らせる
		object->SetNormalLength(Vector3(a, a, 0) * gameTime);
		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);
	}
		object->Update();

	//しっぽの更新
	tail->SetTarget(position);
	tail->Update(gameTime);
}



void Player::Control(float gameTime)
{
	//コントローラー操作
	velocity.x += pad->GetLStickX() * 0.015f;
	//上方向の操作
	if (input->Push(DIK_UP) || pad->Push(XINPUT_A))
	{
		velocity.y += 0.02f;
	}
	else
	{
		if (!hitBlock)
		{
			velocity.y -= 0.03f * gameTime;
		}
	}
	//キーボード入力での左右移動
	if (input->Push(DIK_LEFT) || input->Push(DIK_RIGHT))
	{
		if (input->Push(DIK_LEFT))
		{
			velocity.x -= 0.005f;
		}
		if (input->Push(DIK_RIGHT))
		{
			velocity.x += 0.005f;
		}
	}
	else if (pad->GetLStickX() == 0.0f)	//左右移動の操作がされていないとき
	{
		//減速
		if (abs(velocity.x) > 0.1f)
		{
			if (velocity.x > 0.1f)
			{
				velocity.x -= 0.001f;
			}
			if (velocity.x < -0.1f)
			{
				velocity.x += 0.001f;
			}
		}
	}
}

void Player::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
		
		if (!dead)
		{
			tail->Draw(dxCommon);
		}
	}
}

InputNum Player::GetInput()
{
	if (input->Push(DIK_LEFT) || pad->GetLStickX() < 0.0f)
	{
		return LEFT;
	}
	if (input->Push(DIK_RIGHT) || pad->GetLStickX() > 0.0f)
	{
		return RIGHT;
	}
	if (input->Push(DIK_UP) || pad->Push(XINPUT_A))
	{
		return UP;
	}
		return NONE;
}

void Player::SetDead(bool b)
{
	dead = b;
	if (b)
	{
		soundManager->PlayWave(AudioIndex::DEAD);
	}
}
