#include "core/device.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <cassert>

//#define FULL_SCREEN
//#define WINDOWED_FULL_SCREEN

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
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // we prefer double buffering
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // since we're only working with vulkan, no context is needed

	// create window according to preference
#ifdef FULL_SCREEN
	// set monitor
	monitor = glfwGetPrimaryMonitor();
	window = glfwCreateWindow(640, 480, "chaotic pretty", monitor, NULL);
#elif WINDOWED_FULL_SCREEN
	monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "chaotic pretty", monitor, NULL);
#else
	m_window = glfwCreateWindow(1920, 1080, "chaotic pretty", m_monitor, NULL);
#endif
	if (!m_window)
	{
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	if (m_monitor)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(m_window, KeyCallback);

	glfwSetTime(0.0);

	assert(success);
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

void* Device::GetWindow()
{
	return m_window;
}

bool Device::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
}