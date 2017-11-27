/** @file Scene.h
Header file for functions to draw primitive shapes & other objects.
*/

#ifndef INTERACTION_H_INCLUDED
#define INTERACTION_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <string>
#include <iostream>

void importFile(std::string fname);
void drawFile();

#endif
