#include <iostream>
#include <chrono>
#define FORCE_LOG
#include "tools.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Color.h"
#include "RenderWindow.h"
#include "Mat.h"
#include "MathFunctions.h"

int MAIN
{
	const int screenWidth = 420;
	const int screenHeight = 308;

	float playerX = 8;
	float playerY = 8;
	float playerA = (3.14159 / 4) * 7;

	float fov = 3.14159 / 4;
	float viewDepth = 16.f;

	float distances[screenWidth];


	Mat<const char, 16, 16> map;
	map.p = 
"\
################\
##.............#\
#.#............#\
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
#.#....#.......#\
##.............#\
################\
";


	RenderWindow window(screenWidth, screenHeight, "Hello World");

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();
	float accumulate = 0;
	float framesCount = 0;

	while (!window.shouldClose())
	{
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> duration = tp2 - tp1;
		tp1 = std::chrono::system_clock::now();
		float deltaTime = duration.count();
		accumulate += deltaTime;
		framesCount++;
		if (accumulate >= 1)
		{
			char c[20] = { 0 };
			sprintf_s(c, "%f", framesCount);
			glfwSetWindowTitle(window.window, c);
			accumulate = accumulate-1;
			framesCount = 0;
		}

#pragma region kyes
		float sina = sinf(playerA);
		float cosa = cosf(playerA);

		if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
		{
			playerA -= 1.4 * deltaTime;
		}

		if (GetAsyncKeyState((unsigned short)'E') & 0x8000)
		{
			playerA += 1.4 * deltaTime;
		}

		if(GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{
			playerX += sina * deltaTime * 10.f;
			playerY += cosa * deltaTime * 10.f;

			if(map.at(playerX, playerY) == '#')
			{
				playerX -= sina * deltaTime * 10.f;
				playerY -= cosa * deltaTime * 10.f;
			}
		}

		if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		{
			playerX -= sina * deltaTime * 10.f;
			playerY -= cosa * deltaTime * 10.f;

			if (map.at(playerX, playerY) == '#')
			{
				playerX += sina * deltaTime * 10.f;
				playerY += cosa * deltaTime * 10.f;
			}
		}

#pragma endregion



		glfwPollEvents();

		for(int x=0; x<screenWidth; x++)
		{
			float rayAngle = (playerA - (fov / 2.f)) + ((float)x / screenWidth)*fov;

#pragma region temp
			//temp
			bool hitWall = 0;
			distances[x] = 0;
			while (!hitWall)
			{
				distances[x] += 0.1;
				if (map.at((int)(sinf(rayAngle) * distances[x] + playerX), (int)(cosf(rayAngle) * distances[x] + playerY)) == '#')
				{
					hitWall = 1;
				}

				if (distances[x] >= viewDepth) { break; }
			}
			//temp
#pragma endregion

#pragma region detSpace
			int minx;
			int miny;
			int maxx;
			int maxy;
			int quadrant = getQuadrant(rayAngle);
			if (quadrant == 1)
			{
				minx = (int)playerX + 1;
				maxx = map.width();
				miny = (int)playerY - 1;
				maxy = 0;
			}
			else if (quadrant == 2)
			{
				minx = (int)playerX + 1;
				maxx = map.width();
				miny = (int)playerY + 1;
				maxy = 16;
			}
			else if (quadrant == 3)
			{
				minx = (int)playerX - 1;
				maxx = 0;
				miny = (int)playerY + 1;
				maxy = 16;
			}
			else
			{
				minx = (int)playerX - 1;
				maxx = 0;
				miny = (int)playerY - 1;
				maxy = 0;
			}

#pragma endregion

			float distx = fov + 1;
			for (int linex = minx; linex < maxx; linex++) 
			{
				//auto intersectPos = intersect(rayAngle, playerX, playerY, )

			}
			
			float disty = fov ;
			for (int liney = miny; liney < maxy; liney++)
			{
				auto intersectPos = intersect(rayAngle, playerX, playerY, 0, liney);
				float distance = getDistance(intersectPos.first, intersectPos.second, playerX, playerY);
				if (distance < disty) { disty = distance; }
			}

			//distances[x] = disty;
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
					window.drawPixel(x, y, Color(50, 10, 10));
				}
			}
		
		}
		
		window.render();
		//window.clear(Color(200,0,0));
		//glClear(GL_COLOR_BUFFER_BIT);
	}

	window.cleanup();
	glfwTerminate();
	return 0;
}