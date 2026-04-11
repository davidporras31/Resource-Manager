# Resource Manager

Resource Manager is a library designed to help you efficiently allocate and manage resources for your apps.

## Features

- Add, manage, and remove resources
- remove unused resources
- load rslf(ReSource List File) files to append multiple resources at once
- custom resources loaders

## TODO
- Track resource usage and availability 
- Generate usage reports

## Keys politic
- static (always loaded)
- streamed (unloaded when not used)
- collected (cleanup when wanted)

## Usage
To use Resource Manager, simply import the library and create an instance of the ResourceManager class. You can then add resources, manage them, and remove them as needed.

```cpp
#include <iostream>
#include "ResourceManager.h"

int main() {
    ResourceManager resourceManager;

    // Add resources loader
    resourceManager.addLoader(new FooLoader());

    // Add resources keys
    resourceManager.addKeys("path/to/keys.rslf");

    // use resource
    Resource* fooResource = resourceManager.get("foo");
    std::string* foo = fooResource->get<std::string>();
    if (foo)
    {
        std::cout << "Resource loaded: " << *foo << std::endl;
    }
    else
    {
        std::cout << "Failed to load resource." << std::endl;
    }

    // return resource to the Resource Manager
    delete fooResource;

    return 0;
}
```
create custom resource loader by inheriting from ResourceLoader and implementing the load and unload methods.
```cpp
#include <iostream>
#include "ResourceLoader.h"
class FooLoader : public ResourceLoader {
public:
    void* load(std::string path, DynamicArray<std::string>* params) override {
        // Implement loading logic for Foo resource
        std::string* foo = new std::string("This is a Foo resource loaded from " + path);
        return foo;
    }

    void unload(void *resource) override {
        std::cout << "Unloading resource." << std::endl;
        delete (std::string*)resource;
    }
};
```

## Contributing

Contributions are welcome! Please open issues or submit pull requests.

## License

This project is licensed under the MIT License.