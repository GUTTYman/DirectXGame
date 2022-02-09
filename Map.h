#pragma once
#include<vector>

#include"Vector.h"
class Map
{
private:
	//横の最大のマップサイズ
	static const int mapX = 87;
	//縦の最大のマップサイズ
	static const int mapY = 20;
	//マップの種類（個数）
	static const int mapCount = 6;
	
	std::vector<std::vector<int>> mapchip[mapCount];
	//一個分のサイズ（間隔）
	Vector3 chipsize;
	//現在開いてるマップ
	int nowmap;

	
	
	//ゲームオブジェクトの初期位置用
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
	//三角形の三頂点
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

	//すべてのマップの中でのバウンドオブジェクトの最大数
	int GetSpherePlantMax();
	//すべてのマップの中での下向きバウンドオブジェクトの最大数
	int GetSpherePlantDownMax();
	//すべてのマップの中での上向き連結オブジェクトの最大数
	int GetLinkObjectMax();
	//すべてのマップの中での下向き連結オブジェクトの最大数
	int GetLinkObjectDownMax();
	//すべてのマップの中でのキノコの最大数
	int GetBoundObjectMax();
	//すべてのマップの中でのシュート敵の最大数
	int GetShootEnemyMax();
	//すべてのマップの中での爆弾の最大数
	int GetBombMax();
	//すべてのマップの中での床の最大数
	int GetBlockMax();
	//すべてのマップの中での壁の最大数
	int GetWallMax();
	//すべてのマップの中でのカッターの最大数
	int GetCutterMax();
	//すべてのマップの中での増殖オブジェクトの最大数
	int GetRiseMax();
	//すべてのマップの中での増殖オブジェクトの最大数
	int GetBallMax();

	//すべてのマップの中での三角形各頂点の最大数
	int GetTriangleAMax();
	int GetTriangleBMax();
	int GetTriangleCMax();
};

