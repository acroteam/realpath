// "Copyright [2020] <Taraymovich Igor>"
#ifndef INCLUDE_REALPATH_HPP_
#define INCLUDE_REALPATH_HPP_
#include <fstream>  // std::ifstream
#include <string>   // std::string

// Checks whether the given path is absolute.
inline bool is_absolute(const std::string& path) {
    return path[0] == '/';
}

// Checks whether the given path is empty.
inline bool is_empty(const std::string& path) {
    return path.size() == 0;
}

// Checks whether the file with given path exists.
inline bool exists(const std::string& path) {
    return std::ifstream(path).good();
}

// Returns current working directory.
std::string current();

// Makes the path absolute by adding current directory path.
std::string absolute(const std::string& path);

// Converts path p to a canonical absolute path,
// i.e. an absolute path that has no dot, dot-dot elements
// or symbolic links in its generic format representation.
// If path is not an absolute path,
// the function behaves as if it is first made absolute by absolute(path).
std::string canonical(const std::string& path);

// Converts path p to a canonical absolute path,
// i.e. an absolute path that has no dot, dot-dot elements
// or symbolic links in its generic format representation.
// If path is not an absolute path,
// the function behaves as if it is first made absolute by absolute(path).
// If the path doesn't exist,
// function processes firstly the existing part of the path,
// expanding dot, dot-dot elements and symbolic links.
// Then, it concatenates the rest of the path,
// expanding dot and dot-dot elements.
std::string weakly_canonical(const std::string& path);

#endif  // INCLUDE_REALPATH_HPP_
