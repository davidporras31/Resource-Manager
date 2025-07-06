#include "../ResourceManager.h"
#include "TestLoader.h"

int main()
{
    ResourceManager resourceManager;
    resourceManager.addLoader(new TestLoader());
    resourceManager.printLoaders();
    resourceManager.addKeys("test/resources.keys");
    resourceManager.printKeys();
    Resource* resource = resourceManager.get("example_resource");
    std::string* res = resource->get<std::string>();
    if (res)
    {
        std::cout << "Resource loaded: " << *res << std::endl;
    }
    else
    {
        std::cout << "Failed to load resource." << std::endl;
    }
    resourceManager.purgeKeys();
    resourceManager.purgeLoaders();
    return 0;
}