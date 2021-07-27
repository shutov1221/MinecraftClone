#include "WindowEvents.h"

void WindowEvents::Initialize() {
	
	glfwSetWindowSizeCallback(Window::GetNativeWindow(), [](GLFWwindow* nativeWindow, int width, int height) {
		Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

		glViewport(0, 0, width, height);
		window->SetWidth(width);
		window->SetHeight(height);
	});
}

void WindowEvents::PullWindowEvents() {
	Window::SwapBuffers();
	glfwPollEvents();
}
