#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "Resource.h"
#include "ResourceLoader.h"
#include "ResourceHandler.h"

class ResourceManager
{
private:
    std::map<size_t,ResourceLoader*> loaders;
    std::map<size_t,ResourceHandler*> data;
    static std::string getNextValue(std::string& txt);
    static bool isHeaderValid(std::string& line);
public:
    ~ResourceManager();
    void addLoader(ResourceLoader* loader);
    void printLoaders()
    {
        std::cout << "Loaders:" << std::endl;
        for (const auto& loader : loaders)
        {
            std::cout << loader.second->getName() << " (ID: " << loader.second->getId() << ")" << std::endl;
        }
    }
    void purgeLoaders();

    void addKeys(std::string path);
    void removeKey(const std::string& key);
    void printKeys()
    {
        std::cout << "Keys:" << std::endl;
        for (const auto& entry : data)
        {
            std::cout << entry.first << ", Loader ID: " << entry.second->getLoaderId() << std::endl;
        }
    }
    void purgeKeysFromPath(const std::string& path);
    void purgeKeysFromLoader(const std::string& loaderName);
    void purgeKeys();

    Resource* get(const std::string& name);
};

#endif // RESOURCEMANAGER_H