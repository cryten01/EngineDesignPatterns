#pragma once

#include <glad/glad.h> // include before GLFW!
#include <memory>
#include <iostream>
#include <assert.h>

namespace GPULog
{
	namespace
	{
		enum class LogLevel
		{
			HIGH = 0,
			MEDIUM = 1,
			LOW = 2,
			NOTIFICATION = 3
		};

		static LogLevel s_LogLevel;

		/*
		* The callback function that gets called when OpenGL tracks an error.
		* The APIENTRY qualifier required for glDebugMessageCallback.
		*/
		void APIENTRY GLDebugLogCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			if (id == 131185 || id == 131218) return;  // Ignore performance warnings from nvidia

			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:
				if ((int)s_LogLevel >= 0)
				{
					std::cout << ("[OpenGL Debug HIGH] {0}", message) << std::endl;
					assert(false && "GL_DEBUG_SEVERITY_HIGH"); // Use call stack for identifying error location
				}
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				if ((int)s_LogLevel >= 1)
					std::cout << ("[OpenGL Debug MEDIUM] {0}", message) << std::endl;
				break;
			case GL_DEBUG_SEVERITY_LOW:
				if ((int)s_LogLevel >= 2)
					std::cout << ("[OpenGL Debug LOW] {0}", message) << std::endl;
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				if ((int)s_LogLevel >= 3)
					std::cout << ("[OpenGL Debug NOTIFICATION] {0}", message) << std::endl;
				break;
			}
		};
	}


	void Init() 
	{
		// Sets default log level
		s_LogLevel = LogLevel::HIGH;

		// Registers your callback function
		glDebugMessageCallback(GLDebugLogCallback, NULL);

		glEnable(GL_DEBUG_OUTPUT);

		// Enables synchronous callbacks 
		// This ensures that callback functions are called right after an error has occurred.
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	};


	inline void SetLogLevel(LogLevel level)
	{
		s_LogLevel = level;
	};
};

