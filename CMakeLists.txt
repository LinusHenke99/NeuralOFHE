cmake_minimum_required(VERSION 3.25)
project(NeuralOFHE VERSION 0.1 DESCRIPTION "A library that implements wrappers around the OpenFHE library, in order to make inference on Ciphertexts")
set(CMAKE_CXX_STANDARD 17)

# Setting up OpenFHE
option( BUILD_STATIC OFF)
find_package(OpenFHE REQUIRED)
set( CMAKE_CXX_FLAGS "-fPIC ${OpenFHE_CXX_FLAGS}" )
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
        src/GeneralLinearOperator.cpp
        src/Activation.cpp
        src/Conv2D.cpp
        src/ReLU.cpp
        src/BatchNorm.cpp
        src/AveragePool.cpp
        src/Gemm.cpp
        src/SiLU.cpp
        src/Sigmoid.cpp
        src/BootStrapping.cpp
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

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/NeuralOFHE/NeuralOFHE.h)
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
        include/NeuralOFHE/Operators/Activation.h
        include/NeuralOFHE/Application.h
        include/NeuralOFHE/Operators/AveragePool.h
        include/NeuralOFHE/Operators/BatchNorm.h
        include/NeuralOFHE/Operators/Conv2D.h
        include/NeuralOFHE/Operators/Gemm.h
        include/NeuralOFHE/Helperfunctions/HelperFunctions.h
        include/NeuralOFHE/Operators/InherOperators.h
        include/NeuralOFHE/Operators/Operator.h
        include/NeuralOFHE/Operators/GeneralLinearOperator.h
        include/NeuralOFHE/Operators/ReLU.h
        include/NeuralOFHE/Operators/SiLU.h
        include/NeuralOFHE/Operators/Sigmoid.h
		include/NeuralOFHE/Operators/BootStrapping.h
		include/NeuralOFHE/Operators/PadOperator.h
)

foreach (header ${public_headers})
    file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}" "${CMAKE_SOURCE_DIR}/${header}")
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

# generate and install export file
install(EXPORT "${PROJECT_NAME}Targets"
        FILE "${PROJECT_NAME}Targets.cmake"
        NAMESPACE ${namespace}::
        DESTINATION cmake
        )

include(CMakePackageConfigHelpers)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
)
# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION cmake
        )
# install config files
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION cmake
        )
# generate the export targets for the build tree
export(EXPORT "${PROJECT_NAME}Targets"
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
        NAMESPACE ${namespace}::
        )
