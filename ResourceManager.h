#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <chrono>
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
    void printLoaders();
    void purgeLoaders();

    void addKeys(std::string path);
    void removeKey(const std::string& key);
    void printKeys();
    void purgeKeysFromPath(const std::string& path);
    void purgeKeysFromLoader(const std::string& loaderName);
    void purgeKeys();

    void trashResource(clock_t time);

    Resource* get(const std::string& name);
};

#endif // RESOURCEMANAGER_H