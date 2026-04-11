#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <vector>

/// @brief A dynamic array implementation.
/// @tparam T The type of elements stored in the array.
template <typename T>
class DynamicArray
{
private:
    size_t size;
    T *data;
public:
    DynamicArray(const std::vector<T> &params)
    : size(params.size()), data(new T[params.size()])
    {
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = params.operator[](i);
        }
    }
    DynamicArray(const DynamicArray &other) = delete;

    ~DynamicArray()
    {
        delete[] data;
    }

    size_t getSize() const
    {
        return size;
    }

    T &operator[](size_t index)
    {
        return data[index];
    }

    const T &operator[](size_t index) const
    {
        return data[index];
    }
};

#endif // DYNAMIC_ARRAY_H