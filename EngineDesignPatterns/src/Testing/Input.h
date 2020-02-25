#pragma once

#include <GLFW/glfw3.h>

namespace Input
{
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
			glfwSetWindowShouldClose(window, true);
	};

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{};

	void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
	{};

	void cursor_pos_callback(GLFWwindow* window, double xPos, double yPos)
	{};
}