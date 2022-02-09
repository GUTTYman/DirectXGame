#include "GamePlayScene.h"
GamePlayScene::~GamePlayScene()
{
	delete opening;
}
void GamePlayScene::Initialize()
{
	//GamePlayScene��p�̊J�n�����o�I�u�W�F�N�g
	opening = new Opening();
	opening->Initialize(dxCommon,textureManager);
	//�����������I�u�W�F�N�g����x�����X�V���Ă���
	opening->Update(map->GetPlayerPosition());

}
//�Q�[���v���C���̍X�V
void GamePlayScene::Update()
{

	//�J�n���̉��o�̍X�V
	opening->Update(map->GetPlayerPosition());

	//�J�n���̃t�F�[�h�C��
	if (Fade(120.0f, count))
	{
		//Player����҂��̊Ԃ�UI
		if (opening->isWait())
		{
			sceneObject->ButtonUpdate(map->GetPlayerPosition() + Vector3(0, 5, 0), Vector3(1.5f,0.4f,1.5f));
		}
		//�J�n���̉��o�I��������
		if (opening->GetStep()==OpenStep::OFF|| opening->GetStep() == OpenStep::SPAWN)
		{
			//�v���C���[
			player->Update();
			//�V�[���I�u�W�F�N�g�iUI�Ȃǁj
			sceneObject->PlayUpdate(player->TopPosition(), false);
			//Player���S�����񂾂�V�[���؂�ւ�
			if (!player->GetLiveFlag())
			{
				scene = GAMEOVER_SCENE;
			}
		}
		else
		{
			//�������т���
			player->GetPleyer()[player->TopPlayer()]->SetVelocity(Vector3(0.05f, 1, 0));
		}
		//�}�b�v�؂�ւ�
		ChangeMap();
	}
	else
	{
		count++;
	}
#pragma region �e�I�u�W�F�N�g��Update�Ăяo��
	//ShootEnemy
	ShootEnemy::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetShootEnemy().size(); i++)
	{
		shootEnemy[i]->Update();
	}
	//�̂��I�u�W�F�N�g
	LinkObject::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetLinkObject().size(); i++)
	{
		linkObject[i]->Update();
	}
	//�������̂��I�u�W�F�N�g
	LinkObject::SetPlayer(player->GetPleyer());
	LinkObject::SetShootEnemy(shootEnemy);
	for (int i = 0; i < map->GetLinkObjectDown().size(); i++)
	{
		linkObjectD[i]->Update();
	}
	//�L�m�R�I�u�W�F�N�g
	BoundObject::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetBoundObject().size(); i++)
	{
		boundObject[i]->Update();
	}
	//���̐A���I�u�W�F�N�g
	SpherePlant::SetPlayer(player->GetPleyer());
	SpherePlant::SetShootEnemy(shootEnemy);
	for (int i = 0; i < map->GetSpherePlant().size(); i++)
	{
		spherePlant[i]->Update();
	}
	//���������̐A���I�u�W�F�N�g
	for (int i = 0; i < map->GetSpherePlantDown().size(); i++)
	{
		spherePlantD[i]->Update();
	}
	//�u���b�N�I�u�W�F�N�g
	TileBlock::SetHitObject(player->GetPleyer(), ball, shootEnemy);
	for (int i = 0; i < map->GetBlock().size(); i++)
	{
		block[i]->Update();
	}
	//��
	Wall::SetHitObject(player->GetPleyer(),ball,shootEnemy);
	for (int i = 0; i < map->GetWall().size(); i++)
	{
		wall[i]->Update();
	}
	//�{���I�u�W�F�N�g
	Bomb::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetBomb().size(); i++)
	{
		bomb[i]->Update();
	}
	//������@�I�u�W�F�N�g
	Cutter::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetCutter().size(); i++)
	{
		cutter[i]->Update();
	}
	//���B�I�u�W�F�N�g
	RiseObject::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetRise().size(); i++)
	{
		rise[i]->Update();
		rise[i]->PlayerRise(player, 10, dxCommon, textureManager, 0);
	}
	
	//�O�p�`�I�u�W�F�N�g
	Triangle::SetHitObject(player->GetPleyer(), ball, shootEnemy);
	for (int i = 0; i < map->GetTriangleA().size(); i++)
	{
		triangle[i]->Update();
	}
	//�S�[��
	Goal::SetPlayer(player->GetPleyer());
	goal->Update();
	//�{�[��
	Ball::SetPlayer(player->GetPleyer());
	for (int i = 0; i < map->GetBall().size(); i++)
	{
		ball[i]->Update();
	}

	//�w�i
	back->Update();
	//�}�b�v���ƂɊŔ̃e�N�X�`���؂�ւ�
	switch (mapnum)
	{
	case 0:
		sceneObject->SetBoardTexture(9);
		break;
	case 1:
		sceneObject->SetBoardTexture(1);
		break;
	case 2:
		sceneObject->SetBoardTexture(17);
		break;
	case 3:
		sceneObject->SetBoardTexture(2);
		break;
	case 4:
		sceneObject->SetBoardTexture(18);
		break;
	case 5:
		sceneObject->SetBoardTexture(19);
		break;
	}
	//��������̊Ŕ�
	sceneObject->BoradUpdate(Vector3(50, 0, 0), player->GetPleyer());

