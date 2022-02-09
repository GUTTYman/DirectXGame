#include "Sprite.h"

#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

std::unique_ptr<Sprite::Common> Sprite::common;

void Sprite::StaticInitialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	common = std::make_unique < Common>();
	common->dxCommon = dxCommon;
	common->textureManager = textureManager;

	//グラフィックスパイプライン生成
	common->InitializeGraphicsPipeline();

	// 射影行列計算
	common->matProjection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,WinApp::window_width,
		WinApp::window_height,0.0f,
		0.0f, 1.0f);
}

void Sprite::SetPiepelineState(ID3D12GraphicsCommandList* cmdList)
{
	//パイプラインステートの設定
	cmdList->SetPipelineState(common->pipelineState.Get());
	//ルートシグネチャの設定
	cmdList->SetGraphicsRootSignature(common->rootSignature.Get());
	//プリミティブ形状を設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

Sprite::Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	this->position = XMFLOAT3(position.x, position.y,0);
	//this->size = size;
	this->anchorpoint = anchorpoint;
	this->matWorld = XMMatrixIdentity();
	this->color = color;
	this->texNumber = texNumber;
	this->isFlipX = isFlipX;
	this->isFlipY = isFlipY;
	//this->texSize = size;
}

void Sprite::Initialize(UINT texNumber)
{
	HRESULT result = S_FALSE;
	
	this->texNumber = texNumber;

	if (common->textureManager->GetSpriteTexBuff(texNumber))
	{
		D3D12_RESOURCE_DESC resDesc = common->textureManager->GetSpriteTexBuff(texNumber)->GetDesc();

		width = (float)resDesc.Width;
		height = (float)resDesc.Height;

		tex_width = (float)resDesc.Width;
		tex_height = (float)resDesc.Height;

	}

	//頂点バッファ生成
	result = common->dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv)*4),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertBuff));
	if (FAILED(result)) {
		assert(0);
	}

	TransferVertices();

	////バッファへのデータ転送
	//VertexPosUv* vertMap = nullptr;
	//result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	//memcpy(vertMap, vertices, sizeof(vertices));
	//vertBuff->Unmap(0, nullptr);


	//頂点バッファビューの作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeof(VertexPosUv)*4;
	vbView.StrideInBytes = sizeof(VertexPosUv);

	//定数バッファの生成
	result = common->dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff));
	if (FAILED(result)) {
		assert(0);
	}

	//定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->color = color;//色指定
		constMap->mat = common->matProjection;
		constBuff->Unmap(0, nullptr);
	}
}

void Sprite::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//ワールド行列の更新
	matWorld = XMMatrixIdentity();
	matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));
	matWorld *= XMMatrixTranslation(position.x, position.y, position.z);
	//matWorld*= 
	//行列の転送
	ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->mat = matWorld * common->matProjection;//行列の合成
	constBuff->Unmap(0, nullptr);


	//頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//定数バッファをセット
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());


	//デスクリプタヒープの配列
	common->textureManager->SetDescripterHeaps(cmdList);
	//シェーダリソースビューをセット
	common->textureManager->SetShaderResourceView(cmdList, 1, texNumber);

	//描画コマンド
	cmdList->DrawInstanced(4, 1, 0, 0);
}

