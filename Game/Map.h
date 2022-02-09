#pragma once
#include<vector>

#include"Vector.h"
class Map
{
private:
	//���̍ő�̃}�b�v�T�C�Y
	static const int mapX = 87;
	//�c�̍ő�̃}�b�v�T�C�Y
	static const int mapY = 20;
	//�}�b�v�̎�ށi���j
	static const int mapCount = 6;
	
	std::vector<std::vector<int>> mapchip[mapCount];
	//����̃T�C�Y�i�Ԋu�j
	Vector3 chipsize;
	//���݊J���Ă�}�b�v
	int nowmap;

	
	
	//�Q�[���I�u�W�F�N�g�̏����ʒu�p
	Vector3 player[mapCount];
	Vector3 goal[mapCount];
	std::vector<Vector3> ball[mapCount];
	std::vector<Vector3> shootEnemy[mapCount];
	std::vector<Vector3> spherePlant[mapCount];
	std::vector<Vector3> spherePlantDown[mapCount];
	std::vector<Vector3> linkObject[mapCount];
	std::vector<Vector3> linkObjectDown[mapCount];
	std::vector<Vector3> boundObject[mapCount];
	std::vector<Vector3> block[mapCount];
	std::vector<Vector3> wall[mapCount];
	std::vector<Vector3> bomb[mapCount];
	std::vector<Vector3> cutter[mapCount];
	std::vector<Vector3> rise[mapCount];
	//�O�p�`�̎O���_
	std::vector<Vector3> triangleA[mapCount];
	std::vector<Vector3> triangleB[mapCount];
	std::vector<Vector3> triangleC[mapCount];
public:

	void Initialize();

	inline void SetNowmap(int map)
	{
		nowmap = map;
	}


	//Getter
	inline int GetMapCount() { return mapCount; }

	Vector3 GetPlayerPosition();
	Vector3 GetGoalPosition();
	std::vector<Vector3> GetBall();
	std::vector<Vector3> GetShootEnemy();
	std::vector<Vector3> GetSpherePlant();
	std::vector<Vector3> GetSpherePlantDown();
	std::vector<Vector3> GetLinkObject();
	std::vector<Vector3> GetLinkObjectDown();
	std::vector<Vector3> GetBoundObject();
	std::vector<Vector3> GetBlock();
	std::vector<Vector3> GetBomb();
	std::vector<Vector3> GetWall();
	std::vector<Vector3> GetCutter();
	std::vector<Vector3> GetRise();

	std::vector<Vector3> GetTriangleA();
	std::vector<Vector3> GetTriangleB();
	std::vector<Vector3> GetTriangleC();

	//���ׂẴ}�b�v�̒��ł̃o�E���h�I�u�W�F�N�g�̍ő吔
	int GetSpherePlantMax();
	//���ׂẴ}�b�v�̒��ł̉������o�E���h�I�u�W�F�N�g�̍ő吔
	int GetSpherePlantDownMax();
	//���ׂẴ}�b�v�̒��ł̏�����A���I�u�W�F�N�g�̍ő吔
	int GetLinkObjectMax();
	//���ׂẴ}�b�v�̒��ł̉������A���I�u�W�F�N�g�̍ő吔
	int GetLinkObjectDownMax();
	//���ׂẴ}�b�v�̒��ł̃L�m�R�̍ő吔
	int GetBoundObjectMax();
	//���ׂẴ}�b�v�̒��ł̃V���[�g�G�̍ő吔
	int GetShootEnemyMax();
	//���ׂẴ}�b�v�̒��ł̔��e�̍ő吔
	int GetBombMax();
	//���ׂẴ}�b�v�̒��ł̏��̍ő吔
	int GetBlockMax();
	//���ׂẴ}�b�v�̒��ł̕ǂ̍ő吔
	int GetWallMax();
	//���ׂẴ}�b�v�̒��ł̃J�b�^�[�̍ő吔
	int GetCutterMax();
	//���ׂẴ}�b�v�̒��ł̑��B�I�u�W�F�N�g�̍ő吔
	int GetRiseMax();
	//���ׂẴ}�b�v�̒��ł̑��B�I�u�W�F�N�g�̍ő吔
	int GetBallMax();

	//���ׂẴ}�b�v�̒��ł̎O�p�`�e���_�̍ő吔
	int GetTriangleAMax();
	int GetTriangleBMax();
	int GetTriangleCMax();
};

