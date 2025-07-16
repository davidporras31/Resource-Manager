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
#include "hash.h"

// rslf: ReSource List File
// file format:
// version, version number
// key, loader, loading policy, path, [params...] 
class ResourceManager
{
private:
    std::map<hash_t,ResourceLoader*> loaders;
    std::map<hash_t,ResourceHandler*> data;
    static std::string getNextValue(std::string& txt);
    static bool isHeaderValid(std::string& line);
public:
    ~ResourceManager();
    /// @brief adds a loader to the resource manager
    /// @details The loader name must be unique, otherwise it will be overwritten.
    /// @param loader the loader to add
    /// @note The loader will be deleted when the resource manager is destroyed.
    void addLoader(ResourceLoader* loader);
    void printLoaders();
    void purgeLoaders();

    /// @brief adds keys from a file rslf (ReSource List File)
    /// @param path file path to the rslf file
    void addKeys(std::string path);
    /// @brief removes a key from the resource manager
    /// @param key the key to remove
    void removeKey(const std::string& key);
    void printKeys();
    /// @brief removes all keys from a specific rslf file
    /// @param path the path to the rslf file
    void purgeKeysFromPath(const std::string& path);
    /// @brief removes all keys from a specific loader
    /// @param loaderName the name of the loader
    void purgeKeysFromLoader(const std::string& loaderName);
    void purgeKeys();

    /// @brief destroys all resources in the trash of all loaders
    /// @param timeout the time in milliseconds before the function stops trying to destroy resources
    /// @details This function will try to destroy resources in the trash of all loaders until the timeout is reached.
    /// If the timeout is reached, the function will return and stop trying to destroy resources.
    void trashResource(clock_t timeout);

    /// @brief gets a resource by its name
    /// @param name the name of the resource
    /// @return a pointer to the resource, or exception if the resource is not found
    /// @note The resource will be loaded if it is not already loaded.
    /// remember to delete the resource when you are done with it.
    Resource* get(const char* name);
    Resource* getFromHash(const hash_t& hash);
};

#endif // RESOURCEMANAGER_H