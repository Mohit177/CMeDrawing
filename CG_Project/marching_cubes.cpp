#include <stdlib.h>
#include <GL/glut.h>
#include "callbacks.h"

int main(int argc, char** argv)
{
    GLint windWidth = DEFAULT_WINDOW_WIDTH, windHeight = DEFAULT_WINDOW_HEIGHT;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windWidth, windHeight);
    glutCreateWindow("Matching Cubes");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(DEFAULT_LINE_WIDTH);
    glPointSize(DEFAULT_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboardSpecial);
    glutMainLoop();

    return 0;
}
