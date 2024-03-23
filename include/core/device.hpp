#pragma once
#include <GLFW/glfw3.h>

namespace chap
{
	class Device
	{
	public:
		Device();
		~Device();

		bool ShouldClose();
		void Update();

		void* GetWindow();

	private:
		GLFWwindow* m_window = nullptr;
		GLFWmonitor* m_monitor = NULL;
	};
}