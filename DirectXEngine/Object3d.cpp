#include "Object3d.h"
#include<cassert>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")
using namespace DirectX;

//�ÓI�����o�ϐ��̎���
std::unique_ptr < Object3d::Common> Object3d::common;

void Object3d::Common::BasicInitGraphicsPiepeline(DirectXCommon* dxCommon)
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob>vsBlob;//���_�V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob>hsBlob;//�n���V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob>dsBlob;//�h���C���V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob>gsBlob;//�W�I���g���V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob>psBlob;//�s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob;//�G���[�I�u�W�F�N�g
	//�@����F�ɂ���PS
	ComPtr<ID3DBlob>normalColorPsBlob;
	//�e��`�悵�Ȃ�PS
	ComPtr<ID3DBlob>NoneShadowPsBlob;

	//���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"shaders/BasicVS.hlsl",//�V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//�C���N���[�h�\�ɂ���
		"VSmain", "vs_5_0",//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,//�f�o�b�O�p�ݒ�
		0,
		&vsBlob, &errorBlob);

	if (FAILED(result)) {
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "��n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}
	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"shaders/BasicPS.hlsl",//�V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//�C���N���[�h�\�ɂ���
		"PSmain", "ps_5_0",//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,//�f�o�b�O�p�ݒ�
		0,
		&psBlob, &errorBlob);

	if (FAILED(result)) {
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "��n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}
	
	//�W�I���g���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"shaders/BasicGS.hlsl",//�V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//�C���N���[�h�\�ɂ���
		"main", "gs_5_0",//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,//�f�o�b�O�p�ݒ�
		0,
		&gsBlob, &errorBlob);

	if (FAILED(result)) {
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "��n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{
			"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
		{ // uv ���W(1 �s�ŏ������ق������₷��)
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};
#pragma region �ǉ��V�F�[�_�[�R���p�C��
	//�@���J���[�p�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"shaders/NormalColorPS.hlsl",//�V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//�C���N���[�h�\�ɂ���
		"main", "ps_5_0",//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,//�f�o�b�O�p�ݒ�
		0,
		&normalColorPsBlob, &errorBlob);

	if (FAILED(result)) {
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "��n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}//�e��`�悵�Ȃ��p�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"shaders/NoneShadowPS.hlsl",//�V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//�C���N���[�h�\�ɂ���
		"main", "ps_5_0",//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,//�f�o�b�O�p�ݒ�
		0,
		&NoneShadowPsBlob, &errorBlob);

	if (FAILED(result)) {
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "��n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

#pragma endregion

	//�O���t�B�b�N�X�p�C�v���C���̗����ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.GS = CD3DX12_SHADER_BYTECODE(gsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
	//�T���v���}�X�N
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//�W���ݒ�
	//���X�^���C�U�X�e�[�g
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	//�f�v�X�X�e���V���X�e�[�g
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	//�����_�[�^�[�Q�b�g�̃u�����h�ݒ�
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;//�W���ݒ�
	blenddesc.BlendEnable = true;//�u�����h��L���ɂ���t���O
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;//�A���t�@�l�̃u�����h���@
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;//�\�[�X�A���t�@�̊���
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;//�f�X�e�B�l�[�V�����A���t�@�̊���
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD; //���Z
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA; //�\�[�X�̃A���t�@�l
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; //1.0f-�\�[�X�̃A���t�@�l

	//�u�����h�X�e�[�g�ɐݒ肷��
	gpipeline.BlendState.RenderTarget[0] = blenddesc;
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	gpipeline.NumRenderTargets = 1;//�`��Ώۂ�1��
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0�`255�w���RGBA
	gpipeline.SampleDesc.Count = 1;//1�s�N�Z���ɂ�1��T���v�����O

	//�f�X�N���v�^�e�[�u���̐ݒ�
	CD3DX12_DESCRIPTOR_RANGE  descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	//���[�g�p�����[�^�̐ݒ�
	CD3DX12_ROOT_PARAMETER rootparams[3] = {};
	rootparams[0].InitAsConstantBufferView(0);
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[2].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);

	//�X�^�e�B�b�N�T���v���[
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);
	//���[�g�V�O�l�`���̐ݒ�
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob>rootSigBlob;
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	//���[�g�V�O�l�`������
	result = dxCommon->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature));
	assert(SUCCEEDED(result));

	//�p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	gpipeline.pRootSignature = rootsignature.Get();
	//�@���J���[�̃V�F�[�_�[����������悤
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline2 = gpipeline;
	gpipeline2.PS = CD3DX12_SHADER_BYTECODE(normalColorPsBlob.Get());
	//�e�Ȃ��̃V�F�[�_�[����������悤
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline3 = gpipeline;
	gpipeline3.PS = CD3DX12_SHADER_BYTECODE(NoneShadowPsBlob.Get());

