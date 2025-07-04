#include "ResourceHandler.h"

ResourceHandler::ResourceHandler(ResourceLoader *loader, const std::string &path, const std::vector<std::string> &params, size_t initialCount)
: resourceCount(initialCount), resource(nullptr), loader(loader), path(path), params(params) 
{
    if(initialCount > 0) reloadResource();
}
ResourceHandler::~ResourceHandler()
{
    if (resource)
    {
        loader->unloadResources(resource);
        resource = nullptr; // Clear the resource pointer to avoid dangling pointers
    }
}
void ResourceHandler::releaseResource()
{
    if (resourceCount.fetch_sub(1) == 0)
    {
        if(resource)
        {
            loader->unloadResources(resource);
            resource = nullptr; // Clear the resource pointer to avoid dangling pointers
        }
    }
}

void ResourceHandler::loanResource()
{
    if(!resource)
    {
        resource = loader->loadResources(path, params);
    }
    resourceCount.fetch_add(1);
}

void ResourceHandler::reloadResource()
{
    if(resource)
    {
        loader->unloadResources(resource);
    }
    resource = loader->loadResources(path, params);
}

size_t ResourceHandler::getLoaderId()
{
    return loader->getId();
}

void *ResourceHandler::getResource()
{
    return resource;
}