void Sprite::TransferVertices()
{
	HRESULT result;
		//頂点データ
		VertexPosUv vertices[] = {
			//x      y      z       u     v
			{{  0.0f,100.0f,0.0f},{0.0f,1.0f}},//左下
			{{  0.0f,  0.0f,0.0f},{0.0f,0.0f}},//左上
			{{100.0f,100.0f,0.0f},{1.0f,1.0f}},//右下
			{{100.0f,  0.0f,0.0f},{1.0f,0.0f}},//右上
		};

		//左右上下座標の計算
		enum { LB, LT, RB, RT };

		float left = (0.0f - anchorpoint.x) * width;
		float right = (1.0f - anchorpoint.x) * width;
		float top = (0.0f - anchorpoint.y) * height;
		float botton = (1.0f - anchorpoint.y) * height;

		//反転の反映
		if (isFlipX)
		{//左右入れ替え
			left = -left;
			right = -right;
		}
		if (isFlipY)
		{//上下入れ替え
			top = -top;
			botton = -botton;
		}

		//頂点データ配列に座標セット
		vertices[LB].pos = { left,			botton,			0.0f };	//左下
		vertices[LT].pos = { left,			top,				0.0f };	//	左上
		vertices[RB].pos = { right,		 botton,		0.0f };	//右下
		vertices[RT].pos = { right,		top,				0.0f };	//右上

		//テクスチャ情報取得
		if (common->textureManager->GetSpriteTexBuff(texNumber))
		{
			D3D12_RESOURCE_DESC resDesc = common->textureManager->GetSpriteTexBuff(texNumber)->GetDesc();

			if (tex_width == 0 && tex_height == 0)
			{
				tex_width = resDesc.Width;
				tex_height = resDesc.Height;
			}

			float tex_left = tex_x / resDesc.Width;
			float tex_right = (tex_x + tex_width) / resDesc.Width;
			float tex_top = tex_y / resDesc.Height;
			float tex_botton = (tex_y + tex_height) / resDesc.Height;

			vertices[LB].uv = { tex_left,tex_botton };//左下
			vertices[LT].uv = { tex_left,tex_top };//左上
			vertices[RB].uv = { tex_right,tex_botton };//右下
			vertices[RT].uv = { tex_right,tex_top };//右上
		}

		//頂点バッファへのデータ転送
		VertexPosUv* vertMap = nullptr;
		result = vertBuff->Map(0, nullptr, (void**)&vertMap);
		memcpy(vertMap, vertices, sizeof(vertices));
		vertBuff->Unmap(0, nullptr);
}

void Sprite::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Sprite::TextureRange(float tex_x, float tex_y, float tex_width, float tex_height)
{
	tex_x = tex_x;
	tex_y = tex_y;

	tex_width = tex_width;
	tex_height = tex_height;

	width = tex_width;
	height = tex_height;

}

void Sprite::Common::InitializeGraphicsPipeline()
{

	HRESULT result;
	ComPtr<ID3DBlob> vsBlob;//頂点シェーダーオブジェクト
	ComPtr<ID3DBlob> psBlob;//ピクセルシェーダーオブジェクト
	ComPtr<ID3DBlob> errorBlob;//エラーオブジェクト

	//頂点シェーダーの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"shaders/SpriteVertexShader.hlsl",//シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//インクルードを可能にする
		"VSmain", "vs_5_0",//エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,//デバッグ用設定
		0,
		&vsBlob, &errorBlob);
	if (FAILED(result))
	{
		//errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		//エラー内容をウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	//ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"shaders/SpritePixelShader.hlsl",//シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//インクルード可能にする
		"PSmain", "ps_5_0",//エントリーポイント名、シェーダモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,//デバッグ用指定
		0,
		&psBlob, &errorBlob);

	if (FAILED(result))
	{
		//errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		//エラー内容をウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
	};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//標準設定
	//標準的な設定(背面カリング、塗りつぶし、深度クリッピング有効)
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//背面カリングしない

	//レンダーターゲットのブレンド設定（8個あるがいまは一つしか使わない）
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;//標準設定

	//ブレンドステートに設定する
	blenddesc.BlendEnable = true;
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	gpipeline.BlendState.RenderTarget[0] = blenddesc;


	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1;//描画対象は１つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0^255指定のRGBA
	gpipeline.SampleDesc.Count = 1;//１ピクセルにつき１回サンプリング

	//デプスステンシルステートの設定
	//標準的な設定(深度テストを行う、書き込み許可、深度が小さければ合格)
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;//深度値フォーマット
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	//ルートシグネチャの生成
	//デスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);//t0レジスタ

	//ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootparams[2];
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);//定数バッファビューとして初期化(b0)
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	//テクスチャサンプラー
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	//ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr< ID3DBlob> rootSigBlob;
	//バージョン自動判定でのシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob);

	//ルートシグネチャの生成
	result = dxCommon->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature));

	//グラフィックパイプラインステートの設定にセット
	gpipeline.pRootSignature = rootSignature.Get();

	result = dxCommon->GetDevice()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineState));
}
