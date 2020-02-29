#include "Camera.h"

void Camera::UpdateViewMat()
{
	XMMATRIX rotationMat = XMMatrixRotationRollPitchYawFromVector(m_rotationVec);
	XMMATRIX translationMat = XMMatrixTranslationFromVector(m_positionVec);
	m_viewMat = rotationMat * translationMat;
}

void Camera::UpdateProjectionMat()
{
	m_projectionMat = XMMatrixPerspectiveFovLH(m_fov, m_aspectRatio, m_NEAR_Z, m_FAR_Z);
}

XMVECTOR Camera::CalculateForwardVec()
{
	XMMATRIX rotationMat = XMMatrixRotationRollPitchYawFromVector(m_rotationVec);
	return XMVector4Transform(m_Z_UNIT_VEC, rotationMat);
}

XMVECTOR Camera::CalculateRightVec()
{
	XMMATRIX rotationMat = XMMatrixRotationRollPitchYawFromVector(m_rotationVec);
	return XMVector4Transform(m_X_UNIT_VEC, rotationMat);
}

XMVECTOR Camera::CalculateUpVec()
{
	XMMATRIX rotationMat = XMMatrixRotationRollPitchYawFromVector(m_rotationVec);
	return XMVector4Transform(m_Y_UNIT_VEC, rotationMat);
}

void Camera::SetPosition(const XMFLOAT4 * const position)
{
	m_positionVec = XMLoadFloat4(position);
	UpdateViewMat();
}

void Camera::SetRotation(const XMFLOAT4 * const rotation)
{
	m_rotationVec = XMLoadFloat4(rotation);
	UpdateViewMat();
}

void Camera::SetFov(float fov)
{
	m_fov = fov;
	UpdateProjectionMat();
}

void Camera::SetAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	UpdateProjectionMat();
}

void Camera::RotatePitch(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}

	float previousPitch = XMVectorGetX(m_rotationVec);
	float newPitch = previousPitch - radians;

	if (newPitch > XM_PIDIV2)
	{
		newPitch = XM_PIDIV2;
	}
	else if (newPitch < -XM_PIDIV2)
	{
		newPitch = -XM_PIDIV2;
	}

	m_rotationVec = XMVectorSetX(m_rotationVec, newPitch);
	UpdateViewMat();
}

void Camera::RotateYaw(float radians)
{
	if (radians == 0.0f)
	{
		return;
	}

	float previousYaw = XMVectorGetY(m_rotationVec);
	float newYaw = previousYaw - radians;

	if (newYaw > XM_PI)
	{
		newYaw = XM_PI;
	}
	else if (newYaw < -XM_PI)
	{
		newYaw = -XM_PI;
	}

	m_rotationVec = XMVectorSetY(m_rotationVec, newYaw);
	UpdateViewMat();
}

void Camera::MoveForward(float units)
{
	XMVECTOR translationVec = CalculateForwardVec() * units;
	m_positionVec += translationVec;
	UpdateViewMat();
}

void Camera::MoveRight(float units)
{
	XMVECTOR translationVec = CalculateRightVec() * units;
	m_positionVec += translationVec;
	UpdateViewMat();
}

void Camera::MoveUp(float units)
{
	XMVECTOR translationVec = CalculateUpVec() * units;
	m_positionVec += translationVec;
	UpdateViewMat();
}

Camera::Camera()
	: m_positionVec(XMVectorZero()),
	m_rotationVec(XMVectorZero()),

	m_X_UNIT_VEC_FLOAT(1.0f, 0.0f, 0.0f, 0.0f),
	m_Y_UNIT_VEC_FLOAT(0.0f, 1.0f, 0.0f, 0.0f),
	m_Z_UNIT_VEC_FLOAT(0.0f, 0.0f, 1.0f, 0.0f),

	m_X_UNIT_VEC(XMLoadFloat4(&m_X_UNIT_VEC_FLOAT)),
	m_Y_UNIT_VEC(XMLoadFloat4(&m_Y_UNIT_VEC_FLOAT)),
	m_Z_UNIT_VEC(XMLoadFloat4(&m_Z_UNIT_VEC_FLOAT)),

	m_NEAR_Z(0.1f),
	m_FAR_Z(1000.0f),

	m_fov(90.0f),
	m_aspectRatio(1.0f)
{
}

XMMATRIX Camera::GetViewProjectionMat()
{
	return XMMatrixInverse(nullptr, m_viewMat) * m_projectionMat;
}
