#include "ResourceLoader.h"

ResourceLoader::ResourceLoader(std::string name):name(name)
{

}

std::string ResourceLoader::getName()
{
    return this->name;
}