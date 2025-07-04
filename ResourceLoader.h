#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <string>
#include <vector>

class ResourceLoader {
public:
    ResourceLoader(std::string name);
    virtual ~ResourceLoader() = default;

    virtual void* loadResources(std::string path, std::vector<std::string> params)= 0;
    virtual void unloadResources(void* resource) = 0;
    std::string getName();
    size_t getId() const {
        return id;
    }

private:
    std::string name;
    size_t id;
};

#endif // RESOURCELOADER_H