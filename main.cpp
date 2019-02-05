#include <iostream>
#include <glm/glm.hpp>
#include "tools.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Color.h"
#include "RenderWindow.h"

int MAIN
{


	RenderWindow window(640, 480, "Hello World");

	



	while (!window.shouldClose())
	{
		glfwPollEvents();

		for(int x=10; x<100; x++)
		{
			for(int y=10; y<100; y++)
			{
				window.drawPixel(x, y, Color::red());
			}
		
		}


		window.render();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glfwTerminate();
	return 0;
}