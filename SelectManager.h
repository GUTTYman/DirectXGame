#pragma once
#include <DirectXMath.h>
#include "Object3d.h"
#include"Select.h"
//セレクトシーンのオブジェクトマネージャー＆セレクトシーンの演出管理
class SelectManager
{
private:
	int size;			//ステージ数
	int radius;			//オブジェクト配置の半径
	float division;		//オブジェクト配置の間隔
	float angle;		//加算された角度
	int lerpCount;		//回転のカウント
	int b;				//加算される回数
	int j;				//ピックアップされたオブジェクトの要素番号
	int Enter;			//決定キー
	bool next;			//ステージが解放される演出フラグ
	int nextCount;		//演出のカウント
	float rgbshift;		//ポストエフェクト用変数
	std::vector<Select*> object;

public:
	SelectManager();
	~SelectManager();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	void Update();
	void BoxRotation();				//ステージ選択の回転
	void SelectContorol();			//選択画面の操作と音再生
	void Draw(DirectXCommon* dxCommon);

	//Geter
	int GetMapSelect();
	inline int GetEnter() { return Enter; }
	inline float GetRGBShift() { return rgbshift; }
	inline std::vector<Select*>GetSelect() { return object; }
	//Seter
	void SetNext(bool b);
	void ResetClear();
};

