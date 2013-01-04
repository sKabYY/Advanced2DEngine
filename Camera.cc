#include "Camera.h"

namespace Advanced2D {
	Camera::Camera() {
		p_position = D3DXVECTOR3(0.0f, 0.0f, 10.f);
		p_updir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		float ratio = 640/480;
		setPerspective(3.14159f/4, ratio, 1.0f, 2000.0f);
	}

	Camera::~Camera() {}

	void Camera::setPerspective(float fov, float aspectRatio, 
			float nearRange, float farRange) {
		this->setFOV(fov);
		this->setAspectRatio(aspectRatio);
		this->setNearRange(nearRange);
		this->setFarRange(farRange);
	}

	void Camera::Update() {
		D3DXMatrixPerspectiveFovLH(&this->p_matrixProj, this->p_fov,
				this->p_aspectRatio, this->p_nearRange, this->p_farRange);
		g_engine->getDevice()->SetTransform(D3DTS_PROJECTION, &this->p_matrixProj);
		D3DXMatrixLookAtLH(&this->p_matrixView, &this->p_position, 
				&this->p_target, &this->p_updir);
		g_engine->getDevice()->SetTransform(D3DTS_VIEW, &this->p_matrixView);
	}

	void Camera::setPosition(float x, float y, float z) {
		this->p_position.x = x;
		this->p_position.y = y;
		this->p_position.z = z;
	}

	void Camera::setPosition(D3DXVECTOR3 position) {
		this->setPosition(position.x, position.y, position.z);
	}
}
