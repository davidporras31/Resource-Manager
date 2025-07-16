#include "ResourceLoader.h"

ResourceLoader::ResourceLoader(const char* name):name(name), id(hash(name))
{

}

void ResourceLoader::addToTrash(void* resource)
{
    this->trash.push_back(resource);
}
void ResourceLoader::removeFromTrash(void* resource)
{
    auto it = std::find(this->trash.begin(), this->trash.end(), resource);
    if (it != this->trash.end())
    {
        this->trash.erase(it);
    }
}

std::string ResourceLoader::getName()
{
    return this->name;
}