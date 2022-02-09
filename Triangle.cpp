#include "Triangle.h"

std::vector<Player*> Triangle::player;
std::vector<Ball*>Triangle::ball;
std::vector<ShootEnemy*>Triangle::sEnemy;
Triangle::Triangle()
{
	model = std::make_unique<Model>();
	object = std::make_unique< Object3d>();
}
Triangle::~Triangle()
{

}
void Triangle::SetTrianglePosition(Vector3 pos1, Vector3 pos2, Vector3 pos3)
{
	this->pos1 = pos1;
	this->pos2 = pos2;
	this->pos3 = pos3;
	model->LoadTriangle(pos1, pos2, pos3);
}

void Triangle::StaticFinalize()
{
}
void Triangle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	model->Initialize(dxCommon, textureManager, 0);

	object->Initialize(model.get());
	color = Vector3(0.0f, 0.05f, 0.0f);
	scale = Vector3(1, 1, 1);
	object->SetColor(color);
	liveFlag = true;

}

void Triangle::Update()
{
		object->Update();
	if (liveFlag)
	{
		//Player�Ǝ΂߂̕�
		for (int i = 0; i < player.size(); i++)
		{
			if (TriangleAndPoint(pos1, pos2, pos3, player[i]->GetPosition() + player[i]->GetVelocity()))
			{
				//�q�b�g��
				player[i]->SetHitBlock(true);
				//���_�̈ʒu�֌W����㉺��������
				if (pos1.y > pos2.y)
				{
					if (player[i]->GetPosition().x > pos1.x)
					{
						player[i]->SetVelocity(Repulsion(player[i]->GetVelocity(), pos1, pos2, player[i]->GetPower()));
					}
					else
					{
						player[i]->SetVelocity(Repulsion(player[i]->GetVelocity(), pos3, pos1, player[i]->GetPower()));
					}
				}
				else
				{
					if (player[i]->GetPosition().x > pos1.x)
					{
						player[i]->SetVelocity(Repulsion(player[i]->GetVelocity(), pos3, pos1, player[i]->GetPower()));
					}
					else
					{
						player[i]->SetVelocity(Repulsion(player[i]->GetVelocity(), pos1, pos2, player[i]->GetPower()));
					}
				}
				//�����W������
				player[i]->SetPowerCount(player[i]->GetPowerCount() / 2.0f);
			}
		}
		//�G�Ǝ΂ߕ�
		for (int i = 0; i < sEnemy.size(); i++)
		{
			if (TriangleAndPoint(pos1, pos2, pos3, sEnemy[i]->GetBullet()->GetPosition()))
			{
				sEnemy[i]->GetBullet()->SetLiveFlag(false);
				sEnemy[i]->GetBullet()->GetHitParticle()->SetSpawnFlag(true);
			}
		}

	}
}
void Triangle::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
//������I�u�W�F�N�g���Z�b�g
void Triangle::SetHitObject(std::vector<Player*> p, std::vector<Ball*> b, std::vector<ShootEnemy*> se)
{
	player = p;
	ball = b;
	sEnemy = se;
}