#pragma once
#include "Color.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Vector.h"

class RenderWindow
{
	unsigned int buffer;
	int shaderID;
public:
	GLFWwindow* window;
	const int sizex;
	const int sizey;
	RenderWindow(int x, int y, const char*);

	void drawPixel(int x, int y, Color c);

	void render();

	bool shouldClose() { return glfwWindowShouldClose(window); }

};

