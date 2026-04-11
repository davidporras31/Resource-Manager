#include "TestLoader.h"

TestLoader::TestLoader():ResourceLoader("Test")
{

}

void* TestLoader::loadResources(std::string path, DynamicArray<std::string>* params)
{
    std::cout << "Loading resource with path: " << path << std::endl;
    for (size_t i = 0; i < params->getSize(); ++i)
    {
        std::cout << "Param: " << (*params)[i] << std::endl;
    }
    // For demonstration purposes, we will return a simple char resource.
    return new std::string("Test Resource");
}

void TestLoader::unloadResources(void *resource)
{
    std::cout << "Unloading resource." << std::endl;
    delete (std::string*)resource;
}
