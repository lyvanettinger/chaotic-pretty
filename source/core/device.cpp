#include "core/device.hpp"

#include <cassert>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "rendering/open_gl.h"

#include <stdlib.h>
#include <stdio.h>

using namespace chap;

void ErrorCallback(int error, const char* description)
{
	fputs(description, stderr);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		default:
			break;
		}
	}
}

Device::Device()
{
	// initialize glfw
	bool success = glfwInit();
	if (!success)
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	// set the error callback
	glfwSetErrorCallback(ErrorCallback);

	// set window hints
	//glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // we prefer double buffering
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);

	auto monitorScreenWidth = mode->width;
	auto monitorScreenHeight = mode->height;

	if (m_fullscreen)
	{
		m_width = monitorScreenWidth;
		m_height = monitorScreenHeight;
		m_window = glfwCreateWindow(m_width, m_height, "chaotic pretty", m_monitor, nullptr);
	}
	else
	{
		m_window = glfwCreateWindow(m_width, m_height, "chaotic pretty", nullptr, nullptr);
	}

	if (!m_window)
	{
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		assert(false);
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to initialize GLAD\n");
		assert(false);
		exit(EXIT_FAILURE);
	}

	if (m_monitor)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(m_window, KeyCallback);

	glfwSetTime(0.0);
}

Device::~Device()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Device::Update()
{
	glfwPollEvents();
}

bool Device::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void Device::CloseWindow()
{
	glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}