#pragma once

#include<d3d12.h>
#include<d3dx12.h>
#include<wrl.h>

#include"DirectXCommon.h"
#include"Model.h"
#include"Camera.h"
#include"Vector.h"

#include <DirectXMath.h>

class NormalColorOBJ
{
public:	//�萔
	static const int maxObjectCount = 3000;//3D�I�u�W�F�N�g�̍ő��

public:   //�G�C���A�X
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	//using XMFLOAT2 = DirectX::XMFLOAT2;
	//using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//���ʃf�[�^
	class Common
	{
		friend class NormalColorOBJ;
	public:
		/// <summary>
		/// �O���t�B�N�X�p�C�v���C��������
		/// </summary>
		/// <param name="dxCommon">DirectX���</param>
		void BasicInitGraphicsPiepeline(DirectXCommon* dxCommon);
		/// <summary>
		/// �J����������
		/// </summary>
		void InitializeCamera();
	private:
		//DirectX12���
		DirectXCommon* dxCommon = nullptr;
		//���[�g�V�O�l�`��
		ComPtr < ID3D12RootSignature> rootsignature;
		//�p�C�v���C���X�e�[�g
		ComPtr < ID3D12PipelineState> pipelinestate;
		//�J����
		Camera* camera = nullptr;
	};

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {

		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
		float randomVertex;	//�I�u�W�F�N�g���т�т�U��������

	};

public://�ÓI�����o�֐�
	/// <summary>
	/// �ÓI�����o�̏�����
	/// </summary>
	static void StaticInitialize(DirectXCommon* dxCommon, Camera* camera);
	/// <summary>
	/// �f�X�N���v�^�[�q�[�v���Z�b�g
	/// </summary>
	static void RestDescriptorHeap();
	/// <summary>
	/// �ÓI�����o�̏I������
	/// </summary>
	static void StaticFinalize();

private://�ÓI�����o�ϐ�
	static Common* common;

public://�����o�֐�
	NormalColorOBJ();

	~NormalColorOBJ();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
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
	inline void SetRandomVertex(float f) { randomVertex = f; }
	inline void SetPosition(Vector3 position) { this->position = position; }
	inline void SetScale(Vector3 scale) { this->scale = scale; }
	inline void SetRotation(Vector3 rotation) { this->rotation = rotation; }

private:
	ComPtr<ID3D12Resource> constBuff;
	//�g�����X�t�H�[��
	Vector3 scale = { 1,1,1 };
	Vector3 rotation = { 0,0,0 };
	Vector3 position = { 0,0,0 };
	Vector3 color = { 1,1,1 };
	XMMATRIX matWorld;			//���[�J�����[���h�ϊ��s��
	Vector3 normalLength = { 0,0,0 };	//�W�I���g���V�F�[�_�[�p�@���̔�΂�����
	float randomVertex = 0.0f;	//�I�u�W�F�N�g���т�т�U��������
	NormalColorOBJ* parent = nullptr;	//�e�I�u�W�F�N�g
	//���f���f�[�^
	Model* model = nullptr;

	//�V�F�[�_�[�̎�ގw��
};