#pragma region �J��������
	//�J�����V�F�C�N�̒l���Z
	Vector3 cameraShake = Vector3();
	for (int i = 0; i < ball.size(); i++)
	{
		cameraShake += ball[i]->GetCameraShake();
	}
	//�J�n���o���̃J�������o
	if (opening->GetStep() == OpenStep::OFF || opening->GetStep() == OpenStep::SPAWN)
	{
		//Player�������Ă���ԃJ�������ǂ�
		if (player->GetLiveFlag())
		{
			camera->SetEye(Vector3(player->PlayerCamera().x, -28.0f + cameraShake.y, -65.0f));
			camera->SetTarget(Vector3(player->PlayerCamera().x, -28.0f + cameraShake.y, 0.0f));
		}
	}
	else
	{
		//�J�n���̃J����
		OpeningUpdate();
	}
#pragma endregion


#pragma endregion
}


void GamePlayScene::OpeningUpdate()
{
	//�J�n���J�����������痣��Ă���
	camera->SetEye(opening->GetCameraEye());
	camera->SetTarget(opening->GetCameraTarget());
}
void GamePlayScene::ChangeMap()
{
	//�S�[��������
	if (goal->GetGoalFlag())
	{
		if (mapnum == map->GetMapCount() - 1)
		{
			scene = CLEAR_SCENE;
			//�N���A�������Z�b�g
			opening->Reset();
			select->ResetClear();

		}
		else
		{
			count = 0;
			//�X�e�[�W�I���Ɉڂ�
			scene = SELECT_SCENE;
			//�X�e�[�W�J��
			select->SetNext(true);
		}
		//�}�b�v��ǂݍ��݃S�[���t���O��false�ɂ���
		MapLoad();
		goal->SetGoalFlag(false);
	}
}
//�Q�[���v���C���̕`��
void GamePlayScene::Draw()
{
#pragma region Play���̕`��
	
	for (int i = 0; i < map->GetLinkObject().size(); i++)
	{
		linkObject[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetLinkObjectDown().size(); i++)
	{
		linkObjectD[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetBoundObject().size(); i++)
	{
		boundObject[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetSpherePlant().size(); i++)
	{
		spherePlant[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetSpherePlantDown().size(); i++)
	{
		spherePlantD[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetBlock().size(); i++)
	{
		block[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetWall().size(); i++)
	{
		wall[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetBomb().size(); i++)
	{
		bomb[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetCutter().size(); i++)
	{
		cutter[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetRise().size(); i++)
	{
		rise[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetShootEnemy().size(); i++)
	{
		shootEnemy[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetTriangleA().size(); i++)
	{
		triangle[i]->Draw(dxCommon);
	}
	for (int i = 0; i < map->GetBall().size(); i++)
	{
		ball[i]->Draw(dxCommon);
	}
	//�S�[��
	goal->Draw(dxCommon);
	//�w�i
	back->Draw(dxCommon);
	//��������̊Ŕ�
	sceneObject->BroadDraw(dxCommon);

	//�~�܂��Ă���Ԃ���UI�\��
	if (player->GetRestTime() > 60)
	{
		sceneObject->PlayDraw(dxCommon);
	}
	//�������ꂽ��`�悷��
	if (opening->GetStep() == OpenStep::OFF || opening->GetStep() == OpenStep::SPAWN)
	{
		player->Draw(dxCommon);
	}
	//Player����҂��̊Ԃ�UI
	if (opening->isWait())
	{
		sceneObject->ButtonDraw(dxCommon);
	}
	//�J�n���̗��I�u�W�F�N�g
	opening->Draw(dxCommon);
#pragma endregion
}

