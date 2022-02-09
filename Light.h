#pragma once
#include <DirectXMath.h>
#include "DirectXCommon.h"

class Light
{
private:

	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	struct ConstBufferData
	{
		XMVECTOR lightv;
		XMFLOAT3 lightcolor;
	};

private:
	static ID3D12Device* device;
	ComPtr<ID3D12Resource>constBuff;
	XMVECTOR lightdir = { 1,0,0,0 };
	XMFLOAT3 lightcolor = { 1,1,1 };
	bool dirty = false;
public:

	static void StaticInitialize(ID3D12Device*device);

	void Initialize();

	void TransferConstBuffer();

	void SetLightDir(const XMVECTOR&lightdir);

	void SetLightColor(const XMFLOAT3&lightcolor);

	void Update();

	void Draw(ID3D12GraphicsCommandList*cmdList, UINT rootParameterIndex);

	static std::unique_ptr < Light> Create();
};

