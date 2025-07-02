#ifndef TESTLOADER_H
#define TESTLOADER_H

#include <iostream>
#include <any>
#include "../ResourceLoader.h"
class TestLoader : public ResourceLoader
{
public:
    TestLoader();
    ~TestLoader();

    Resource<std::any>* loadResources(std::string key, std::string path, std::vector<std::string> params);
};

#endif // TESTLOADER_H