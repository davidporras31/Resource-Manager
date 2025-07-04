#include "TestLoader.h"

TestLoader::TestLoader():ResourceLoader("Test")
{

}

void* TestLoader::loadResources(std::string path, std::vector<std::string> params)
{
    std::cout << "Loading resource with path: " << path << std::endl;
    for (const auto& param : params)
    {
        std::cout << "Param: " << param << std::endl;
    }
    // For demonstration purposes, we will return a simple char resource.
    return new std::string("Test Resource");
}

void TestLoader::unloadResources(void *resource)
{
    delete (std::string*)resource;
}
