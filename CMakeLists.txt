cmake_minimum_required(VERSION 3.8)

project(Shooting2D)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(app ${PROJECT_SOURCES})

find_package(PkgConfig)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLM REQUIRED glm)
target_include_directories(app PRIVATE
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
	/usr/local/include # For SOIL
)

target_link_directories(app PRIVATE
	${GLEW_LIBRARY_DIRS}
	/usr/local/lib # For SOIL
)

# For SOIL
find_library(COCOA_FRAMEWORK Cocoa)

target_compile_features(app PUBLIC cxx_std_11)
target_compile_options(app PUBLIC -Wall -O0 -g )
target_link_libraries(app
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
	SOIL
	${COCOA_FRAMEWORK}
)

add_custom_target(copy_shaders ALL COMMAND "cp" "-r" "${CMAKE_SOURCE_DIR}/src/Shaders/" "${CMAKE_BINARY_DIR}/Shaders/")

add_custom_target(copy_assets ALL COMMAND "cp" "-r" "${CMAKE_SOURCE_DIR}/src/Assets/" "${CMAKE_BINARY_DIR}/Assets/")