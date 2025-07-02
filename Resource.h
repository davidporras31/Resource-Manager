#ifndef RESOURCE_H
#define RESOURCE_H

template <typename T>
class Resource
{
private:
    T* resource;
public:
    Resource(T* resource) : resource(resource) {}
    T* get() const { return resource; }

};
#endif // RESOURCE_H