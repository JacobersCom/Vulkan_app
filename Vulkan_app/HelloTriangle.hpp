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
	int ExCount = 0;
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
		const char** glfwRequiredExtensions;

		//Passes a array of vulkan extensions needed for glfw to create vulkan surfaces
		glfwRequiredExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

		InstanceInfo.enabledExtensionCount = glfwExtensionsCount;
		InstanceInfo.ppEnabledExtensionNames = glfwRequiredExtensions;
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
		vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionsCount, nullptr);

		//Array of extensionproperties. The size is determined by the count
		std::vector<VkExtensionProperties> extension(ExtensionCount);
		std::vector<VkExtensionProperties> glfwExtensions(glfwExtensionsCount);

		//Returns the name and version of avaliable extension
		vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, extension.data());
		vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionsCount, glfwExtensions.data());


		
		//What extensions are available through vulkan and glfw?
		
		std::cout << "avaliable extension throught vulkan and glfw" << std::endl;
		
		if (extension.size() != glfwExtensions.size())
			return;


		for (;ExCount < extension.size();)
		{
			char* ptrEx = extension[ExCount].extensionName;
			char* ptrGlfwEx = glfwExtensions[ExCount].extensionName;
				
			if (*ptrEx != '\0' && *ptrGlfwEx != '\0')
			{
				if (*ptrEx == *ptrGlfwEx)
				{
					std::cout << "Match Found!\n" << "VkExtension: " << ptrEx
						<< "\nGlfwExtension: " << ptrGlfwEx << std::endl;

					ExCount++;
				}
					
			}
		}
		std::cout << "Total extension count: " << ExCount << std::endl;
	}
};