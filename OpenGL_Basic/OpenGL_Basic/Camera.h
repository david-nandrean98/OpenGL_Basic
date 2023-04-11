#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace graphics
{
	class Camera
	{
	public:
		Camera(const uint16_t width, const uint16_t height, const float FOVdeg, const float nearPlane, const float farPlane, const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f));
		void updateProjectionMatrix(const uint16_t width, const uint16_t height, const float FOVdeg, const float nearPlane, const float farPlane);
		void updateViewMatrix();
		const glm::mat4& cameraMatrix() const;
		const glm::vec3& pos() const;
		const glm::vec3& ori() const;
		const glm::vec3& Up() const;
		const glm::mat4& ViewMatrix() const;
		const glm::mat4& ProjectionMatrix() const;
		void moveForward();
		void moveBackward();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void increaseSpeed();
		void resetSpeed();
		void rotate(const float rotateX, const float rotateY);
	private:
		void updateCameraMatrix();
		glm::vec3 position;
		glm::vec3 orientation;
		glm::vec3 up;
		float speed;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 camMatrix;
	};
}