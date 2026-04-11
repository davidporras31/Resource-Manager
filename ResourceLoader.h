#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <string>
#include <deque>
#include <algorithm>
#include "hash.h"
#include "DynamicArray.h"

class ResourceLoader {
public:
    ResourceLoader(const char* name);
    virtual ~ResourceLoader() = default;

    /// @brief loads resources from a given path with optional parameters
    /// @param path the path to the resource file
    /// @param params optional parameters for loading the resource
    /// @return a pointer to the loaded resource, or nullptr if loading failed
    virtual void* loadResources(std::string path, DynamicArray<std::string>* params)= 0;
    /// @brief unloads a resource
    /// @param resource the resource to unload
    /// @details This function should be implemented to properly release the resource.
    /// It is called when the resource is no longer needed.
    virtual void unloadResources(void* resource) = 0;

    void addToTrash(void* resource);
    void removeFromTrash(void* resource);
    std::deque<void*>& getTrash() {
        return trash;
    }

    std::string getName();
    hash_t getId() const {
        return id;
    }

private:
    std::string name;
    hash_t id;
    std::deque<void*> trash;
};

#endif // RESOURCELOADER_H