#include "ResourceHandler.h"

ResourceHandler::ResourceHandler(ResourceLoader *loader, const std::string &path, const std::vector<std::string> &params, size_t initialCount, bool collectible)
: resourceCount(initialCount), collectible(collectible), collected(false), resource(nullptr), loader(loader), path(path), params(params)
{
    if(initialCount > 0) reloadResource();
}
ResourceHandler::~ResourceHandler()
{
    this->unloadResource();
}
void ResourceHandler::releaseResource()
{
    if (--resourceCount == 0)
    {
        if(resource)
        {
            if (collectible)
            {
                loader->addToTrash(this);
                collected = true;
            }
            else
            {
                // If not collectible, unload the resource immediately
                loader->unloadResources(resource);
                resource = nullptr; // Clear the resource pointer to avoid dangling pointers
            }
        }
    }
}

void ResourceHandler::loanResource()
{
    this->loadResource();
    if(collected)
    {
        loader->removeFromTrash(this);
        collected = false;
    }
    resourceCount.fetch_add(1);
}

void ResourceHandler::reloadResource()
{
    this->unloadResource();
    this->loadResource();
}

void ResourceHandler::loadResource()
{
    if (!resource)
    {
        resource = loader->loadResources(path, params);
    }
}

void ResourceHandler::unloadResource()
{
    if(collected)
    {
        loader->removeFromTrash(this);
        collected = false;
    }
    if (resource)
    {
        loader->unloadResources(resource);
        resource = nullptr; // Clear the resource pointer to avoid dangling pointers
    }
}

size_t ResourceHandler::getLoaderId()
{
    return loader->getId();
}

void *ResourceHandler::getResource()
{
    return resource;
}

bool ResourceHandler::isCollectible() const
{
    return collectible;
}

bool ResourceHandler::isCollected() const
{
    return collected;
}

size_t ResourceHandler::getResourceCount() const
{
    return resourceCount.load(std::memory_order_relaxed);
}
