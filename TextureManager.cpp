#include "TextureManager.h"
#include<cassert>

using namespace DirectX;
void TextureManager::Initialize(DirectXCommon* dxCommon)
{
	HRESULT result = S_FALSE;

	this->dxCommon = dxCommon;
	//デスクリプタヒープを作成する。
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	descHeapDesc.NumDescriptors = spriteSRVCount;
	// 生成
	result = dxCommon->GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&spriteDescHeap));
	if (FAILED(result))
	{
		assert(0);
	}
}

void TextureManager::LoadTexture(UINT texnumber, const wchar_t* filename)
{
	HRESULT result;
	//WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		filename,								//[Resources]フォルダの[texture.png]
		WIC_FLAGS_NONE,
		&metadata, scratchImg);
	if (FAILED(result)) {
		assert(0);
	}
	const Image* img = scratchImg.GetImage(0, 0, 0);//生データ抽出

	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	result = dxCommon->GetDevice()->CreateCommittedResource(    //GPUリソースの生成
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,//テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&spriteTexBuff[texnumber]));
	if (FAILED(result)) {
		assert(0);
	}

	//テクスチャバッファにデータ転送
	result = spriteTexBuff[texnumber]->WriteToSubresource(
		0,
		nullptr,//全領域へコピー
		img->pixels,       //元データアドレス
		(UINT)img->rowPitch,//1ラインサイズ
		(UINT)img->slicePitch//1枚サイズ
	);
	if (FAILED(result)) {
		assert(0);
	}

	//シェーダーリソースビュー作成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//設定構造体
	srvDesc.Format = metadata.format;//RGBA
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	dxCommon->GetDevice()->CreateShaderResourceView(spriteTexBuff[texnumber].Get(),
		&srvDesc,//テクスチャ設定情報
		CD3DX12_CPU_DESCRIPTOR_HANDLE(
			spriteDescHeap->GetCPUDescriptorHandleForHeapStart(),
			texnumber,
			dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));
}

ID3D12Resource* TextureManager::GetSpriteTexBuff(UINT texnumber)
{
	//配列オーバーフロー防止
	//assert(texnumber < spriteSRVCount);
	if (texnumber >= spriteSRVCount) {
		return nullptr;
	}
	return spriteTexBuff[texnumber].Get();
}

void TextureManager::SetDescripterHeaps(ID3D12GraphicsCommandList* cmdList)
{
	//デスクリプタヒープの配列
	ID3D12DescriptorHeap* ppHeaps[] = { spriteDescHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void TextureManager::SetShaderResourceView(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex, UINT texNumber)
{
	//SRVのサイズを取得
	UINT sizeSRV = dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	
	//デスクリプターテーブルの先頭を取得
	D3D12_GPU_DESCRIPTOR_HANDLE start = spriteDescHeap->GetGPUDescriptorHandleForHeapStart();

	//SRVのGPUハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE handle = CD3DX12_GPU_DESCRIPTOR_HANDLE(start,texNumber,sizeSRV);
	
	//シェーダリソースビューをセット
	cmdList->SetGraphicsRootDescriptorTable(rootParameterIndex,handle);
}
