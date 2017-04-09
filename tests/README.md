#Project 1 Testing

# What files to copy

Please copy the following **student** files into the **src** directory:

- BinarySearchTree.h, Set.h


# How to execute the Testing Executable

1. Compile the Cmake files using the instructions on the repo README.
2. Run `./RunBSTProjectTests`

# I got an error reporting a file not found

This is because the CMake project was compiled by a different TA and the CMakeLists.txt was not re-executed.

This is what the error looks like:

``` bash
> $ make                                                         [±master ●●]
> /bin/sh: line 0: cd: /Users/scott/Documents/CSE-331-UnitTesting/Hw2: No such file or directory
> make[2]: *** [ext/gtest/CMakeFiles/gtest.dir/depend] Error 1
> make[1]: *** [ext/gtest/CMakeFiles/gtest.dir/all] Error 2
> make: *** [all] Error 2
```

To fix it, simply run:

```bash
./cmake_clean
```
