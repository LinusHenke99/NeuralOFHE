cmake_minimum_required(VERSION 3.25)
project(NeuralOFHE)
set(CMAKE_CXX_STANDARD 17)

# Setting up OpenFHE
option( BUILD_STATIC OFF)
find_package(OpenFHE REQUIRED)
set( CMAKE_CXX_FLAGS ${OpenFHE_CXX_FLAGS} )
link_directories( ${OpenFHE_LIBDIR} )
set( CMAKE_EXE_LINKER_FLAGS ${OpenFHE_EXE_LINKER_FLAGS} )
link_libraries( ${OpenFHE_SHARED_LIBRARIES} )

add_subdirectory(src)

add_executable(test test.cpp)
target_link_libraries(test NeuralOFHE)