project(VIEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

option(VIENGINE_HEADLESS "Build VIEngine without windowing (headless)" ON)

# Try to find or fetch GLFW only if not headless
if (NOT VIENGINE_HEADLESS)
	# Try to find GLFW via CMake package first
	find_package(glfw3 QUIET)

	# If not found, fetch GLFW from source
	if (NOT glfw3_FOUND)
		include(FetchContent)
		# Configure GLFW options before fetching
		set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
		set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
		set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
		set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
		set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
		set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)

		FetchContent_Declare(
			glfw
			GIT_REPOSITORY https://github.com/glfw/glfw.git
			GIT_TAG 3.4
		)
		FetchContent_MakeAvailable(glfw)
	endif()
endif()

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/VIEngine/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

if (VIENGINE_HEADLESS)
	target_compile_definitions(${PROJECT_NAME} PUBLIC ON_VI_ENGINE DYNAMIC_LIB=0 DYNAMIC_BUILD=0 VIENGINE_HEADLESS=1 FMT_HEADER_ONLY=1 SPDLOG_HEADER_ONLY=1)
else()
	target_compile_definitions(${PROJECT_NAME} PUBLIC ON_VI_ENGINE DYNAMIC_LIB=0 DYNAMIC_BUILD=0 FMT_HEADER_ONLY=1 SPDLOG_HEADER_ONLY=1)
endif()

# Link against GLFW target when not headless
if (NOT VIENGINE_HEADLESS)
	if (TARGET glfw)
		target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
	elseif (glfw3_FOUND)
		target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
	else()
		message(FATAL_ERROR "GLFW not found and could not be fetched.")
	endif()
endif()

# Public include dirs for engine and vendors
target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/VIEngine
	${CMAKE_SOURCE_DIR}/Vendors/include
)

# Precompiled headers
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/VIEngine/pch.h ${CMAKE_SOURCE_DIR}/Vendors/include/glad/gl.h)