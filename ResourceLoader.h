#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <string>
#include <vector>
#include <any>
#include "Resource.h"

class ResourceLoader {
public:
    ResourceLoader(std::string name);
    ~ResourceLoader();

    // Add public methods here
    virtual Resource<std::any>* loadResources(std::string key, std::string path, std::vector<std::string> params)= 0;
    std::string getName();

private:
    // Add private members here
    std::string name;
};

#endif // RESOURCELOADER_H