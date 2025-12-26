# Specifies the minimum required version of CMake
cmake_minimum_required(VERSION 3.28.3)

set(RAYLIB_DIR /home/vboxuser/Desktop/Workspace_cpp/ciexyYVisualizer/external/raylib-5.5_linux_amd64)
set(HELPER_LIB helper)
# Defines the project name and enables C support
project(app)

set(CMAKE_C_FLAGS "-Wall -Wextra")

add_library(${HELPER_LIB} STATIC ${CMAKE_SOURCE_DIR}/src/helper.c)
target_include_directories(${HELPER_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${HELPER_LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/resources)
target_include_directories(${HELPER_LIB} PRIVATE ${RAYLIB_DIR}/include/)
target_link_directories(${HELPER_LIB} PRIVATE ${RAYLIB_DIR}/lib/)
target_link_libraries(${HELPER_LIB} PRIVATE raylib m)

# Adds an executable target named "app"
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.c)
# Link raylib static library to the executable
target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_DIR}/include/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/resources)
target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_DIR}/lib/)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE helper)



