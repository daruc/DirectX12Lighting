#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
private:
	const XMFLOAT4 m_X_UNIT_VEC_FLOAT;
	const XMFLOAT4 m_Y_UNIT_VEC_FLOAT;
	const XMFLOAT4 m_Z_UNIT_VEC_FLOAT;

	const XMVECTOR m_X_UNIT_VEC;
	const XMVECTOR m_Y_UNIT_VEC;
	const XMVECTOR m_Z_UNIT_VEC;

	const float m_NEAR_Z;
	const float m_FAR_Z;

	XMVECTOR m_positionVec;
	XMVECTOR m_rotationVec;
	XMMATRIX m_viewMat;

	float m_fov;
	float m_aspectRatio;
	XMMATRIX m_projectionMat;

	void UpdateViewMat();
	void UpdateProjectionMat();
	XMVECTOR CalculateForwardVec();
	XMVECTOR CalculateRightVec();
	XMVECTOR CalculateUpVec();

public:
	void SetPosition(const XMFLOAT4* const position);
	void SetRotation(const XMFLOAT4* const rotation);
	void SetFov(float fov);
	void SetAspectRatio(float aspectRatio);
	void RotatePitch(float radians);
	void RotateYaw(float radians);
	void MoveForward(float units);
	void MoveRight(float units);
	void MoveUp(float units);

	Camera();
	XMMATRIX GetViewProjectionMat();
};

