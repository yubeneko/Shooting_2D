cmake_minimum_required(VERSION 3.8)

project(Shooting2D)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(app ${PROJECT_SOURCES})

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(PkgConfig)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLM REQUIRED glm)
pkg_check_modules(SDL2_TTF REQUIRED sdl2_ttf)

# CMake はデフォルトで target_link_directories で指定したディレクトリを
# ターゲットの rpath に追加するので、これを無効化する
# 後に install_name_tool で半手動で rpath を追加する
set_target_properties(app PROPERTIES SKIP_BUILD_RPATH TRUE)

target_include_directories(app PRIVATE
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
	/usr/local/include # For SOIL
	${CMAKE_SOURCE_DIR}/external/FMOD/core/inc
	${CMAKE_SOURCE_DIR}/external/FMOD/studio/inc
	${SDL2_TTF_INCLUDE_DIRS}
)

target_link_directories(app PRIVATE
	${GLEW_LIBRARY_DIRS}
	/usr/local/lib # For SOIL
	${CMAKE_SOURCE_DIR}/external/FMOD/core/lib
	${CMAKE_SOURCE_DIR}/external/FMOD/studio/lib
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
	fmodstudioL
	fmodL
	SDL2_ttf
)

add_custom_target(copy_assets ALL
	COMMAND "cp" "-r" "${CMAKE_SOURCE_DIR}/src/Assets/" "${CMAKE_BINARY_DIR}/Assets/"
	COMMAND "cp" "-r" "${CMAKE_SOURCE_DIR}/src/Shaders/" "${CMAKE_BINARY_DIR}/Shaders/"
)

add_custom_target(copy_libs ALL
	COMMAND "mkdir" "-p" "${CMAKE_BINARY_DIR}/lib"
	COMMAND "cp" "${CMAKE_SOURCE_DIR}/external/FMOD/core/lib/*.dylib" "${CMAKE_BINARY_DIR}/lib/"
	COMMAND "cp" "${CMAKE_SOURCE_DIR}/external/FMOD/studio/lib/*.dylib" "${CMAKE_BINARY_DIR}/lib/"
)

add_custom_target(add_rpath ALL
	COMMAND "install_name_tool" "-add_rpath" "@executable_path/lib" "${CMAKE_BINARY_DIR}/app"
)