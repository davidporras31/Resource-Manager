#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
    this->purgeLoaders();
    this->purgeKeys();
}

void ResourceManager::addLoader(ResourceLoader* loader)
{
    this->loaders[std::hash<std::string>()(loader->getName())] = loader;
}
void ResourceManager::purgeLoaders()
{
    for (auto& loader : this->loaders)
    {
        delete loader.second;
    }
    this->loaders.clear();
}
void ResourceManager::addKeys(std::string path)
{
    std::ifstream stream(path);
    std::string line;
    if(!stream.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }

    //get version
    std::getline(stream,line);
    if (!isHeaderValid(line))
    {
        std::cerr << "Invalid header in file: " << path << std::endl;
        return;
    }

    while (std::getline(stream,line))
    {
        std::string key, loader, path;
        std::vector<std::string> params;
        key = getNextValue(line);
        loader = getNextValue(line);
        path = getNextValue(line);
        while (line != "")
        {
            params.push_back(getNextValue(line));
        }
        size_t hash = std::hash<std::string>()(key);
        this->data[hash] = new ResourceHandler(this->loaders[std::hash<std::string>()(loader)], path, params);
    }
    
}
void ResourceManager::removeKey(const std::string &key)
{
    size_t hash = std::hash<std::string>()(key);
    auto it = this->data.find(hash);
    if (it != this->data.end())
    {
        delete it->second;
        this->data.erase(it);
    }
}
void ResourceManager::purgeKeysFromLoader(const std::string &loaderName)
{
    size_t loaderHash = std::hash<std::string>()(loaderName);
    for (auto it = this->data.begin(); it != this->data.end(); )
    {
        if (it->second->getLoaderId() == loaderHash)
        {
            delete it->second;
            it = this->data.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
void ResourceManager::purgeKeysFromPath(const std::string& path)
{
    std::ifstream stream(path);
    std::string line;
    if(!stream.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }
    //get version
    std::getline(stream,line);
    if( !isHeaderValid(line))
    {
        std::cerr << "Invalid header in file: " << path << std::endl;
        return;
    }
    while (std::getline(stream,line))
    {
        std::string key, loader, resourcePath;
        std::vector<std::string> params;
        key = getNextValue(line);
        this->removeKey(key);
    }
}


void ResourceManager::purgeKeys()
{
    for (auto& entry : this->data)
    {
        delete entry.second;
    }
    this->data.clear();
}
Resource *ResourceManager::get(const std::string &name)
{
    std::hash<std::string> hasher;
    size_t hash = hasher(name);
    return new Resource(data.at(hash));
}
std::string ResourceManager::getNextValue(std::string &txt)
{
    size_t pos = txt.find(',');
    if (pos == std::string::npos)
    {
        std::string value = txt;
        txt.clear();
        return value;
    }
    std::string value = txt.substr(0, pos);
    txt.erase(0, pos + 1);
    return value;
}

bool ResourceManager::isHeaderValid(std::string &line)
{
    if(line.empty())
    {
        return false;
    }
    std::string version_txt = "version", version= "1.0";
    if(version_txt != getNextValue(line))
    {
        return false;
    }
    if(version != getNextValue(line))
    {
        return false;
    }   

    return true;
}
