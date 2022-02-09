#pragma once

#include"DirectXCommon.h"

#include<d3d12.h> 
#include<d3dx12.h>
#include<wrl.h>
#include<DirectXTex.h>


class TextureManager
{
public:   //エイリアス
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:	  //定数
	static const int spriteSRVCount = 512;//テクスチャの最大枚数
public:		//メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dxCommon"></param>
	void Initialize(DirectXCommon*dxCommon);
	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="texnumber">テクスチャ番号</param>
	/// <param name="filename">テクスチャファイル名</param>
	void LoadTexture(UINT texnumber, const wchar_t* filename);
	/// <summary>
	/// テクスチャバッファ取得
	/// </summary>
	ID3D12Resource* GetSpriteTexBuff(UINT texnumber);
	/// <summary>
	/// デスクリプターヒープをセット(グラフィックスコマンド)
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void SetDescripterHeaps(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// SRVをセット（グラフィックスコマンド）
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	/// <param name="rootParameterIndex">ルートパラメーターの番号</param>
	/// <param name="texNumber">テクスチャ番号</param>
	void SetShaderResourceView(ID3D12GraphicsCommandList* cmdList,UINT rootParameterIndex,UINT texNumber);
	//getter
	ID3D12DescriptorHeap* GetSpriteDescHeap() { return spriteDescHeap.Get(); }
private:  //メンバ変数
	ComPtr<ID3D12DescriptorHeap> spriteDescHeap;
	ComPtr<ID3D12Resource> spriteTexBuff[spriteSRVCount];
	DirectXCommon* dxCommon = nullptr;
};

