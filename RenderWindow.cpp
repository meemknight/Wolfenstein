#include "RenderWindow.h"
#include "tools.h"

const GLchar* vertexShaderSource =
"                                                   \
#version 330                                        \n\
													\
layout (location = 0) in vec4 inVertexPosition;     \
layout (location = 1) in vec4 inColor;			    \
		out vec4 c; 								\
													\
													\
void main()                                         \
{                                                   \
	gl_Position =  vec4(inVertexPosition.xy, 1.0, 1.0);	\
	c = inColor;									\
}                                                   \
";

const GLchar* fragmentShaderSource =
"                                                   \
#version 330                                        \n\
in vec4 c;                                          \
out vec4 color;                                     \
void main()                                         \
{                                                   \
	color = vec4(c.rgb, 1);	                        \
}                                                   \
";


RenderWindow::RenderWindow(int x, int y, const char* t):sizex(x), sizey(y)
{
	if (!glfwInit())
	{std::exit(1); }

	window = glfwCreateWindow(x, y, t, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		{std::exit(1); }
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{std::exit(2); }

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector) * 8) * x * y, 0, GL_DYNAMIC_DRAW);
	
	for (int sy = 0; sy < y; sy++)
	{
		for (int sx = 0; sx < x; sx++)
		{
			//tempbuf[pos] = ((((float)x / (float)width) * 2) - 1)*-1;	//x
			
			//tempbuf[pos] = ((((float)y / (float)height) * 2) - 1)*-1; 	//y
			Vector v[2];
			v[0].x = ((((float)sx / x) * 2) -1)*1;
			v[0].y = ((((float)sy / y) * 2) -1)*-1;
			v[1].x = 0;
			v[1].y = 0;
			v[1].z = 0;
			v[1].w = 0;
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 8 * (sx + (sy*sizex)), sizeof(Vector) * 2, v);
		}

	}


	shaderID = glCreateProgram();
	auto vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShaderID);

	{
		GLint isSuccess;
		GLchar infoLog[512];

		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &isSuccess);

		if (!isSuccess)
		{
			glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
			llog("Error compiling vertex shader: ", std::string(infoLog).c_str());
			pause();
			exit(1);
		}
	}

	auto fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShaderID);

	{
		GLint isSuccess;
		GLchar infoLog[512];

		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &isSuccess);

		if (!isSuccess)
		{
			glGetShaderInfoLog(fragmentShaderID, 512, nullptr, infoLog);
			llog("Error compiling fragment shader: ", std::string(infoLog).c_str());
			pause();
			exit(1);
		}
	}

	glAttachShader(shaderID, vertexShaderID);
	glAttachShader(shaderID, fragmentShaderID);
	glLinkProgram(shaderID);
	glValidateProgram(shaderID);

	{
		GLint success;
		GLchar infoLog[512];

		glGetShaderiv(shaderID, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);     // Generate error as infoLog
			std::cout << "Error " << infoLog << std::endl;  // Display
		}
	}
	glUseProgram(shaderID);
}

void RenderWindow::drawPixel(int x, int y, Color c)
{
	Vector v;
	v.x = (float)c.r / UCHAR_MAX;
	v.y = (float)c.g / UCHAR_MAX;
	v.z = (float)c.b / UCHAR_MAX;

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 8 * (x + (y*sizex)) + sizeof(float) * 4, sizeof(Vector), &v);
}

void RenderWindow::clear(Color c)
{
	for(int y=0; y<sizey; y++)
	{
		for (int x = 0; x < sizex; x++)
		{
			drawPixel(x, y, c);
		}
	}
}

void RenderWindow::render()
{
	glUseProgram(shaderID);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glVertexAttribPointer(0, 4, GL_FLOAT ,0 , 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT ,0 , 0, (const void*)(sizeof(float) * 4));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_POINTS, 0, sizex * sizey * 2);

	glfwSwapBuffers(window);
}
