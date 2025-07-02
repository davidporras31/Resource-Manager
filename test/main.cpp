#include "../ResourceManager.h"
#include "TestLoader.h"

int main()
{
    ResourceManager resourceManager;
    resourceManager.addLoader(new TestLoader());
    resourceManager.printLoaders();
    resourceManager.addKeys("../test/resources.keys");
    resourceManager.printKeys();
    Resource<char>* resource = resourceManager.get<char>("example_resource");
    char* res = resource->get();
    if (res)
    {
        std::cout << "Resource loaded: " << res << std::endl;
    }
    else
    {
        std::cout << "Failed to load resource." << std::endl;
    }
    return 0;
}