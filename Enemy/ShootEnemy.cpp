#include "ShootEnemy.h"

std::vector<Player*> ShootEnemy::player;
ShootEnemy::ShootEnemy()
{
	eye = std::make_unique< Object3d>();
	cubeOBJ = std::make_unique< GPUParticle>();

	fire = std::make_unique< FireParticle>();
	bullet = std::make_unique< Bullet>();
}
ShootEnemy::~ShootEnemy()
{
	
}
void ShootEnemy::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	fire->Initialize(dxCommon, textureManager);
	bullet->Initialize(dxCommon, textureManager);
	a = 0.0f;
	liveFlag = true;
	dead = false;
	color = Vector3(1,1,1);
	rotation = Vector3(-20, 0, 0);
	scale = Vector3(2, 2, 2);

	//体の周りのオブジェクト
	cubeOBJ->Initialize(modelLoader->GetModel(ModelIndex::CUBE));
	cubeOBJ->SetColor(Vector3());
	cubeOBJ->SetScale(Vector3(1, 1, 1));
	//cube用カウント
	cubeCount = 0;

	//目のオブジェクト
	eye->Initialize(modelLoader->GetModel(EYE));
	eye->SetColor(color);
	eye->SetScale(scale);
}

void ShootEnemy::Update()
{
	if (liveFlag)
	{
#pragma region
		//プレイヤーとの当たり判定
		for (int i = 0; i < player.size(); i++)
		{
			//一定範囲に入ったら撃ってくる
			if (SphereAndSphere(position, player[i]->GetPosition(), 60, player[i]->GetScale().x, player[i]->GetLiveFlag(),liveFlag))
			{
				//弾が描画されていない状態
				if (!bullet->GetLiveFlag())
				{
					//弾の衝突パーティクルが出ていない状態
					if (!bullet->GetHitParticle()->GetSpawn())
					{
						//次の弾をセット
						bullet->SetVelocity(Vector3(player[i]->GetPosition() - position).normalize() * 0.8f);
						bullet->SetLiveFlag(true);
						//発射音を再生
						soundManager->PlayWave(AudioIndex::SHOOT);
					}
				}
			}
			//Playerが死んでいなかったら
			if (!player[i]->GetDead())
			{
				//衝突した弾とPlayerが消滅（死亡）
				if (SphereAndSphere(bullet->GetPosition(), player[i]->GetPosition(), bullet->GetScale().x, player[i]->GetScale().x, player[i]->GetLiveFlag(), bullet->GetLiveFlag()))
				{
					player[i]->SetDead(true);
					bullet->SetLiveFlag(false);
					bullet->GetHitParticle()->SetSpawnFlag(true);

				}
			}
		}
		
		//反復移動繰り返し
		velocity = Vector3(sin(a) * 0.1f, 0, 0);
		position += velocity;
		a += 0.01f;
		//目のオブジェクト更新
		eye->SetPosition(position);
		eye->SetRotation(rotation);
		eye->Update();
		//弾が描画されていない状態
		if (!bullet->GetLiveFlag())
		{
			//ポジションを更新
			bullet->SetPosition(position);
		}
		//弾の更新
		bullet->Update();

		//体の周りのオブジェクトUpdate
		CubeOBJUpdate();
		//パーティクルのUpdate
		fire->Update(position);
#pragma endregion
	}
}
void ShootEnemy::CubeOBJUpdate()
{
	cubeCount += 1;
	//体の周りをオブジェクトが回転している
	cubeOBJ->SetPosition(position);
	//ShootEnemyParticleGSで制御
	cubeOBJ->SetTime(cubeCount);
	cubeOBJ->Update();
}
void ShootEnemy::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		//体の周りのオブジェクト
		cubeOBJ->Draw(dxCommon->GetCommandList(),SHOOTENEMY,20);
		//弾
		bullet->Draw(dxCommon);
		//目
		eye->Draw(dxCommon->GetCommandList());
		//噴出パーティクル
		if (!dead)
		{
			fire->Draw(dxCommon);
		}
	}
}
