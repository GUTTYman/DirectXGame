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

	//�̂̎���̃I�u�W�F�N�g
	cubeOBJ->Initialize(modelLoader->GetModel(ModelIndex::CUBE));
	cubeOBJ->SetColor(Vector3());
	cubeOBJ->SetScale(Vector3(1, 1, 1));
	//cube�p�J�E���g
	cubeCount = 0;

	//�ڂ̃I�u�W�F�N�g
	eye->Initialize(modelLoader->GetModel(EYE));
	eye->SetColor(color);
	eye->SetScale(scale);
}

void ShootEnemy::Update()
{
	if (liveFlag)
	{
#pragma region
		//�v���C���[�Ƃ̓����蔻��
		for (int i = 0; i < player.size(); i++)
		{
			//���͈͂ɓ������猂���Ă���
			if (SphereAndSphere(position, player[i]->GetPosition(), 60, player[i]->GetScale().x, player[i]->GetLiveFlag(),liveFlag))
			{
				//�e���`�悳��Ă��Ȃ����
				if (!bullet->GetLiveFlag())
				{
					//�e�̏Փ˃p�[�e�B�N�����o�Ă��Ȃ����
					if (!bullet->GetHitParticle()->GetSpawn())
					{
						//���̒e���Z�b�g
						bullet->SetVelocity(Vector3(player[i]->GetPosition() - position).normalize() * 0.8f);
						bullet->SetLiveFlag(true);
						//���ˉ����Đ�
						soundManager->PlayWave(AudioIndex::SHOOT);
					}
				}
			}
			//Player������ł��Ȃ�������
			if (!player[i]->GetDead())
			{
				//�Փ˂����e��Player�����Łi���S�j
				if (SphereAndSphere(bullet->GetPosition(), player[i]->GetPosition(), bullet->GetScale().x, player[i]->GetScale().x, player[i]->GetLiveFlag(), bullet->GetLiveFlag()))
				{
					player[i]->SetDead(true);
					bullet->SetLiveFlag(false);
					bullet->GetHitParticle()->SetSpawnFlag(true);

				}
			}
		}
		
		//�����ړ��J��Ԃ�
		velocity = Vector3(sin(a) * 0.1f, 0, 0);
		position += velocity;
		a += 0.01f;
		//�ڂ̃I�u�W�F�N�g�X�V
		eye->SetPosition(position);
		eye->SetRotation(rotation);
		eye->Update();
		//�e���`�悳��Ă��Ȃ����
		if (!bullet->GetLiveFlag())
		{
			//�|�W�V�������X�V
			bullet->SetPosition(position);
		}
		//�e�̍X�V
		bullet->Update();

		//�̂̎���̃I�u�W�F�N�gUpdate
		CubeOBJUpdate();
		//�p�[�e�B�N����Update
		fire->Update(position);
#pragma endregion
	}
}
void ShootEnemy::CubeOBJUpdate()
{
	cubeCount += 1;
	//�̂̎�����I�u�W�F�N�g����]���Ă���
	cubeOBJ->SetPosition(position);
	//ShootEnemyParticleGS�Ő���
	cubeOBJ->SetTime(cubeCount);
	cubeOBJ->Update();
}
void ShootEnemy::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		//�̂̎���̃I�u�W�F�N�g
		cubeOBJ->Draw(dxCommon->GetCommandList(),SHOOTENEMY,20);
		//�e
		bullet->Draw(dxCommon);
		//��
		eye->Draw(dxCommon->GetCommandList());
		//���o�p�[�e�B�N��
		if (!dead)
		{
			fire->Draw(dxCommon);
		}
	}
}
