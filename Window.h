#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Keyboard.h"
#include "Mouse.h"



class Window
{
public:
	static Window* Create(int width, int height, const char* title);
	static GLFWwindow* GetNativeWindow();
	static Mouse* mouse;
	static Keyboard* keyboard;

	static void Terminate();
	static void LockCursor();
	static bool IsShouldClose();
	static void SetShouldClose(bool flag);
	static int GetWidth();
	static int GetHeight();
	static float GetAspect();
	static Window* GetInstance();

	static void SetWidth(int newWidth);
	static void SetHeight(int newHeight);
	static void SetTitle(std::string title);

	static void SwapBuffers();

private:
	static GLFWwindow* window;
	static Window* instance;
	static int width;
	static int height;
	static const char* title;
	static bool cursorLock;
	Window();
	~Window();
};

