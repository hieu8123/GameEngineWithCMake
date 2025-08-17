#pragma once

/* Minimal stub of GLFW for build purposes */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GLFWwindow GLFWwindow;

#define GLFW_CONTEXT_VERSION_MAJOR 0x00022002
#define GLFW_CONTEXT_VERSION_MINOR 0x00022003
#define GLFW_OPENGL_PROFILE        0x00022008
#define GLFW_OPENGL_CORE_PROFILE   0x00032001

static inline int glfwInit(void) { return 1; }
static inline void glfwTerminate(void) {}
static inline void glfwWindowHint(int, int) {}
static inline GLFWwindow* glfwCreateWindow(int, int, const char*, void*, void*) { return (GLFWwindow*)0; }
static inline void glfwMakeContextCurrent(GLFWwindow*) {}
static inline void glfwSwapBuffers(GLFWwindow*) {}
static inline void glfwPollEvents(void) {}
static inline int glfwWindowShouldClose(GLFWwindow*) { return 1; }
static inline void* glfwGetProcAddress(const char*) { return 0; }

#ifdef __cplusplus
}
#endif

