#pragma once
#include"DirectXCommon.h"
#include"TextureManager.h"
#include"Vector.h"
#include<DirectXMath.h>

#include<d3d12.h>
#include<wrl.h>
/// <summary>
/// 幾何モデル
/// </summary>
class Model
{
public:
	static const int division = 4;
	static const float radius;
	static const float prizmHeight;
	static const int planeCount = division * 2 + division * 2;
	static const int vertexCount = planeCount * 3;

public:
	//頂点データ構造体
	struct Vertex
	{
		DirectX::XMFLOAT3 pos; // xyz 座標
		DirectX::XMFLOAT3 normal; //法線ベクトル
		DirectX::XMFLOAT2 uv; // uv 座標
	};
public:
	/// <summary>
	/// 1頂点
	/// </summary>
	void PointVertex();
	/// <summary>
	/// OBJロード
	/// </summary>
	/// <param name="modelname">ファイルネーム</param>
	/// <param name="smoothing">スムース</param>
	void LoadModel(const std::string& modelname, bool smoothing);
	/// <summary>
	/// 三角形モデル
	/// </summary>
	void LoadTriangle(Vector3 pos1, Vector3 pos2, Vector3 pos3);
	/// <summary>
	/// 初期化	
	/// </summary>
	void Initialize(DirectXCommon*dxCommon, TextureManager* textureManager,UINT texNumber);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// インスタンシング描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, int instanceIndex);


	//インデックス配列の要素数を数える
	int CountIndices() { return (int)indices.size(); }

	inline const D3D12_VERTEX_BUFFER_VIEW& GetVbView() { return vbView; }
	inline const D3D12_INDEX_BUFFER_VIEW& GetIbView() { return ibView; }

	inline std::vector<Vertex> GetVertices() { return vertices; }
	//Setter
	inline void SetTexNumber(UINT i) { texNumber = i; }
private:
	//テクスチャーマネージャ
	TextureManager*textureManager = nullptr;
	//テクスチャー番号
	UINT texNumber;
	//頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>vertBuff;
	//インデックスバッファ
	Microsoft::WRL::ComPtr < ID3D12Resource>indexBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView{};

	//頂点データ配列
	 std::vector<Vertex> vertices;
	//頂点インデックス配列
	 std::vector<unsigned short> indices;
};

