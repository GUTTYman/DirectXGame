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

//�I�u�W�F�N�g�̃��[�h
enum OBJtype
{
	DEFAULT,
	NORMALCOLOR,
};

class Object3d
{
public:	//�萔
	static const int maxObjectCount = 3000;//3D�I�u�W�F�N�g�̍ő��

public:   //�G�C���A�X
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//���ʃf�[�^
	class Common
	{
		friend class Object3d;
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
		ComPtr < ID3D12PipelineState> pipelinestate[2];
		//�J����
		Camera* camera = nullptr;
		//���C�g
		Light* light = nullptr;
	};

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {

		XMFLOAT4 color;// �F (RGBA)
		XMFLOAT3 normalLength;
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
		float dummy;
		XMFLOAT3 randomVertex;	//�I�u�W�F�N�g���т�т�U��������

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

private://�ÓI�����o�ϐ�
	static std::unique_ptr<Common> common;

public://�����o�֐�
	Object3d();

	~Object3d();
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
	inline void SetRandomVertex(Vector3 v){randomVertex = v; }
	inline void SetPosition(Vector3 position) { this->position = position; }
	inline void SetScale(Vector3 scale) { this->scale = scale; }
	inline void SetRotation(Vector3 rotation) { this->rotation = rotation; }
	inline static void SetLight(Light* light) { common->light = light; }
	inline void SetOBJType(OBJtype objtype) { type = objtype; }

private:
	ComPtr<ID3D12Resource> constBuff;
	//�g�����X�t�H�[��
	Vector3 scale = Vector3(1,1,1);
	Vector3 rotation = Vector3();
	Vector3 position = Vector3();
	Vector3 normalLength = Vector3();	//�W�I���g���V�F�[�_�[�p�@���̔�΂�����
	Vector3 color = Vector3(1,1,1);
	XMMATRIX matWorld;			//���[�J�����[���h�ϊ��s��
	Vector3 randomVertex = Vector3();	//�I�u�W�F�N�g���т�т�U��������
	Object3d* parent = nullptr;	//�e�I�u�W�F�N�g
	//���f���f�[�^
	Model* model = nullptr;
	//�V�F�[�_�[�̎�ގw��
	OBJtype type = DEFAULT;

};

