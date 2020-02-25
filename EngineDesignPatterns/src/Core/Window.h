#pragma once

#include <glad/glad.h> // include before GLFW!
#include <GLFW/glfw3.h>

#include "Core/Input.h"

namespace Window
{
	void GLFWErrorCallback(int error, const char* description)
	{
		std::cout << ("GLFW Error ({0}): {1}", error, description) << std::endl;
	}

	GLFWwindow* Create(const char* screenTitle, const uint32_t screenWidth, const uint32_t screenHeight)
	{
		// Initialize GLFW
		bool success = glfwInit();
		assert(success && "Failed to initialize GLEW!");
		glfwSetErrorCallback(GLFWErrorCallback);

		// Configure GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // window size fixed
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		// GLFW: Window creation
		GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, screenTitle, NULL, NULL);
		assert(window && "Failed to create window!");

		// GLFW: Make the window's context current
		glfwMakeContextCurrent(window);

		// GLFW: Set callbacks
		glfwSetKeyCallback(window, Input::key_callback);
		glfwSetMouseButtonCallback(window, Input::mouse_button_callback);
		glfwSetScrollCallback(window, Input::scroll_callback);
		glfwSetCursorPosCallback(window, Input::cursor_pos_callback);

		// GLAD: Load all OpenGL function pointers
		assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) && "Failed to init GLAD!");

		return window;
	}

	int Destroy() 
	{
		// Terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
		return 0;
	}
}
