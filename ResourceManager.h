#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <any>
#include <fstream>
#include "Resource.h"
#include "ResourceLoader.h"

class ResourceManager
{
private:
    std::map<size_t,ResourceLoader*> loaders;
    std::map<size_t,Resource<std::any>*> data;
    static std::string getNextValue(std::string& txt);
public:
    void addLoader(ResourceLoader* loader);
    void printLoaders()
    {
        for (const auto& loader : loaders)
        {
            std::cout << "Loader: " << loader.second->getName() << std::endl;
        }
    }
    void addKeys(std::string path);
    void printKeys()
    {
        for (const auto& entry : data)
        {
            std::cout << "Key: " << entry.first << std::endl;
        }
    }
    template <typename T>
    Resource<T>* get(const std::string& name);
};
template <typename T>
Resource<T>* ResourceManager::get(const std::string& name)
{
    std::hash<std::string> hasher;
    size_t hash = hasher(name);
    return (Resource<T>*)data.at(hash);
}

#endif // RESOURCEMANAGER_H