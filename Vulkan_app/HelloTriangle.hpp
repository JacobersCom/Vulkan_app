#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangle
{
private:

	int width = 700, height = 700;
	GLFWwindow* glfwWindow;

public:


	void run()
	{
		InitWindow();
		InitVulkan();
		Update();
		CleanUp();
	}

private:

	void InitWindow()
	{
		glfwInit();
		//Turn off openGL context creation
		glfwWindowHint(GLFW_OPENGL_API, GLFW_NO_API);
		//Turn off window resizing for now
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindow = glfwCreateWindow(width, height, "Vulkan App", nullptr, nullptr);

	}

	void InitVulkan()
	{

	}

	void Update()
	{
		while (!glfwWindowShouldClose(glfwWindow))
		{
			glfwPollEvents();
		}
	}

	void CleanUp()
	{

	}

	
};