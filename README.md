# JsonParser

This repository contains a JSON Parser implemented in C++ as a thin wrapper of the nlohmann library.

The JSON parser has been developed following Test-Driven Development (TDD).

The project can be built using CMake. The build file is 'CMakeLists.txt', which is located in the root directory.

The project has been developed and tested using Visual Studio 2019 + ReSharper C++.

TODO:

* Fix the relative paths of the JSON files for the functional tests. When using a test runner that is not ReShaper C++, the relative paths may cause some functional tests to fail. This is because some test runners consider a different current directory during execution, and this renders the relative paths invalid.