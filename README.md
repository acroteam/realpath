# Realpath

Small library, containing implementation of weakly_canonical function from c++17.

It converts path to a canonical absolute path, i.e. an absolute path that has no dot, dot-dot elements or symbolic links in its generic format representation. If the argument is not an absolute path, the function behaves as if it is first made absolute by adding current directory path in the beginning. If the path doesn't exist, function processes firstly the existing part of the path, expanding dot, dot-dot elements and symbolic links. Then, it concatenates the rest of the path, expanding dot and dot-dot elements.

## Build

To build, just use

```(bash)
make
```

It will compile all sources to one executive `build/realpath`. If you want to build sources to library, use

```(bash)
make lib
```

It will create a shared library `lib/librealpath.so`, that you can use with header `include/realpath.hpp`.

## Usage

If you built project to executive, just use

```(bash)
build/realpath <path>
```

replacing `<path>` with the path you need to expand.

## Functionality

The library contains a few useful functions:

* `bool is_absolute(const std::string& path)` - checks whether the given path is absolute;
* `bool is_empty(const std::string& path)` - checks whether the given path is empty;
* `bool exists(const std::string& path)` - checks whether the file with given path exists;
* `std::string current()` - returns current working directory;
* `std::string absolute(const std::string& path)` - makes the path absolute by adding current directory path;
* `std::string canonical(const std::string& path)` - works as weakly_canonical, but without processing the non-existing paths;
* `std::string weakly_canonical(const std::string& path)` - described above.
