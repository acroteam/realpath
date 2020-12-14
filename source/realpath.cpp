// "Copyright [2020] <Taraymovich Igor>"
#include "realpath.hpp"     // own header
#include <unistd.h>         // getcwd
#include <cerrno>           // errno
#include <climits>          // PATH_MAX
#include <iostream>         // std::cerr
#include <sstream>          // std::istringstream
#include <string>           // std::string
#include <vector>           //std::vector

// Splits a string str by deliminator delim.
std::vector<std::string> split(const std::string& str, char delim = '/') {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Returns current working directory.
std::string current() {
    size_t size = PATH_MAX;
    char* buffer = new char[size];
    char* err = getcwd(buffer, size);
    if (err == nullptr) {
        std::cerr << "getcwd: " << errno << std::endl;
        return "";
    }
    std::string result = buffer;
    delete[] buffer;
    return result;
}

// Makes the path absolute by adding current directory path.
std::string absolute(const std::string& path) {
    if (is_absolute(path) || is_empty(path)) {
        return path;
    }
    return current() + '/' + path;
}

// Expands dot and dot-dot elements either in existing or non-existing path.
std::string lexically_normal(const std::string& path) {
    if (is_empty(path)) {
        return path;
    }
    std::string work = absolute(path);
    std::vector<std::string> parts = split(work, '/');
    std::vector<bool> take(parts.size(), true);
    for (size_t i = 0; i < parts.size(); ++i) {
        if (parts[i] == "" || parts[i] == ".") {
            take[i] = false;
        }
        if (parts[i] == "..") {
            take[i] = false;
            for (size_t j = i; j != 0; --j) {
                if (take[j - 1]) {
                    take[j - 1] = false;
                    break;
                }
            }
        }
    }

    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (take[i]) {
            result += "/" + parts[i];
        }
    }
    return is_empty(result) ? "/" : result;
}

// Converts path p to a canonical absolute path,
// i.e. an absolute path that has no dot, dot-dot elements
// or symbolic links in its generic format representation.
// If path is not an absolute path,
// the function behaves as if it is first made absolute by absolute(path).
std::string canonical(const std::string& path) {
    if (is_empty(path)) {
        return path;
    }
    std::string work = absolute(path);
    size_t size = PATH_MAX;
    char* buffer = new char[size];
    char* err = realpath(work.c_str(), buffer);
    if (err == nullptr) {
        std::cerr << "realpath(" << work << "): " << errno << std::endl;
        return "";
    }
    std::string result = buffer;
    delete[] buffer;
    return result;
}

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
std::string weakly_canonical(const std::string& path) {
    if (is_empty(path)) {
        return path;
    }
    std::string result = "/";
    std::string work = absolute(path);
    std::vector<std::string> parts = split(work, '/');

    bool scan = true;
    for (std::string part : parts) {
        if (part == "") {
            continue;
        }
        if (scan) {
            std::string tmp = result + "/" + part;
            if (exists(tmp)) {
                result = tmp;
            } else {
                scan = false;
                if (!is_empty(result)) {
                    result = canonical(result) + "/" + part;
                }
            }
        } else {
            result += "/" + part;
        }
    }

    if (scan) {
        result = canonical(result);
    } else {
        result = lexically_normal(result);
    }
    return result;
}
