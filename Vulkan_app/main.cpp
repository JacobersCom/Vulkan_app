#include "HelloTriangle.hpp"

#include <iostream>

int main() {
    
    HelloTriangle app;

    try 
    {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}