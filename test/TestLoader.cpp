#include "TestLoader.h"

TestLoader::TestLoader():ResourceLoader("Test")
{

}

Resource<std::any>* TestLoader::loadResources(std::string key, std::string path, std::vector<std::string> params)
{
    std::cout << "Loading resource with key: " << key << ", path: " << path << std::endl;
    for (const auto& param : params)
    {
        std::cout << "Param: " << param << std::endl;
    }
    // For demonstration purposes, we will return a simple char resource.
    return (Resource<std::any>*)new Resource<char>(new char[14]{'T', 'e', 's', 't', ' ', 'R', 'e', 's', 'o', 'u', 'r', 'c', 'e', '\0'});
}