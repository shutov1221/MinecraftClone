#include "EventsKeys.h"

uint* EventsKeys::_frames;
uint EventsKeys::_current = 0;

EventsKeys::~EventsKeys() {
	delete[] _frames;
}

int EventsKeys::Initialize() {

	_frames = new uint[1032];
	memset(_frames, 0, 1032 * sizeof(uint));

	Window::keyboard->frameHandler(_frames, _current);

	glfwSetKeyCallback(Window::GetNativeWindow(), [](GLFWwindow* nativeWindow, int key, int scancode, int action, int mods) {
		Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

		switch (action)
		{
		case GLFW_REPEAT:
		case GLFW_PRESS:
			_frames[key] = _current;
			window->keyboard->SetKeyPressed(key);
			break;
		case GLFW_RELEASE:
			_frames[key] = -1;
			window->keyboard->SetKeyReleased(key);
			break;

		default:
			break;
		}
	});

	glfwSetMouseButtonCallback(Window::GetNativeWindow(), [](GLFWwindow* nativeWindow, int button, int action, int mode) {
		Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			if (action == GLFW_PRESS)
				window->mouse->SetKeyPressed(MouseButton::RIGHT);
			else if (action == GLFW_RELEASE)
				window->mouse->SetKeyReleased(MouseButton::RIGHT);
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			if (action == GLFW_PRESS)
				window->mouse->SetKeyPressed(MouseButton::LEFT);
			else if (action == GLFW_RELEASE)
				window->mouse->SetKeyReleased(MouseButton::LEFT);
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			if (action == GLFW_PRESS)
				window->mouse->SetKeyPressed(MouseButton::MIDDLE);
			else if (action == GLFW_RELEASE)
				window->mouse->SetKeyReleased(MouseButton::MIDDLE);
			break;

		default:
			break;
		}
	});

	glfwSetCursorPosCallback(Window::GetNativeWindow(), [](GLFWwindow* nativeWindow, double xPos, double yPos) {
		Mouse::dx = xPos - Mouse::x;
		Mouse::dy = yPos - Mouse::y;

		Mouse::x = xPos;
		Mouse::y = yPos;
	});

	return 0;
}

void EventsKeys::PullKeysEvents() {
	Mouse::dx = 0.0f;
	Mouse::dy = 0.0f;
	_current++;
	Window::keyboard->frameHandler(_frames, _current);
}