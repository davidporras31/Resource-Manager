#include "ResourceManager.h"

void ResourceManager::addLoader(ResourceLoader* loader)
{
    this->loaders[std::hash<std::string>()(loader->getName())] = loader;
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
    std::string version_txt = "version", version= "1.0";
    if(version_txt != getNextValue(line))
    {
        std::cerr << "Invalid version header in file: " << path << std::endl;
        return;
    }
    if(version != getNextValue(line))
    {
        std::cerr << "Invalid version in file: " << path << std::endl;
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
        Resource<std::any>* resource = this->loaders.at(std::hash<std::string>()(loader))->loadResources(key, path, params);
        if (resource != nullptr)
        {
            size_t hash = std::hash<std::string>()(key);
            this->data[hash] = resource;
        }
    }
    
}
std::string ResourceManager::getNextValue(std::string& txt)
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