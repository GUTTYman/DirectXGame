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
		friend class GPUParticle;
	public:
		/// <summary>
		/// �O���t�B�N�X�p�C�v���C��������
		/// </summary>
		/// <param name="dxCommon">DirectX���</param>
		void InitializeGraphicsPipeline(DirectXCommon* dxCommon);
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
		ComPtr < ID3D12PipelineState> pipelinestate[3];
		//�J����
		Camera* camera = nullptr;
	};

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {

		XMFLOAT4 color;// �F (RGBA)
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
		int time;
		int maxCount;
	};

public://�ÓI�����o�֐�
	/// <summary>
	/// �ÓI�����o�̏�����
	/// </summary>
	static void StaticInitialize(DirectXCommon* dxCommon, Camera* camera);
	/// <summary>
	/// �f�X�N���v�^�[�q�[�v���Z�b�g
	/// </summary>
	static void ResetDescriptorHeap();

private://�ÓI�����o�ϐ�
	static std::unique_ptr < Common> common;

public://�����o�֐�
	GPUParticle();

	~GPUParticle();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// ���f���`��
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList, ParticleMode mode, int instanceIndex);
	/// <summary>
	/// ���_�̂ݕ`��
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
	//�g�����X�t�H�[��
	Vector3 scale = { 1,1,1 };
	Vector3 rotation = { 0,0,0 };
	Vector3 position = { 0,0,0 };
	Vector3 color = { 1,1,1 };
	int time = 0;
	int maxCount = 0;

	XMMATRIX matWorld;			//���[�J�����[���h�ϊ��s��


	GPUParticle* parent = nullptr;	//�e�I�u�W�F�N�g
	//���f���f�[�^
	Model* model = nullptr;
};

