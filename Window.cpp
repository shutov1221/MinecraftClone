#include "Window.h"

GLFWwindow* Window::window = nullptr;
Window* Window::instance = nullptr;

int Window::width = 0;
int Window::height = 0;

const char* Window::title = "";
bool Window::cursorLock = false;
Mouse* Window::mouse = new Mouse;
Keyboard* Window::keyboard = new Keyboard;

Window::Window(){}

Window* Window::Create(int width, int height, const char* title) {

    if (window == nullptr) {

        instance = new Window;

        instance->width = width;
        instance->height = height;
        instance->title = title;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        instance->window = glfwCreateWindow(instance->width, instance->height, instance->title, nullptr, nullptr);
        if (instance->window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }
        glfwSetWindowUserPointer(instance->window, instance);
        glfwMakeContextCurrent(instance->window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return nullptr;
        }

        glViewport(0, 0, instance->width, instance->height);

        return instance;
    }

    instance;
}

Window::~Window() {
    glfwTerminate();
}

void Window::Terminate() {
    glfwTerminate();
}

bool Window::IsShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::SetShouldClose(bool flag) {
    glfwSetWindowShouldClose(window, flag);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

int Window::GetHeight() {
    return height;
}

int Window::GetWidth() {
    return width;
}

float Window::GetAspect() {
    return (float)width / (float)height;
}

Window* Window::GetInstance() {
    return instance;
}

void Window::SetWidth(int newWidth) {
    width = newWidth;
}

void Window::SetHeight(int newHeight) {
    height = newHeight;
}

void Window::SetTitle(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

GLFWwindow* Window::GetNativeWindow() {
    return window;
}

void Window::LockCursor() {
    cursorLock = !cursorLock;
    glfwSetInputMode(window, GLFW_CURSOR, cursorLock ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}
