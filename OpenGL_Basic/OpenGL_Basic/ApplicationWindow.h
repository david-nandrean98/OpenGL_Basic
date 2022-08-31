#pragma once

#include "Camera.h" 
#include "Scene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>


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
		std::unique_ptr<graphics::Camera> camera;
		graphics::Scene scene;
	};
}