#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
    this->purgeLoaders();
    this->purgeKeys();
}

void ResourceManager::addLoader(ResourceLoader* loader)
{
    this->loaders[hash(loader->getName().c_str())] = loader;
}
std::string ResourceManager::printLoaders()
{
    std::string output;
    output += "Loaders:\n";
    for (const auto& loader : loaders)
    {
        output += loader.second->getName() += " (ID: " + std::to_string(loader.second->getId()) += ")\n";
    }
    return output;
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
        throw fileNotFoundException(path);
    }

    //get version
    std::getline(stream,line);
    if (!isHeaderValid(line))
    {
        throw versionMismatchException(path);
    }

    while (std::getline(stream,line))
    {
        std::string key, loader, loading_policy, path;
        std::vector<std::string> params;
        key = getNextValue(line);
        loader = getNextValue(line);
        loading_policy = getNextValue(line);
        if(loading_policy != "static" && loading_policy != "streamed" && loading_policy != "collected")
        {
            loading_policy = "streamed";
        }
        path = getNextValue(line);
        while (line != "")
        {
            params.push_back(getNextValue(line));
        }
        hash_t hashValue = hash(key.c_str());
        this->data[hashValue] = new ResourceHandler(this->loaders[hash(loader.c_str())], path, params,
                                                loading_policy == "static" ? 1 : 0, loading_policy == "collected");
    }
    
}
std::string ResourceManager::printKeys()
{
    std::string output;
    output += "Keys:\n";
    for (const auto& entry : data)
    {
        output += std::to_string(entry.first) + ", Loader ID: " + std::to_string(entry.second->getLoaderId())
                += ", Resource Count: " + std::to_string(entry.second->getResourceCount())
                += ", Collectible: " + std::string(entry.second->isCollectible() ? "Yes" : "No")
                += ", Collected: " + std::string(entry.second->isCollected() ? "Yes" : "No")
                += ", Loaded: " + std::string(entry.second->getResource() ? "Yes" : "No")
                += "\n";
    }
    return output;
}
void ResourceManager::removeKey(const std::string &key)
{
    hash_t hashValue = hash(key.c_str());
    auto it = this->data.find(hashValue);
    if (it != this->data.end())
    {
        delete it->second;
        this->data.erase(it);
    }
}
void ResourceManager::purgeKeysFromLoader(const std::string &loaderName)
{
    hash_t loaderHash = hash(loaderName.c_str());
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
        throw fileNotFoundException(path);
    }
    //get version
    std::getline(stream,line);
    if( !isHeaderValid(line))
    {
        throw versionMismatchException(path);
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
void ResourceManager::trashResource(clock_t timeout)
{
    // from sfml clock.hpp
    using clock = std::conditional_t<
        std::chrono::high_resolution_clock::is_steady,
        std::chrono::high_resolution_clock,
        std::chrono::steady_clock
    >;
    auto endTime = clock::now() + std::chrono::milliseconds(timeout);
    for(auto it = loaders.begin(); it != loaders.end(); ++it)
    {
        ResourceLoader* loader = it->second;
        auto& trash = loader->getTrash();
        size_t size = trash.size();
        bool stop = false;
        for (size_t i = 0; i < size; ++i)
        {
            void* resource = trash.front();
            trash.pop_front();
            ResourceHandler* handler = static_cast<ResourceHandler*>(resource);
            handler->collect();
            handler->unloadResource();
            if(i == size - 1 || i % 10 == 0)
            {
                if (clock::now() >= endTime)
                {
                    stop = true;
                    break;
                }
            }
        }
        if(stop)
            break;
    }
}
Resource *ResourceManager::get(const char* name)
{
    return getFromHash(hash(name));
}
Resource *ResourceManager::getFromHash(const hash_t &hash)
{
    return new Resource(this->data[hash]);
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
    std::string version_txt = "version", version= "1.1";
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
