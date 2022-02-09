#include "PlayerEmitter.h"
PlayerEmitter::PlayerEmitter()
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Player());
	}
}

PlayerEmitter::~PlayerEmitter()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void PlayerEmitter::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	liveFlag = false;
	for (int i = 0; i < object.size(); ++i)
	{
		object[i]->Initialize(dxCommon, textureManager);
	}
		object[0]->SetLiveFlag(true);
}

void PlayerEmitter::Update()
{
	liveFlag = false;
	for (int i = 0; i < object.size(); ++i)
	{
		object[i]->Update();
		//��̂ł������Ă��瑱�s
		if (object[i]->GetLiveFlag())
		{
			liveFlag = true;
			if (Player::GetInput() != InputNum::LEFT)
			{
				if (i != TopPlayer())
				{
					//�ǂɓ������Ă��Ȃ���Ԃ�
					if (!object[i]->GetHitBlock())
					{
						//�����ɂ���ꍇ�͐擪��Player�ɏW�܂��Ă���
						if (!SphereAndSphere(object[TopPlayer()]->GetPosition(), object[i]->GetPosition(),
							object[i]->GetScale().x / 2, 10.0f, object[TopPlayer()]->GetLiveFlag(), object[i]->GetLiveFlag()))
						{
							//�擪�Ƃ�Direction
							Vector3 dir = object[TopPlayer()]->GetPosition() - object[i]->GetPosition();
							object[i]->SetVelocity(object[i]->GetVelocity() + dir.normalize() * 0.01f);
						}
					}
				}
			}
			//Player���m�̔���
			for (int j = 0; j < object.size(); ++j)
			{
				if (j != i)
				{
					if (!object[i]->GetHitBlock())
					{
						if (SphereAndSphere(object[i]->GetPosition(), object[j]->GetPosition(), object[i]->GetScale().x / 2, object[j]->GetScale().x / 2, object[i]->GetLiveFlag(), object[j]->GetLiveFlag()))
						{
							Vector3 direction = Vector3(object[i]->GetPosition() - object[j]->GetPosition()).normalize();
							//object[i]->SetPosition(object[i]->GetPosition() + direction);
							object[i]->SetVelocity(direction / 10);

						}
					}
				}
			}
		}
	}
	
	//���u����Ă��邩���ׂ�
	if(object[TopPlayer()]->GetVelocity().x == 0.0f &&
		abs(object[TopPlayer()]->GetVelocity().y) < 0.05f)
	{
		rest++;
	}
	else
	{
		rest = 0;
	}
}

void PlayerEmitter::Draw(DirectXCommon* dxCommon)
{
	for (int i = 0; i < object.size(); ++i)
	{
			object[i]->Draw(dxCommon);
	}
}
void PlayerEmitter::Rise(Vector3 position, DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	for (int i = 0; i < object.size(); ++i)
	{
		if (!object[i]->GetLiveFlag())
		{
			object[i]->SetLiveFlag(true);
			float rx = rand() % 100 - 50;
			float ry = rand() % 100 - 50;
			object[i]->SetPosition(position + Vector3(rx / 10.0f, ry / 10.0f, 0));
			object[i]->SetVelocity(object[TopPlayer()]->GetVelocity());
			//�v���C���[�Ƃ̃T�C�Y�w��
			float rs = rand() % 20 + 10;
			object[i]->SetScale(Vector3(rs / 10.0f, rs / 10.0f, rs / 10.0f));
			break;
		}
	}

}
void PlayerEmitter::SetPosition(Vector3 position)
{
	object[0]->SetPosition(position);
	for (int i = 1; i < object.size(); i++)
	{
		float rx = rand() % 100 - 50;
		float ry = rand() % 100 - 50;
		object[i]->SetPosition(position - Vector3(rx / 100.0f, ry / 100.0f, 0));	}
}
void PlayerEmitter::SetVelocity(Vector3 velocity)
{
	for (auto& o : object)
	{
		o->SetVelocity(velocity);
	}
}

void PlayerEmitter::PlayerReset()
{
	object[0]->SetLiveFlag(true);

	for (int i = 1; i < object.size(); ++i)
	{
		object[i]->SetLiveFlag(false);
	}

}

Vector3 PlayerEmitter::PlayerCamera()
{
	Vector3 result=Vector3();
	for (int i = 0; i < object.size(); i++)
	{
		//if (object[i]->GetLiveFlag())
		if (result.x < object[i]->GetPosition().x && object[i]->GetLiveFlag())
		{
			result = object[i]->GetPosition();
			//break;
		}
	}
	//�}�b�v���Ŏ擾
	result.x > 53.0f ? true : result.x = 53.0f;
	result.x < 208.0f ? true : result.x = 208.0;

	return result;
}

Vector3 PlayerEmitter::TopPosition()
{
	Vector3 result = Vector3();
	for (int i = 0; i < object.size(); i++)
	{
		//�擪�������Ă���
		if (result.x < object[i]->GetPosition().x&& object[i]->GetLiveFlag())
		{
			result = object[i]->GetPosition();
		}
	}

	return result;
}

int PlayerEmitter::TopPlayer()
{
	Vector3 result = object[0]->GetPosition();
	int a = 0;
	for (int i = 0; i < object.size(); i++)
	{
		//�擪�������Ă���
		//if (object[i]->GetLiveFlag())
		if (result.x < object[i]->GetPosition().x && object[i]->GetLiveFlag())
		{
			result.x = object[i]->GetPosition().x;
			a = i;
			//break;
		}
	}
	return a;
}

