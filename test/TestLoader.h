#ifndef TESTLOADER_H
#define TESTLOADER_H

#include <iostream>
#include "../ResourceLoader.h"
class TestLoader : public ResourceLoader
{
public:
    TestLoader();

    void* loadResources(std::string path, std::vector<std::string> params) override;
    void unloadResources(void* resource) override;
};

#endif // TESTLOADER_H