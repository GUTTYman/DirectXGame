#include "TileBlock.h"

std::vector<Player*> TileBlock::player;
std::vector<Ball*> TileBlock::ball;
std::vector<ShootEnemy*>TileBlock::sEnemy;


TileBlock::TileBlock()
{
	object = std::make_unique< Object3d>();
}
TileBlock::~TileBlock()
{
}

void TileBlock::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{

	object->Initialize(modelLoader->GetModel(CUBE));
	position = Vector3();
	color = Vector3(0.0f,0.05f,0.0f);
	scale = Vector3(77, 8, 3);
	object->SetColor(color);
	object->SetScale(scale);
	liveFlag = true;
}

void TileBlock::Update()
{
	if (liveFlag)
	{
		object->Update();
#pragma region  Block����
		//Player
		for (int i = 0; i < player.size(); i++)
		{
			if (RectangleAndSphere2D(position - scale / 2, position + scale / 2, player[i]->GetPosition() + player[i]->GetVelocity(), player[i]->GetScale().z))
			{
				player[i]->SetHitBlock(true);
				if (player[i]->GetVelocity().y < -0.03f)
				{
					//���ɑ΂��钵�˕Ԃ茸��
					player[i]->SetVelocity(Vector3(player[i]->GetVelocity().x / 1.5f, -player[i]->GetVelocity().y / 9.0f, player[i]->GetVelocity().z));
				}
				else if (player[i]->GetPosition().y < position.y)	//�V��Ȃ�
				{
					//�߂荞�񂾕������Ԃ��Ă��甽��������
					player[i]->SetPosition(Vector3(player[i]->GetPosition().x , player[i]->GetPosition().y - player[i]->GetVelocity().y, 0.0f));
					player[i]->SetVelocity(Vector3(player[i]->GetVelocity().x, -player[i]->GetVelocity().y, player[i]->GetVelocity().z));
				}
				else
				{
					player[i]->SetVelocity(Vector3(player[i]->GetVelocity().x, 0, 0));
					//���삵�ĂȂ���
					if (Player::GetInput() == NONE)
					{
						player[i]->SetVelocity(Vector3());
					}
				}
			}
		}
		//Ball
		for (int i = 0; i < ball.size(); i++)
		{
			if (RectangleAndSphere2D(position - scale / 2, position + scale / 2, ball[i]->GetPosition() + ball[i]->GetVelocity(), ball[i]->GetScale().z))
			{
				//�o�E���h
				ball[i]->SetVelocity(Vector3(ball[i]->GetVelocity().x, -ball[i]->GetVelocity().y, ball[i]->GetVelocity().z));
				ball[i]->SetHitBlock(2);
			}
		}
		//�_���G
		for (int i = 0; i < sEnemy.size(); i++)
		{
			if (RectangleAndSphere2D(position - scale / 2, position + scale / 2, sEnemy[i]->GetBullet()->GetPosition(), sEnemy[i]->GetBullet()->GetScale().x))
			{
				sEnemy[i]->GetBullet()->SetLiveFlag(false);
				sEnemy[i]->GetBullet()->GetHitParticle()->SetSpawnFlag(true);
			}
		}

#pragma endregion
		object->SetPosition(position);
		object->SetRotation(rotation);
	}
}
void TileBlock::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
//������I�u�W�F�N�g���Z�b�g
void TileBlock::SetHitObject(std::vector<Player*> p, std::vector<Ball*> b, std::vector<ShootEnemy*> se)
{
	player = p;
	ball = b;
	sEnemy = se;
}