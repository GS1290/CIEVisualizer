# Specifies the minimum required version of CMake
cmake_minimum_required(VERSION 3.28.3)

if (WIN32)
    message(STATUS "Windows build")
    set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib-5.5_win64_msvc16)
else()
    message(STATUS "Linux build")
    set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib-5.5_linux_amd64)
endif()
set(HELPER_LIB helper)
# Defines the project name and enables C support
project(app C)

# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUC)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_C_FLAGS "-Wall -Wextra")
endif()

add_library(${HELPER_LIB} STATIC ${CMAKE_SOURCE_DIR}/src/helper.c)
target_include_directories(${HELPER_LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${HELPER_LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/resources)
target_include_directories(${HELPER_LIB} PRIVATE ${RAYLIB_DIR}/include)
target_link_directories(${HELPER_LIB} PRIVATE ${RAYLIB_DIR}/lib)
if (WIN32)
    target_link_libraries(${HELPER_LIB} PRIVATE raylib.lib winmm.lib)
else()
    target_link_libraries(${HELPER_LIB} PRIVATE libraylib.a m)
endif()


# Adds an executable target named "app"
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.c)
# Link raylib static library to the executable
target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/resources)
target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE helper)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib.lib winmm.lib)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE libraylib.a)
endif()




