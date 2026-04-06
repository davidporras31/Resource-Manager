#ifndef RESOURCE_H
#define RESOURCE_H
#include "ResourceHandler.h"
class Resource
{
private:
    ResourceHandler* resourceHandler;
public:
    Resource(ResourceHandler* handler) : resourceHandler(handler) {resourceHandler->loanResource(); }
    ~Resource() { resourceHandler->releaseResource(); }
    /// @brief get the actual object from the resource
    /// @return a pointer to the actual object
    template<typename T>
    T* get() const { return static_cast<T*>(resourceHandler->getResource()); }
};
#endif // RESOURCE_H