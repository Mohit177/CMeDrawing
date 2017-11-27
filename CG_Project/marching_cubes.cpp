/***********************************************************************
   CS580 Programming Assignment 5: Matching Cubes Algorithm
************************************************************************
        Author: Lavanya Viswanathan
                Dept. of Cognitive and Neural Systems
                Boston University
                December 01, 1997
************************************************************************
***********************************************************************/

#include <stdlib.h>
#include <GL/glut.h>
#include "funcs.h"

//#include "callbacks.c"

/* MAIN PROGRAM: The input parameters 'argc' and 'argv' are the program's 
                 unmodified variables that are initialized by 'glutInit'
		 */
int main(int argc, char **argv)
{
  GLint windWidth=DEFAULT_WINDOW_WIDTH, windHeight=DEFAULT_WINDOW_HEIGHT;

  glutInit(&argc, argv);

  /* create a window for spline curve editing */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(windWidth,windHeight);
  glutCreateWindow("Volume Rendering: Matching Cubes Algorithm");

  /* set default polygon attributes */
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(DEFAULT_LINE_WIDTH);
  glPointSize(DEFAULT_POINT_SIZE);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);  /* draw lines with correct filtering */
  glEnable(GL_BLEND);  /* blend the incoming RGBA color values with */
                       /* the values in the color buffers */
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  /*glEnable(GL_DEPTH_TEST);*/
  
  /* define window redisplay and reshape event callbacks for the subwindow */
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  /* define functions for mouse button press and mouse motion event callbacks for the sub-window */ 
//  glutMotionFunc(mouseMotion);
//  glutMouseFunc(mouseButton);

  /* define the callback function for normal and special keys on the keyboard */
//  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboardSpecial);

/*  volume = createVolume(256,256,114);
  volReadFile(volume,"../data/256.dat");*/
  /* initialize lighting for the scene */

  /* turn over control to GLUT */
  glutMainLoop();

  return 0;
}
