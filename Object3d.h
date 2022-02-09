#pragma once

#include<d3d12.h>
#include<d3dx12.h>
#include<wrl.h>

#include"DirectXCommon.h"
#include"Model.h"
#include"Camera.h"
#include"Vector.h"
#include"Light.h"

#include <DirectXMath.h>

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

//オブジェクトのモード
enum OBJtype
{
	DEFAULT,
	NORMALCOLOR,
};

class Object3d
{
public:	//定数
	static const int maxObjectCount = 3000;//3Dオブジェクトの最大個数

public:   //エイリアス
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//共通データ
	class Common
	{
		friend class Object3d;
	public:
		/// <summary>
		/// グラフィクスパイプライン初期化
		/// </summary>
		/// <param name="dxCommon">DirectX基盤</param>
		void BasicInitGraphicsPiepeline(DirectXCommon* dxCommon);
		/// <summary>
		/// カメラ初期化
		/// </summary>
		void InitializeCamera();
	private:
		//DirectX12基盤
		DirectXCommon* dxCommon = nullptr;
		//ルートシグネチャ
		ComPtr < ID3D12RootSignature> rootsignature;
		//パイプラインステート
		ComPtr < ID3D12PipelineState> pipelinestate[2];
		//カメラ
		Camera* camera = nullptr;
		//ライト
		Light* light = nullptr;
	};

	//定数バッファ用データ構造体
	struct ConstBufferData {

		XMFLOAT4 color;// 色 (RGBA)
		XMFLOAT3 normalLength;
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
		float dummy;
		XMFLOAT3 randomVertex;	//オブジェクトをびりびり振動させる

	};
public://静的メンバ関数
	/// <summary>
	/// 静的メンバの初期化
	/// </summary>
	static void StaticInitialize(DirectXCommon* dxCommon, Camera* camera);
	/// <summary>
	/// デスクリプターヒープリセット
	/// </summary>
	static void RestDescriptorHeap();

private://静的メンバ変数
	static std::unique_ptr<Common> common;

public://メンバ関数
	Object3d();

	~Object3d();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	//Getter
	inline const Vector3& GetPosition() { return position; }
	inline const Vector3& GetScale() { return scale; }
	inline const Vector3& GetRotation() { return rotation; }
	inline const Vector3& GetNormalLength() { return normalLength; }
	//Setter
	inline void SetColor(Vector3 c) { color = c; }
	inline void SetNormalLength(Vector3 v) { normalLength = v; }
	inline void SetRandomVertex(Vector3 v){randomVertex = v; }
	inline void SetPosition(Vector3 position) { this->position = position; }
	inline void SetScale(Vector3 scale) { this->scale = scale; }
	inline void SetRotation(Vector3 rotation) { this->rotation = rotation; }
	inline static void SetLight(Light* light) { common->light = light; }
	inline void SetOBJType(OBJtype objtype) { type = objtype; }

private:
	ComPtr<ID3D12Resource> constBuff;
	//トランスフォーム
	Vector3 scale = Vector3(1,1,1);
	Vector3 rotation = Vector3();
	Vector3 position = Vector3();
	Vector3 normalLength = Vector3();	//ジオメトリシェーダー用法線の飛ばす距離
	Vector3 color = Vector3(1,1,1);
	XMMATRIX matWorld;			//ローカルワールド変換行列
	Vector3 randomVertex = Vector3();	//オブジェクトをびりびり振動させる
	Object3d* parent = nullptr;	//親オブジェクト
	//モデルデータ
	Model* model = nullptr;
	//シェーダーの種類指定
	OBJtype type = DEFAULT;

};

