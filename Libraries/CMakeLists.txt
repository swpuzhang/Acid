include(FindVulkan.cmake)
include(FindOpenAL.cmake)

set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE INTERNAL "Use MSVC Runtime Library DLL (/MD or /MDd)")

set(GLSLANG_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Libraries/glslang/" PARENT_SCOPE)
set(SKIP_GLSLANG_INSTALL ON CACHE INTERNAL "Skip installation")
set(BUILD_TESTING OFF CACHE INTERNAL "Enables test builds")
set(ENABLE_SPVREMAPPER OFF CACHE INTERNAL "Enables building of SPVRemapper")
set(ENABLE_GLSLANG_BINARIES OFF CACHE INTERNAL "Builds glslangValidator and spirv-remap")
set(ENABLE_AMD_EXTENSIONS OFF CACHE INTERNAL "Enables support of AMD-specific extensions")
set(ENABLE_NV_EXTENSIONS OFF CACHE INTERNAL "Enables support of Nvidia-specific extensions")
set(ENABLE_HLSL OFF CACHE INTERNAL "Enables HLSL input support")
set(ENABLE_OPT OFF CACHE INTERNAL "Enables spirv-opt capability if present")
add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/glslang)
set(GLSLANG_LIBRARIES "glslang" "SPIRV" PARENT_SCOPE)

set(GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Libraries/glfw/include" PARENT_SCOPE)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
set(GLFW_VULKAN_STATIC OFF CACHE INTERNAL "Use the Vulkan loader statically linked into application")
add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/glfw)
set(GLFW_LIBRARY "glfw" PARENT_SCOPE)

# TODO: Compile bullet dlls in MSVC. 
set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")

if(MSVC)
	set(BUILD_SHARED_LIBS OFF)
endif()

set(BULLET_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Libraries/bullet3/src" PARENT_SCOPE)
set(INSTALL_LIBS OFF CACHE INTERNAL "Set when you want to install libraries")
set(INSTALL_CMAKE_FILES OFF CACHE INTERNAL "Install generated CMake files")
set(BUILD_PYBULLET OFF CACHE INTERNAL "Set when you want to build pybullet (Python bindings for Bullet)")
set(BUILD_BULLET3 OFF CACHE INTERNAL "Set when you want to build Bullet 3")
set(BUILD_OPENGL3_DEMOS OFF CACHE INTERNAL "Set when you want to build the OpenGL3+ demos")
set(BUILD_CPU_DEMOS OFF CACHE INTERNAL "Build original Bullet CPU examples")
set(BUILD_BULLET2_DEMOS OFF CACHE INTERNAL "Set when you want to build the Bullet 2 demos")
set(USE_GRAPHICAL_BENCHMARK OFF CACHE INTERNAL "Use Graphical Benchmark")
set(BUILD_EXTRAS OFF CACHE INTERNAL "Set when you want to build the extras")
set(USE_GLUT OFF CACHE INTERNAL "Use Glut")
set(BUILD_UNIT_TESTS OFF CACHE INTERNAL "Build Unit Tests")
add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/bullet3)
set(BULLET_LIBRARIES "BulletSoftBody" "BulletDynamics" "BulletCollision" "LinearMath" PARENT_SCOPE)

set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")

set(PHYSFS_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Libraries/physfs/src" PARENT_SCOPE)
set(PHYSFS_BUILD_STATIC FALSE CACHE INTERNAL "Build static library") # physfs-static
set(PHYSFS_BUILD_SHARED TRUE CACHE INTERNAL "Build shared library") # physfs
set(PHYSFS_BUILD_TEST FALSE CACHE INTERNAL "Build stdio test program")
add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/physfs)
set(PHYSFS_LIBRARY "physfs" PARENT_SCOPE)