#pragma endregion
	result = dxCommon->GetDevice()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate[OBJtype::DEFAULT]));
	assert(SUCCEEDED(result));

	result = dxCommon->GetDevice()->CreateGraphicsPipelineState(&gpipeline2, IID_PPV_ARGS(&pipelinestate[OBJtype::NORMALCOLOR]));
	assert(SUCCEEDED(result));
	
	result = dxCommon->GetDevice()->CreateGraphicsPipelineState(&gpipeline3, IID_PPV_ARGS(&pipelinestate[OBJtype::NONE_SHADOW]));
	assert(SUCCEEDED(result));
}

void Object3d::Common::InitializeCamera()
{

}
void Object3d::StaticInitialize(DirectXCommon* dxCommon, Camera* camera)
{
	common = std::make_unique<Common>();

	common->dxCommon = dxCommon;
	//�O���t�B�N�X�p�C�v���C���̏�����
	common->BasicInitGraphicsPiepeline(dxCommon);
	//�J�����̏�����
	common->InitializeCamera();

	common->camera = camera;
}

Object3d::Object3d()
{
}
Object3d::~Object3d()
{

}
void Object3d::Initialize(Model* model)
{
	this->model = model;

	HRESULT result = S_FALSE;

	//�萔�o�b�t�@�r���[�̐���
	result = common->dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));

	//�f�X�N���v�^1���̃T�C�Y
	UINT descHandleIncrementSize = common->dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

}
void Object3d::Update()
{
	HRESULT result;
	XMMATRIX matScale, matRot, matTrans; // �ړ��A��]�A�g�k�̍s��

	//�X�P�[���A��]�A���s�s��̌v�Z
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z); //���s�ړ��s������W����Čv�Z

	//���[���h�s��̍���
	matWorld = XMMatrixIdentity(); //�ό`�����Z�b�g
	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

	//�e�I�u�W�F�N�g�������
	if (parent != nullptr)
	{	//�e�I�u�W�F�N�g�̃��[���h�s���������
		matWorld *= parent->matWorld;
	}

	//�J�����̍s��擾
	const XMMATRIX& matView = common->camera->getMatView();
	const XMMATRIX& matProjection = common->camera->getMatProjection();
	const XMFLOAT3& cameraPos = common->camera->GetEye();

	//�萔�o�b�t�@�ւ̃f�[�^�]��
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->color = XMFLOAT4(color.x, color.y, color.z, alpha);//RGBA
	constMap->normalLength = { normalLength.x,normalLength.y,normalLength.z };
	constMap->viewproj = matView * matProjection;
	constMap->world = matWorld;
	constMap->cameraPos = cameraPos;
	constMap->randomVertex = { randomVertex.x,randomVertex.y,randomVertex.z };
	constBuff->Unmap(0, nullptr);

}

void Object3d::Draw(ID3D12GraphicsCommandList* cmdList)
{
#pragma region ���ʕ`��R�}���h
	//�p�C�v���C���X�e�[�g�̐ݒ�
	cmdList->SetPipelineState(common->pipelinestate[type].Get());
	//���[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetGraphicsRootSignature(common->rootsignature.Get());
	//�v���~�e�B�u�`���ݒ�
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
#pragma endregion

#pragma region �ʂ̕`��R�}���h
	// �萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//���C�g�̕`��
	common->light->Draw(cmdList, 2);
	//���f���̕`��
	model->Draw(cmdList);

#pragma endregion
}