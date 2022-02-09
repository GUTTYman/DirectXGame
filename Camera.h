#pragma once
#include"Vector.h"
#include<DirectXMath.h>
class Camera
{
public://�G�C���A�X
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �r���[�s��ϊ��̌v�Z
	/// </summary>
	void UpdateViewMatrix();
	/// <summary>
	/// �������e
	/// </summary>
	void UpdateProjectionMatrix();

	//getter
	inline const XMMATRIX& getMatView() { return matView; }
	inline const XMMATRIX& getMatProjection() { return matProjection; }
	inline const XMFLOAT3& GetEye() { return eye; }
	inline const XMFLOAT3& GetTarget() { return target; }
	inline const XMFLOAT3& GetUp() { return up; }
	//setter
	inline void SetMatView(const XMMATRIX& matView) { this->matView = matView; }
	inline void SetMatProjection(const XMMATRIX& matProjection) { this->matProjection = matProjection; }
	inline void SetEye(const XMFLOAT3& eye) { this->eye = eye; }
	inline void SetEye(const Vector3& eye) { this->eye.x = eye.x; this->eye.y = eye.y; this->eye.z = eye.z; }
	inline void SetTarget(const XMFLOAT3& target) { this->target = target; }
	inline void SetTarget(const Vector3& target) { this->target.x = target.x; this->target.y = target.y; this->target.z = target.z; }
	inline void SetUp(const XMFLOAT3& up) { this->up = up; }

private:
	XMMATRIX matView;				//�r���[�s��
	XMMATRIX matProjection;			//�ˉe�s��
	XMFLOAT3 eye;					//���_���W
	XMFLOAT3 target;				//�����_���W
	XMFLOAT3 up;					//������x�N�g��
};

