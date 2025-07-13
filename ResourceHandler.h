#ifndef RESOURCE_HANDLER_H
#define RESOURCE_HANDLER_H

#include <atomic>
#include <cstddef>
#include "ResourceLoader.h"

class ResourceHandler {
public:
    ResourceHandler(ResourceLoader* loader, const std::string& path, const std::vector<std::string>& params, size_t initialCount = 0, bool collectible = false);
    ~ResourceHandler();

    void releaseResource();
    void loanResource();

    void loadResource();
    void unloadResource();

    void reloadResource();
    
    size_t getLoaderId();
    void* getResource();

    bool isCollectible() const;
    bool isCollected() const;
    size_t getResourceCount() const;

private:
    std::atomic<size_t> resourceCount;
    bool collectible, collected;
    void* resource; // Pointer to the actual resource
    ResourceLoader* loader; // Pointer to the loader that manages this resource
    std::string path;
    std::vector<std::string> params;
};

#endif // RESOURCE_HANDLER_H