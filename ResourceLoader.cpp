#include "ResourceLoader.h"

ResourceLoader::ResourceLoader(std::string name):name(name), id(std::hash<std::string>()(name))
{

}

std::string ResourceLoader::getName()
{
    return this->name;
}