#ifndef INTERACTION_H_INCLUDED
#define INTERACTION_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>

void mouseButtonCallback( GLFWwindow *window, int button, int action, int mods );
void scrollCallback( GLFWwindow *window, double xoffset, double yoffset );
#endif
