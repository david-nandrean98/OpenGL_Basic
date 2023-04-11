#include "ApplicationWindow.h"
#include "QuadricSurfaceCreator.h"
#include <glad/glad.h>
#include <stdexcept>
#include <iostream>

namespace glfwutils
{
	ApplicationWindow::ApplicationWindow(const int width, const int height, const char* title): width{width}, height{width}, firstClick{true}, camera{width, height, 45.0f, 0.5f, 1000.0f}
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (window == nullptr)
		{
			glfwTerminate();
			throw std::runtime_error("Window could not be initialized!");
		}
		glfwMakeContextCurrent(window);
		gladLoadGL();
		glViewport(0, 0, width, height);

		glClearColor(0.07f, 1.0f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		std::vector<std::string> facesCubemap =
		{
			"skybox/yokohama/right.jpg",
			"skybox/yokohama/left.jpg",
			"skybox/yokohama/top.jpg",
			"skybox/yokohama/bottom.jpg",
			"skybox/yokohama/front.jpg",
			"skybox/yokohama/back.jpg"
		};
		/*
		scene.createSkybox(facesCubemap);


		scene.addShader("default.vert", "default.frag");
		scene.addTexture("brick.png");
		scene.addSphere(camera);
		scene.addSphere(camera);
		scene.getObject(1).translate(glm::vec3(30.0f, 50.0f, 10.0f));
		scene.addLight(Light(Light::LightType::Directional, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.8f)));
		scene.addLight(Light(Light::LightType::Directional, glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.2f, 0.5f, 0.0f)));
		*/
		rtScene.addLight(Light(Light::LightType::Directional, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.8f)));
		rtScene.addLight(Light(Light::LightType::Directional, glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.2f, 0.5f, 0.0f)));
		//auto& surf = rtScene.addQuadricSurface(graphics::QuadricSurface(graphics::QuadricSurfaceCreator::Sphere(), graphics::QuadricSurface::Type::Diffuse, graphics::Material::Gold()));
		//surf.translate(glm::vec3(8.0f, 2.0f, 0.0f));
		auto* surf = &rtScene.addQuadricSurface(graphics::QuadricSurface(graphics::QuadricSurfaceCreator::Plane(), graphics::QuadricSurface::Type::Reflective, graphics::Material::Chrome()));
		surf->scale(0.003f);
		surf = &rtScene.addQuadricSurface(graphics::QuadricSurface(graphics::QuadricSurfaceCreator::Sphere(), graphics::QuadricSurface::Type::Diffuse, graphics::Material::Copper()));
		surf->translate(glm::vec3(15.0f, 7.0f, 1.0f));
		surf->scale(glm::vec3(15.0f, 7.0f, 8.0f));

		//surf.translate(glm::vec3(-2.0f, -2.0f, 0.0f));
		rtScene.addRayTraceShader(facesCubemap);


	}

	ApplicationWindow::~ApplicationWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void ApplicationWindow::Run()
	{
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			const auto currentTime = glfwGetTime();
			handleInputs();
			rtScene.draw(camera);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void ApplicationWindow::handleInputs()
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.moveForward();
		}


		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.moveBackward();
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.moveLeft();
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.moveRight();
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			camera.moveUp();
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			camera.moveDown();
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			camera.increaseSpeed();
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			camera.resetSpeed();
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			if (firstClick)
			{
				firstClick = false;
				glfwSetCursorPos(window, (width / 2), (height / 2));
			}
			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotateX = 100.0f * (float)(mouseY - (height / 2)) / height;
			float rotateY = 100.0f * (float)(mouseX - (width / 2)) / width;

			camera.rotate(rotateX, rotateY);
			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}
	}
}