#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

class HelloTriangle
{
private:

	int width = 700, height = 700;
	GLFWwindow* glfwWindow;

	//Handle to instance
	VkInstance Instance;

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
		//Connects the vulkan lib to my applcation
		CreateInstance();
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
		vkDestroyInstance(Instance, nullptr);

		glfwDestroyWindow(glfwWindow);

		glfwTerminate();
	}

	void CreateInstance()
	{
		//sType can't be null

		//Information about the applcation
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Vulkan app";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		//Information about the created Instanced
		VkInstanceCreateInfo InstanceInfo{};
		InstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		InstanceInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionsCount = 0;
		const char** glfwExtensions;

		//Passes a array of vulkan extensions needed for glfw to create vulkan surfaces
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

		InstanceInfo.enabledExtensionCount = glfwExtensionsCount;
		InstanceInfo.ppEnabledExtensionNames = glfwExtensions;
		//Count of enabled validation layers
		InstanceInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&InstanceInfo, nullptr, &Instance);

		if (result != VK_SUCCESS)
		{
			std::runtime_error("ERROR::Failed to create VkInstance");
		}

		uint32_t ExtensionCount = 0;

		//total number of avaliable extensions
		vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, nullptr);

		//Array of extensionproperties. The size is determined by the count
		std::vector<VkExtensionProperties> extension(ExtensionCount);

		//Returns the name and version of avaliable extension
		vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, extension.data());

		std::cout << "avaliable extension" << std::endl;

		for (const auto& ex : extension)
		{
			std::cout << ex.extensionName << "avaliable" << std::endl;
		}
		
		//The start of checking if the all the glfw extension match the 
		//Vkextensionproperties
		for (int i = 0; i < ExtensionCount; i++)
		{
			std::cout << glfwExtensions[i] << "\n" << std::endl;
		}

	}
	
};