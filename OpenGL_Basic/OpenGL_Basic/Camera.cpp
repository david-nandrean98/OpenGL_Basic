#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace graphics
{
	Camera::Camera(const uint16_t width, const uint16_t height, const float FOVdeg, const float nearPlane, const float farPlane, const glm::vec3& pos) : 
		position{pos},
		orientation{0.0f, 0.0f, -1.0f},
		up{0.0f, 1.0f, 0.0f},
		speed{0.01f},
		viewMatrix{glm::lookAt(position, position + orientation, up)},
		projectionMatrix{ glm::perspective(glm::radians(FOVdeg), width / static_cast<float>(height), nearPlane, farPlane) }
	{
		updateCameraMatrix();
	}

	void Camera::updateProjectionMatrix(const uint16_t width, const uint16_t height, const float FOVdeg, const float nearPlane, const float farPlane)
	{
		projectionMatrix = glm::perspective(glm::radians(FOVdeg), float(width / height), nearPlane, farPlane);
		updateCameraMatrix();
	}

	void Camera::updateViewMatrix()
	{
		viewMatrix = glm::lookAt(position, position + orientation, up);
		updateCameraMatrix();
	}

	void Camera::updateCameraMatrix()
	{
		camMatrix = projectionMatrix * viewMatrix;
	}

	const glm::mat4& Camera::cameraMatrix() const
	{
		return camMatrix;
	}

	const glm::vec3& Camera::pos() const
	{
		return position;
	}

	const glm::vec3& Camera::ori() const
	{
		return orientation;
	}

	const glm::vec3& Camera::Up() const
	{
		return up;
	}

	const glm::mat4& Camera::ViewMatrix() const
	{
		return viewMatrix;
	}

	const glm::mat4& Camera::ProjectionMatrix() const
	{
		return projectionMatrix;
	}

	void Camera::moveForward()
	{
		position += speed * orientation;
		updateViewMatrix();
	}

	void Camera::moveBackward()
	{
		position -= speed * orientation;
		updateViewMatrix();
	}

	void Camera::moveLeft()
	{
		position += speed * glm::normalize(glm::cross(up, orientation));
		updateViewMatrix();
	}

	void Camera::moveRight()
	{
		position -= speed * glm::normalize(glm::cross(up, orientation));
		updateViewMatrix();
	}

	void Camera::moveUp()
	{
		position += speed * up;
		updateViewMatrix();
	}

	void Camera::moveDown()
	{
		position -= speed * up;
		updateViewMatrix();
	}

	void Camera::increaseSpeed()
	{
		speed += 0.01f;
	}

	void Camera::resetSpeed()
	{
		speed = 0.1f;
	}

	void Camera::rotate(const float rotateX, const float rotateY)
	{
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotateX), glm::normalize(glm::cross(orientation, up)));
		if (std::abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}
		orientation = glm::rotate(orientation, glm::radians(-rotateY), up);
		updateViewMatrix();
	}
}