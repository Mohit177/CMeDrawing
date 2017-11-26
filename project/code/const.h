/*******************************************************************
      Constants declaration for CS580 Programming Assignment 0
********************************************************************
    Author: Lavanya Viswanathan
      Date: September 16, 1997
   Subject: Declaration of constants
********************************************************************/
#ifndef CONST_H
#define CONST_H
/* draw attribute flags */
#define FILL_BIT       1  /* whether area filling is requested */
#define ANTIALIAS_BIT  2  /* whether antialiasing is requested */
#define CROSSHATCH_BIT 4  /* whether cross-hatching is requested */

/* maximum no. of vertices of a polygon */
#define MAX_VERTICES           910
#define MIN_VERTICES_CONTROL   4
#define MAX_VERTICES_CONTROL   30
#define MAX_VERTICES_AXIS      2

/* define the maximum number of elements in a transformation matrix */
#define MAX_ELEM_TRANSFORM   4

/* define PI */
#define PI   3.1415927

/* boolean constants */
#define TRUE  1
#define FALSE 0

/* colors */
#define RED     1
#define GREEN   2
#define BLUE    3
#define YELLOW  4
#define MAGENTA 5
#define CYAN    6
#define WHITE   7

/* line widths */
#define LINE_WIDTH_1 1
#define LINE_WIDTH_2 2
#define LINE_WIDTH_3 3
#define LINE_WIDTH_4 4

/* point sizes */
#define POINT_SIZE_1 1
#define POINT_SIZE_4 4
#define POINT_SIZE_8 8

/* default line attributes */
#define DEFAULT_LINE_WIDTH   LINE_WIDTH_1
#define DEFAULT_POINT_SIZE   POINT_SIZE_8
#define DEFAULT_LINE_COLOR   WHITE

/* default window dimensions */
#define DEFAULT_WINDOW_WIDTH    512
#define DEFAULT_WINDOW_HEIGHT   512

/* displays types */
#define RGB_SLICE_DISPLAY      0
#define POLYGONAL_DISPLAY      1

/* cube parameters */
#define NUM_CUBE_PERMS         256
#define NUM_BASIS_CUBES        15
#define NUM_CUBE_VERTICES      8
#define NUM_CUBE_EDGES         12
#define NUM_CUBE_ROTATIONS     24

/* minimum short int */
#define SHORT_INT_MIN          -32767

/* type definitions for points and triangles */
typedef struct 
{
  double x,y,z;
} point;

typedef struct
{
  point *pt1, *pt2, *pt3;
} triangle;


#endif