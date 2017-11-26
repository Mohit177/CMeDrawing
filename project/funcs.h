/*******************************************************************
       Function Prototypes for CS580 Programming Assignment 5
********************************************************************
    Author: Lavanya Viswanathan
      Date: December 01, 1997
   Subject: Function prototypes 
********************************************************************/
#ifndef FUNCS_H
#define FUNCS_H
#include "data.h"
#include "const.h"
#include <string>

/* in the file 'callbacks.c' */
void selectColor(int color);
void selectDataSet(int option,std::string fname,int xdim,int ydim, int zdim);
void selectOption(int option);
void initStructures(void);
void freeStructures(void);
void generateFacetData(void);
void printFacetDataFile(void);
void generateEdgeData(void);
void printEdgeDataFile(void);
short int getCorner(int corner, int imarch, int jmarch);
void contour_intersect(int edge_name, int imarch, int jmarch, int kmarch, point *pt);
void add_vertex(point *pt);
void add_facet(int num_verts, long vertex_list[]);
void printVerticesFile(void);
void printFacetsFile(void);
int cube_index(int imarch, int jmarch);
void load_facet(int cube_index, int imarch, int jmarch, int kmarch);
void drawVolumeRGB(Volume *vol, int slice);
void drawPolygonalModel(void);
void computePolygonalModel(void);
void reshape(int width, int height);
void show(std::string file_input, int xdimen, int ydimen, int zdimen);
void mouseButton(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(int key, int x, int y);
void keyHandler(int key, int x, int y);
void createMenus(void);
void initLighting(void);

#endif