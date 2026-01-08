# Vulkan_app

## Goal
- I didn't feel school was teaching vulkan well, so I when off and started learning it on my own as well. This repo will include my own examples as well as examples from the Vulkan Tutorial.

### Chapter one
- Created a Vulkan instance for my applcation. This is the connection between the vulkan libary and your applcation, also you propvide details about your applcation to the driver during this creation.
- Vulkan information is mainly passed throught structs instead of function parameters.
- sType is apart of all Vulkan structure. This value is used to define what type of structure is being passed to the driver
- pAllocte is used for passing callback function into Vulkan functions
- You can retrieve a list of supported extensions before creating your Vulkan instance
- Should also call ``VkDestoryInstance`` after a program is done running

### Chapter two
- Finished challenge from chapter one, which checks which extension are avaiable through glfw, and vulkan.h
- Enabled validation layer support. C++ has a macro to check if the program is in debug. If so validation layer support is enabled, but if layer support is for some reason not avaiable the program will throw a runtime error.
- TBC
