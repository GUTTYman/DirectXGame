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
enum ParticleMode
{
	POINTPARTICLE,
	SHOOTENEMY,
	HITPARTICLE,
};
class GPUParticle
{
public:	//定数
	static const int maxObjectCount = 3000;//3Dオブジェクトの最大個数

public:   //エイリアス
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	//using XMFLOAT2 = DirectX::XMFLOAT2;
	//using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//共通データ
	class Common
	{
		friend class GPUParticle;
	public:
		/// <summary>
		/// グラフィクスパイプライン初期化
		/// </summary>
		/// <param name="dxCommon">DirectX基盤</param>
		void InitializeGraphicsPipeline(DirectXCommon* dxCommon);
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
		ComPtr < ID3D12PipelineState> pipelinestate[3];
		//カメラ
		Camera* camera = nullptr;
	};

	//定数バッファ用データ構造体
	struct ConstBufferData {

		XMFLOAT4 color;// 色 (RGBA)
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
		int time;
		int maxCount;
	};

public://静的メンバ関数
	/// <summary>
	/// 静的メンバの初期化
	/// </summary>
	static void StaticInitialize(DirectXCommon* dxCommon, Camera* camera);
	/// <summary>
	/// デスクリプターヒープリセット
	/// </summary>
	static void ResetDescriptorHeap();

private://静的メンバ変数
	static std::unique_ptr < Common> common;

public://メンバ関数
	GPUParticle();

	~GPUParticle();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// モデル描画
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList, ParticleMode mode, int instanceIndex);
	/// <summary>
	/// 頂点のみ描画
	/// </summary>
	void PointDraw(ID3D12GraphicsCommandList* cmdList, ParticleMode mode, int instanceIndex);

	//Getter
	inline const Vector3& GetPosition() { return position; }
	inline const Vector3& GetScale() { return scale; }
	inline const Vector3& GetRotation() { return rotation; }
	//Setter
	inline void SetColor(Vector3 c) { color = c; }
	inline void SetPosition(Vector3 position) { this->position = position; }
	inline void SetScale(Vector3 scale) { this->scale = scale; }
	inline void SetRotation(Vector3 rotation) { this->rotation = rotation; }
	inline void SetTime(int time) { this->time = time; }
	inline void SetMaxCount(int a) { maxCount = a; }

private:
	ComPtr<ID3D12Resource> constBuff;
	//トランスフォーム
	Vector3 scale = { 1,1,1 };
	Vector3 rotation = { 0,0,0 };
	Vector3 position = { 0,0,0 };
	Vector3 color = { 1,1,1 };
	int time = 0;
	int maxCount = 0;

	XMMATRIX matWorld;			//ローカルワールド変換行列


	GPUParticle* parent = nullptr;	//親オブジェクト
	//モデルデータ
	Model* model = nullptr;
};

