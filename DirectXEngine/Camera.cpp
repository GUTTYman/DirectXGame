#include "Camera.h"
#include"WinApp.h"

using namespace DirectX;

void Camera::Initialize()
{
	const float distance = 20.0f;	//�J��������

	eye = { 0, 0, -distance }; // ���_���W
	target = { 0, 0, 0 }; // �����_���W
	up = { 0, 1, 0 }; // ������x�N�g��

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void Camera::Update()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void Camera::UpdateViewMatrix()
{
	//�r���[�s��ϊ�
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void Camera::UpdateProjectionMatrix()
{
	// �������e
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinApp::window_width / WinApp::window_height,
		0.1f, 2000.0f
	);
}
