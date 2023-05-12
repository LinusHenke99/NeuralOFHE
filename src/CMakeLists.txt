cmake_minimum_required(VERSION 3.25)

add_library(NeuralOFHE
        LinTools.cpp
        MatrixFormatting.cpp

        Application.cpp
        HelperFunctions.cpp

        Operator.cpp
        Conv2D.cpp
        ReLU.cpp
        BatchNorm.cpp
)

target_include_directories(NeuralOFHE
        PUBLIC ../include
        ${OpenFHE_INCLUDE}
        ${OpenFHE_INCLUDE}/third-party/include
        ${OpenFHE_INCLUDE}/core
        ${OpenFHE_INCLUDE}/pke
        ${HDF5_INCLUDE_DIR}
)

target_link_libraries(NeuralOFHE PRIVATE
        ${OpenFHE_SHARED_LIBRARIES}
)
