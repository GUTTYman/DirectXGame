#pragma once
#include<d3d12.h>
#include<d3dx12.h>
#include<wrl.h>
#include<DirectXMath.h>

#include"TextureManager.h"
#include"DirectXCommon.h"

/// <summary>
/// スプライト
/// </summary>
class Sprite
{
public:   //エイリアス
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	class  Common
	{
		friend class Sprite;
	public:
		void InitializeGraphicsPipeline();

	protected:
		DirectXCommon* dxCommon = nullptr;
		TextureManager* textureManager = nullptr;
		ComPtr<ID3D12RootSignature>rootSignature;
		ComPtr<ID3D12PipelineState>pipelineState;
		XMMATRIX matProjection{};//射影変換
	};

	struct VertexPosUv
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};
	//定数バッファ用データ構造体
	struct ConstBufferData {
		DirectX::XMFLOAT4 color;// 色 (RGBA)
		DirectX::XMMATRIX mat;	//３D変換行列
	};

public:	//静的メンバ関数
	/// <summary>
	/// 静的メンバの初期化
	/// </summary>
	static void StaticInitialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	/// <summary>
	/// グラフィックスパイプラインのセット
	/// </summary>
	static void SetPiepelineState(ID3D12GraphicsCommandList* cmdList);

protected:	//静的メンバ変数
	static std::unique_ptr<Common> common;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="texNumber"></param>
	/// <param name="position"></param>
	/// <param name="size"></param>
	/// <param name="color"></param>
	/// <param name="anchorpoint"></param>
	/// <param name="isFlipX"></param>
	/// <param name="isFlipY"></param>
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="texNumber"></param>
	void Initialize(UINT texNumber);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// 頂点バッファにデータ転送
	/// </summary>
	void TransferVertices();
	/// <summary>
	/// サイズ設定
	/// </summary>
	void SetSize(float width, float height);
	/// <summary>
	/// テクスチャの範囲指定
	/// </summary>
	/// <param name="anchorpoint"></param>
	void TextureRange(float tex_x, float tex_y, float tex_width, float tex_height);
public:
	DirectXCommon* GetdxCommon() { return common->dxCommon; }
	ComPtr<ID3D12PipelineState> GetPipielineState() { return common->pipelineState; }

protected:	//メンバ変数
	ComPtr<ID3D12Resource> vertBuff;//頂点バッファ
	ComPtr<ID3D12Resource> constBuff;//定数バッファ
	D3D12_VERTEX_BUFFER_VIEW vbView{};//頂点バッファビュー
	float rotation = 0.0f;//Z軸回転
	XMFLOAT3 position{};//座標
	XMMATRIX matWorld{};//ワールド行列
	XMFLOAT4 color = { 1,1,1,1 };//色
	UINT texNumber = 0;//テクスチャ番号
	XMFLOAT2 anchorpoint = { 0.5f,0.5f };//基準点
	float width=100.0f;
	float height=100.0f;
	bool isFlipX = false;//左右反転
	bool isFlipY = false;//上下反転
	float tex_x = 0.0f;//テクスチャ左上　x座標
	float tex_y = 0.0f;//テクスチャ左上　y座標
	float tex_width = 100.0f;//テクスチャ横幅
	float tex_height = 100.0f;//テクスチャ縦幅
};

