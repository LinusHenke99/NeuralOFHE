# NeuralOFHE
A C++ library that implements machine learning Operators, so that they can be used 
with the [OpenFHE](https://github.com/openfheorg/openfhe-development) library.

## Dependencies
- [CMake 3.25 or newer](https://cmake.org/)
- [OpenFHE](https://github.com/openfheorg/openfhe-development)

## Installation
This project is simply installed using CMake, which is done by executing the following commands in the cloned directory.
```
mkdir build && cd build
cmake ..
make
make install
```
The `make install` step will probably require sudo privileges.