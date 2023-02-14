#pragma once

#include "Camera.h" 
#include "Scene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>


namespace glfwutils
{
	class ApplicationWindow
	{
	public:
		ApplicationWindow(const int width, const int height, const char* title);
		~ApplicationWindow();
		void Run();
	private:
		void handleInputs();
		int width;
		int height;
		bool firstClick;
		GLFWwindow* window;
		graphics::Camera camera;
		graphics::Scene scene;
		glutils::VertexArrayObject* vao = nullptr;
		glutils::VertexBufferObject vbo;
		glutils::ElementBufferObject ebo;
		glutils::Shader* shader = nullptr;
		glm::mat4 model;
	};
}