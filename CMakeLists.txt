cmake_minimum_required(VERSION 3.25)
project(NeuralOFHE VERSION 0.1 DESCRIPTION "A library that implements wrappers around the OpenFHE library, in order to make inference on Ciphertexts")
set(CMAKE_CXX_STANDARD 17)

# Setting up OpenFHE
option( BUILD_STATIC OFF)
find_package(OpenFHE REQUIRED)
set( CMAKE_CXX_FLAGS ${OpenFHE_CXX_FLAGS} )
link_directories( ${OpenFHE_LIBDIR} )
set( CMAKE_EXE_LINKER_FLAGS ${OpenFHE_EXE_LINKER_FLAGS} )
link_libraries( ${OpenFHE_SHARED_LIBRARIES} )

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/install)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        #   Sources of the private include files
        src/LinTools.cpp
        src/MatrixFormatting.cpp

        #   Sources concerning application building
        src/Application.cpp
        src/HelperFunctions.cpp

        #   Sources that define the ML Operations on the Ciphertext
        src/Operator.cpp
        src/Activation.cpp
        src/Conv2D.cpp
        src/ReLU.cpp
        src/BatchNorm.cpp
        src/AveragePool.cpp
        src/Gemm.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${OpenFHE_INCLUDE}
        ${OpenFHE_INCLUDE}/third-party/include
        ${OpenFHE_INCLUDE}/core
        ${OpenFHE_INCLUDE}/pke
        ${HDF5_INCLUDE_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${OpenFHE_SHARED_LIBRARIES}
        )

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ../NeuralOFHE.h)
if (DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
            STATUS
            "CMAKE_INSTALL_PREFIX is not set\n"
            "Default value: ${CMAKE_INSTALL_PREFIX}\n"
            "Will set it to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX )
else()
    message(
            STATUS
            "CMAKE_INSTALL_PREFIX was already set\n"
            "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

include(GNUInstallDirs)

set(public_headers
    NeuralOFHE.h
    include/Activation.h
    include/Application.h
    include/AveragePool.h
    include/BatchNorm.h
    include/Conv2D.h
    include/Gemm.h
    include/HelperFunctions.h
    include/InherOperators.h
    include/Operator.h
    include/ReLU.h
)

foreach (header ${public_headers})
    file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}" "${header}")
    get_filename_component(header_directory_path "${header_file_path}" DIRECTORY)
    install(
        FILES ${header}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}"
    )
endforeach ()

install(TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}Targets"
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
