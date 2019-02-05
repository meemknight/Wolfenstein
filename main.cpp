#include <iostream>
#include <glm/glm.hpp>
#include "tools.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Color.h"
#include "RenderWindow.h"
#include "Mat.h"

int MAIN
{
	const int screenWidth = 360;
	const int screenHeight = 228;

	float playerX = 8;
	float playerY = 8;
	float playerA = 3.14159 / 4;

	float fov = 3.14159 / 4;
	float viewDepth = 16.f;

	float distances[screenWidth];


	Mat<const char, 16, 16> map;
	map.p = 
"\
################\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
#..............#\
################\
";


	RenderWindow window(screenWidth, screenHeight, "Hello World");



	while (!window.shouldClose())
	{
		glfwPollEvents();

		for(int x=0; x<screenWidth; x++)
		{
			float rayAngle = (playerA - (fov / 2.f)) + ((float)x / screenWidth)*fov;

			//temp
			bool hitWall = 0;
			distances[x] = 0;
			while(!hitWall)
			{
				distances[x]+= 0.1;
				if(map.at((int)(sinf(rayAngle) * distances[x] + playerX), (int)(cosf(rayAngle) * distances[x] + playerY)) == '#')
				{
					hitWall = 1;
				}

				if (distances[x] >= viewDepth) { break; }
			}

		}
		
		for(int x=0; x<screenWidth; x++)
		{
			int ceeling = (screenHeight / 2.f) - (screenHeight / distances[x]);
			int floor = screenHeight - ceeling;
			
			for(int y=0; y<screenHeight; y++)
			{
				if(y<ceeling)
				{
					window.drawPixel(x, y, Color(10, 10, 10));
				}else
				if(y<floor)
				{
					window.drawPixel(x, y, Color(100, 100, 100));
				}else
				{
					window.drawPixel(x, y, Color(10, 10, 10));
				}
			}
		
		}


		window.render();
		//glClear(GL_COLOR_BUFFER_BIT);
	}

	glfwTerminate();
	return 0;
}