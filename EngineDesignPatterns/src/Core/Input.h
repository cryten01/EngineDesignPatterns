#pragma once

#include <GLFW/glfw3.h>

namespace Input
{
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		static bool wireframe;
		static bool culling;

		if (action != GLFW_RELEASE)
			return;

		switch (key) 
		{
		case GLFW_KEY_ESCAPE: 
		{
			glfwSetWindowShouldClose(window, true);
			break;
		}
		case GLFW_KEY_F1: 
		{
			wireframe = !wireframe;
			glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
			break;
		}
		case GLFW_KEY_F2:
		{
			culling = !culling;

			if (culling)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);

			break;
		}
		}
	};

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{};

	void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
	{};

	void cursor_pos_callback(GLFWwindow* window, double xPos, double yPos)
	{};
}