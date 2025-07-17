#include "../ResourceManager.h"
#include "TestLoader.h"

int main_test()
{
    ResourceManager resourceManager;
    resourceManager.addLoader(new TestLoader());
    std::cout << resourceManager.printLoaders();
    resourceManager.addKeys("test/resources.rslf");
    std::cout << resourceManager.printKeys();
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
int policy_load_test()
{
    ResourceManager resourceManager;
    resourceManager.addLoader(new TestLoader());
    std::cout << resourceManager.printLoaders();
    resourceManager.addKeys("test/policy_load.rslf");
    std::cout << resourceManager.printKeys();

    std::cout << "Testing resource loading policies..." << std::endl;
    
    // Test loading a resource with static policy
    Resource* staticResource = resourceManager.get("static_resource");
    std::string* staticRes = staticResource->get<std::string>();
    if (staticRes)
    {
        std::cout << "Static Resource loaded: " << *staticRes << std::endl;
    }
    else
    {
        std::cout << "Failed to load static resource." << std::endl;
    }
    delete staticResource;

    // Test loading a resource with streamed policy
    Resource* streamedResource = resourceManager.get("streamed_resource");
    std::string* streamedRes = streamedResource->get<std::string>();
    if (streamedRes)
    {
        std::cout << "Streamed Resource loaded: " << *streamedRes << std::endl;
    }
    else
    {
        std::cout << "Failed to load streamed resource." << std::endl;
    }
    delete streamedResource;

    // Test loading a resource with collectible policy
    Resource* collectibleResource = resourceManager.get("collectible_resource");
    std::string* collectibleRes = collectibleResource->get<std::string>();
    if (collectibleRes)
    {
        std::cout << "Collectible Resource loaded: " << *collectibleRes << std::endl;
    }
    else
    {
        std::cout << "Failed to load collectible resource." << std::endl;
    }
    delete collectibleResource;

    std::cout << resourceManager.printKeys();

    std::cout << "Testing resource trashing..." << std::endl;
    resourceManager.trashResource(1000);
    std::cout << resourceManager.printKeys();

    resourceManager.purgeKeys();
    resourceManager.purgeLoaders();
    
    return 0;
}

int dynamic_hash_test()
{
    ResourceManager resourceManager;
    resourceManager.addLoader(new TestLoader());
    std::cout << resourceManager.printLoaders();
    resourceManager.addKeys("test/dynamic_hash.rslf");
    std::cout << resourceManager.printKeys();

    std::cout << "Testing dynamic hash..." << std::endl;
    
    std::string dynamicResourceName = "dynamic_hash_resource";
    std::cout << "Loading dynamic hash" << std::endl;
    Resource* constHashResource = resourceManager.get(dynamicResourceName.c_str());
    std::string* constHashRes = constHashResource->get<std::string>();
    if (constHashRes)
    {
        std::cout << "dynamic Hash Resource loaded: " << *constHashRes << std::endl;
    }
    else
    {
        std::cout << "Failed to load dynamic hash resource." << std::endl;
    }
    
    delete constHashResource;

    resourceManager.purgeKeys();
    resourceManager.purgeLoaders();
    
    return 0;
}

int main()
{
    std::cout << "Running main_test..." << std::endl;
    int result = main_test();
    if (result != 0)
    {
        std::cerr << "main_test failed with code: " << result << std::endl;
        return result;
    }
    std::cout << std::endl;
    
    std::cout << "Running policy_load_test..." << std::endl;
    result = policy_load_test();
    if (result != 0)
    {
        std::cerr << "policy_load_test failed with code: " << result << std::endl;
        return result;
    }
    std::cout << std::endl;

    std::cout << "Running dynamic_hash_test..." << std::endl;
    result = dynamic_hash_test();
    if (result != 0)
    {
        std::cerr << "dynamic_hash_test failed with code: " << result << std::endl;
        return result;
    }
    return 0;
}