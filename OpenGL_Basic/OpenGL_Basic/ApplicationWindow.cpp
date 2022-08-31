#include "ApplicationWindow.h"
#include <glad/glad.h>
#include <stdexcept>

namespace glfwutils
{
	ApplicationWindow::ApplicationWindow(const int width, const int height, const char* title): width{width}, height{height}, firstClick{true}, camera{std::make_unique<graphics::Camera>(width, height, 45.0f, 0.1f, 100.0f)}
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		scene.addMesh("Skull.obj", "Skull.jpg", graphics::FileFormat3D::OBJ);
	}

	ApplicationWindow::~ApplicationWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void ApplicationWindow::Run()
	{
		GLfloat vertices[] =
		{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
			-0.5f, 0.0f,  0.5f,      	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
			-0.5f, 0.0f, -0.5f,     	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
			 0.5f, 0.0f, -0.5f,     	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
			 0.5f, 0.0f,  0.5f,     	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

			-0.5f, 0.0f,  0.5f,      	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
			-0.5f, 0.0f, -0.5f,     	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
			 0.0f, 0.8f,  0.0f,       	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

			-0.5f, 0.0f, -0.5f,     	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
			 0.5f, 0.0f, -0.5f,     	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
			 0.0f, 0.8f,  0.0f,     	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

			 0.5f, 0.0f, -0.5f,     	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
			 0.5f, 0.0f,  0.5f,     	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
			 0.0f, 0.8f,  0.0f,     	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

			 0.5f, 0.0f,  0.5f,     	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
			-0.5f, 0.0f,  0.5f,      	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
			 0.0f, 0.8f,  0.0f,     	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
		};

		// Indices for vertices order
		GLuint indices[] =
		{
			0, 1, 2, // Bottom side
			0, 2, 3, // Bottom side
			4, 6, 5, // Left side
			7, 9, 8, // Non-facing side
			10, 12, 11, // Right side
			13, 15, 14 // Facing side
		};
		glutils::Texture2D texture("brick.png", GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		glutils::Shader shaderProgram("default.vert", "default.frag");
		// Generates Vertex Array Object and binds it
		glutils::VertexArrayObject VAO1;
		VAO1.Bind();
		// Generates Vertex Buffer Object and links it to vertices
		glutils::VertexBufferObject VBO1;
		VBO1.initialize(vertices, sizeof(vertices), GL_STATIC_DRAW);
		// Generates Element Buffer Object and links it to indices
		glutils::ElementBufferObject EBO1;
		EBO1.initialize(indices, sizeof(indices), GL_STATIC_DRAW);
		// Links VBO attributes such as coordinates and colors to VAO
		VAO1.VertexAttribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAO1.VertexAttribute(VBO1, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.VertexAttribute(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
		// Unbind all to prevent accidentally modifying them
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			const auto currentTime = glfwGetTime();
			handleInputs();
			//scene.drawMeshes(*camera);
			shaderProgram.Use();
			
			shaderProgram.setUniform1f("tex0", 0);
			shaderProgram.setUniformMat4x4f("model", glm::mat4(1.0f));
			shaderProgram.setUniform3f("cameraPosition", camera->pos());
			shaderProgram.setUniformMat4x4f("cameraMatrix", camera->cameraMatrix());
			texture.Bind();
			VAO1.Bind();
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, indices);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void ApplicationWindow::handleInputs()
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera->moveForward();
		}


		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera->moveBackward();
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera->moveLeft();
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera->moveRight();
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			camera->moveUp();
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			camera->moveDown();
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			camera->increaseSpeed();
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			camera->resetSpeed();
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
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "transforms" them into degrees 
			float rotateX = 100.0f * (float)(mouseY - (height / 2)) / height;
			float rotateY = 100.0f * (float)(mouseX - (width / 2)) / width;

			camera->rotate(rotateX, rotateY);
			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}
	}
}