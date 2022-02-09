#include "Camera.h"
#include"WinApp.h"

using namespace DirectX;

void Camera::Initialize()
{
	const float distance = 20.0f;	//カメラ距離

	eye = { 0, 0, -distance }; // 視点座標
	target = { 0, 0, 0 }; // 注視点座標
	up = { 0, 1, 0 }; // 上方向ベクトル

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
	//ビュー行列変換
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void Camera::UpdateProjectionMatrix()
{
	// 透視投影
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinApp::window_width / WinApp::window_height,
		0.1f, 2000.0f
	);
}
