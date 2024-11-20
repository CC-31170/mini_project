////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Specification:
//   An animation is a robot with chassis and vertical Lifting mechanism 
//   and two robotic arms with 
//   Copy right of Liu Yunju 2024-10-13
//	 Department of Electronic Engineering  City University of HongKong
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "freeglut.h"
#include "objects.h"
//////////////////////////////////////////////////////////////////
// 
// Include the header file of our rotation user-interface.
// 
#include "gsrc.h"
#include "object.h"
// 
//////////////////////////////////////////////////////////////////

#define PI 3.141592654
#define GRIDSIZE 4
#define WIN_POSX   50
#define WIN_POSY   100
#define WIN_WIDTH  400
#define WIN_HEIGHT 300

typedef struct point{ // define a structure for 3D point (x, y, z)
	GLfloat x;
	GLfloat y;
	GLfloat z;
} vertex;

vertex mesh [GRIDSIZE][GRIDSIZE];           // define a mesh whose elements are 3D point (x, y, z)
vertex table[GRIDSIZE];
double theta, phi, psi;			      // rotation angles of robot, lower-and-upper arm, upper arm respectivley
GLUquadricObj* pObj1, * pObj2, * pObj3; //quadric objects to store properties of the quadric mesh

void draw_arm_1(void)
{
	glPushMatrix();					
	glColor3f(0.0, 1.0, 0.0);
	glScalef(21, 25.0, 21);
	cube();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(10.0, 32.0, 0.0);
	glRotatef(60.0, 0.0, 0.0, 1.0);
	glScalef(21, 45.0, 21);
	cube();
	glPopMatrix();

}


void calculateplane (void)
// calculate the parameters of the plane mesh
{
  for (int i=0;i<GRIDSIZE;i++)
    for (int j=0;j<GRIDSIZE;j++) 
    {
      mesh[i][j].x = 2*float(i)/(GRIDSIZE-1)-1;
      mesh[i][j].y = 2*float(j)/(GRIDSIZE-1)-1;
      mesh[i][j].z = 0;
    }
}
void calculatebase(void)
{
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
		{
			mesh[i][j].x = 2 * float(i) / (GRIDSIZE - 1) - 1;
			mesh[i][j].y = 2 * float(j) / (GRIDSIZE - 1) - 1;
			mesh[i][j].z = 1;
		}
}
void displayobject (void)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport); // viewport is by default the display window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, double(viewport[2]) / viewport[3], 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 400, 0, 0, 0, 0, 1, 0);
	glMultMatrixf(gsrc_getmo());  // get the rotation matrix from the rotation user-interface
  //
  //////////////////////////////////////////////////////////////////
	/*  Enable Z buffer method for visibility determination. */
	//  Z buffer code starts
    glClear (GL_DEPTH_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Set display-window color to white.
	glClear(GL_COLOR_BUFFER_BIT);

	draw_base();

	glTranslatef(0.0, 30.0, 0.0);

	draw_arm_1();
	
	glutSwapBuffers();

}

void main (int argc, char** argv)
{
	
	glutInit(&argc, argv);			                      // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set display mode

	glutInitWindowPosition(WIN_POSX, WIN_POSY);         // Set display-window position at (WIN_POSX, WIN_POSY) 
														  // where (0, 0) is top left corner of monitor screen
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);		  // Set display-window width and height.

	glutCreateWindow("mini project");					  // Create display window.

	theta = 0; phi = 0; psi = 0;
	pObj1 = gluNewQuadric();
	pObj2 = gluNewQuadric();
	pObj3 = gluNewQuadric();
	//////////////////////////////////////////////////////////////////
	// 
	// Register mouse-click and mouse-move glut callback functions
	// for the rotation user-interface.
	// 
	glutMouseFunc(gsrc_mousebutton);
	glutMotionFunc(gsrc_mousemove);
	//
	//////////////////////////////////////////////////////////////////
	glutDisplayFunc(displayobject);   // put everything you wish to draw in drawscene
	glutMainLoop();
}