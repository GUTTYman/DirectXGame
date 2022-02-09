#include "LinkObject.h"

std::vector<Player*> LinkObject::player;
std::vector<ShootEnemy*> LinkObject::sEnemies;

LinkObject::LinkObject()
{
	object = std::make_unique< Object3d>();
}
LinkObject::~LinkObject()
{
	
}

void LinkObject::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{

	object->Initialize(modelLoader->GetModel(CUBE));

	scale = Vector3(1, 1, 1);
	accel = Vector3(0.0f, 0.2f, 0.0f);
	color = Vector3();
	target = Vector3(0, 0, 0);
	reverse = 1;
	liveFlag = true;

}

void LinkObject::Update()
{
	if (liveFlag)
	{
		object->Update();
#pragma region  LinkObject‘€ì
		//ŒÅ‚³
		float stiffness = 0.3f;
		//Œ¸Š
		float damping = 0.6f;
		//d‚³
		float mass = 1.0f;
		//d—Í
		float gravity = 0.3f;

		//‚Î‚Ë‚ÌŒvZ
		Vector3 force = stiffness * (target - position);
		force.y -= gravity*reverse;
		accel = force / mass;
		velocity = damping * (velocity + accel);
		//ˆÚ“®—Ê‰ÁZ
		position += velocity;
		//Player‚Ì“–‚½‚è”»’è
		for (int i = 0; i < player.size(); i++)
		{
			if (player[i]->GetLiveFlag())
			{
				if (SphereAndSphere(position, player[i]->GetPosition(), scale.x, player[i]->GetScale().x, player[i]->GetLiveFlag(), liveFlag))
				{
					velocity = player[i]->GetVelocity();
				}
			}
		}
		//‘_Œ‚“G‚Ì“–‚½‚è”»’è
		for (int i = 0; i < sEnemies.size(); i++)
		{
			if (sEnemies[i]->GetLiveFlag())
			{
				if (SphereAndSphere(position, sEnemies[i]->GetPosition(), scale.x, sEnemies[i]->GetScale().x * 3))
				{
					velocity = sEnemies[i]->GetVelocity();
				}
			}
		}

#pragma endregion

		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);
		object->SetColor(color);
	} 
}
void LinkObject::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}

void LinkObject::SetPlayer(std::vector<Player*> p)
{
	player = p;
}

void LinkObject::SetShootEnemy(std::vector<ShootEnemy*> e)
{
	sEnemies = e;
}

void LinkObject::SetTarget(Vector3 aPos)
{
	target = aPos;
}
void LinkObject::IsReverse(bool r)
{
	if (r == true)
	{
		reverse = -1;
	}
	else
	{
		reverse = 1;
	}
}
