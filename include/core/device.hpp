#pragma once

struct GLFWwindow;
struct GLFWmonitor;

namespace chap
{
	class Device
	{
	public:
		Device();
		~Device();

		void Update();
		bool ShouldClose();
		void CloseWindow();

		GLFWwindow* GetWindow() { return m_window; }
		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }

	private:
		bool m_fullscreen = false;
		int m_width = 1920;
		int m_height = 1080;
		GLFWwindow* m_window = nullptr;
		GLFWmonitor* m_monitor = nullptr;
	};
}