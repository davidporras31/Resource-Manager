#ifndef HASH_H
#define HASH_H
#include <cstdint>
#include <cstring>


typedef unsigned long long hash_t;
/// @brief Computes a hash for a given string using FNV-1a algorithm.
/// @param str The input string to hash.
/// @return The computed hash value as a hash_t.
constexpr hash_t hash(const char * str) {
    hash_t hash = 14695981039346656037ull;
    size_t size = strlen(str);
    for (size_t i = 0; i < size; ++i) {
        hash ^= static_cast<uint8_t>(*(str + i));
        hash *= 1099511628211ull;
    }
    return hash;
}
#endif // HASH_H