#ifndef INTERACTION_H_INCLUDED
#define INTERACTION_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <string>
#include <iostream>

void drawBoundary();
void drawSeeSaw();
void drawSlide();
void drawSlide1();
void drawSwings();
void drawUnitCube(GLfloat red, GLfloat green, GLfloat blue);
void drawCylinder(GLfloat radius, GLfloat height, GLfloat red, GLfloat green, GLfloat blue);
void drawDisk(GLfloat inner_radius, GLfloat outer_radius,GLfloat red, GLfloat green, GLfloat blue);
void drawJungleGym();
void drawMonkeyBars();
void drawMerryGoRound();
void drawBench(GLfloat red, GLfloat green, GLfloat blue);
void importObjFile(const std::string&, const std::string& );
void drawObjFile();

#endif
