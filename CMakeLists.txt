cmake_minimum_required(VERSION 3.16.5)
project(BentoCL)
set(CMAKE_CXX_STANDARD 11)

MESSAGE(Compiler: \ ${CMAKE_CXX_COMPILER_ID} \ ${CMAKE_CXX_COMPILER_VERSION})
MESSAGE(CMake\ Version: \ ${CMAKE_VERSION})

# Setup OpenCL
if(DEFINED OCL_ROOT AND DEFINED CUDA_PATH)
    MESSAGE("Both AMD and NVIDIA OpenCL SDKs have been found. Defaulting to AMD.")
endif()
if (DEFINED OCL_ROOT)
    MESSAGE("Building with AMD OpenCL SDK.")
    # Set required OpenCL CMake build options.
    set(OpenCL_INCLUDE_DIR ${OCL_ROOT}/include/)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64 bits
        set(OpenCL_LIBRARY ${OCL_ROOT}/lib/x86_64/OpenCL.lib)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # 32 bits
        set(OpenCL_LIBRARY ${OCL_ROOT}/lib/x86/OpenCL.lib)
    endif()

    # Add OpenCL stuff.
    find_package(OpenCL REQUIRED)
    #add_library(OpenCL ${OpenCL_LIBRARY})
    include_directories(${OpenCL_INCLUDE_DIR})
    #SET_TARGET_PROPERTIES(OpenCL PROPERTIES LINKER_LANGUAGE C)
elseif(DEFINED CUDA_PATH)
    MESSAGE("Building with NVIDIA OpenCL SDK (CUDA Toolkit).")
    set(OpenCL_INCLUDE_DIR ${CUDA_PATH}/include/)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # 64 bits
        set(OpenCL_LIBRARY ${CUDA_PATH}/lib/x64/OpenCL.lib)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # 32 bits
        set(OpenCL_LIBRARY ${CUDA_PATH}/lib/Win32/OpenCL.lib)
    endif()


    # Add OpenCL stuff.
    find_package(OpenCL REQUIRED)
    #add_library(OpenCL ${OpenCL_LIBRARY})
    include_directories(${OpenCL_INCLUDE_DIR})
    #SET_TARGET_PROPERTIES(OpenCL PROPERTIES LINKER_LANGUAGE C)
else()
    MESSAGE(OCL_ROOT\ not\ found.)
    find_package(OpenCL REQUIRED)
    set(OpenCL_LIBRARY OpenCL::OpenCL)
endif()


# Allow PROJECT_DIR to be used in C source files
add_compile_definitions(PROJECT_DIR="${PROJECT_SOURCE_DIR}/src/")

# General source files

file(GLOB_RECURSE main_SOURCE_FILES
        "src/util/*.h" "src/util/*.c"
)

file(GLOB_RECURSE run_SOURCE_FILES src/run/main.c)
add_executable(main ${main_SOURCE_FILES} ${run_SOURCE_FILES})
target_link_libraries(main ${OpenCL_LIBRARY})
