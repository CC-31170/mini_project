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

double t_prev;                   // previous time elapsed
double theta, phi, psi;

GLUquadricObj* pObj1, * pObj2, * pObj3; //quadric objects to store properties of the quadric mesh

void displayobject(void)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Set display-window color to white.
	glClear(GL_COLOR_BUFFER_BIT);

	draw_base();
	glRotatef(theta, 0.0, 1.0, 0.0); // first joint rotation
	
	draw_arm_1();
	
	dram_arm_2(theta);

}

void drawscene(void)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport); // viewport is by default the display window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, double(viewport[2]) / viewport[3], 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 600, 0, 0, 0, 0, 1, 0);
	glMultMatrixf(gsrc_getmo());  // get the rotation matrix from the rotation user-interface

	displayobject();

	glutSwapBuffers();
}

void animate(void)
{
	double	t, rt, cosang;
	double swing_angle = 90.0;                  
	double swing_time = 1000.0;

	t = glutGet(GLUT_ELAPSED_TIME) - t_prev;

	theta = swing_angle * pow(sin(PI * t / (2 * swing_time)), 2);
	glutPostRedisplay();
}

void main (int argc, char** argv)
{
	
	glutInit(&argc, argv);			                      // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set display mode

	glutInitWindowPosition(WIN_POSX, WIN_POSY);         // Set display-window position at (WIN_POSX, WIN_POSY) 
														  // where (0, 0) is top left corner of monitor screen
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);		  // Set display-window width and height.

	glutCreateWindow("mini project");					  // Create display window.
	t_prev = glutGet(GLUT_ELAPSED_TIME);
	theta = 0; phi = 0; psi = 0;
	//////////////////////////////////////////////////////////////////
	// 
	// Register mouse-click and mouse-move glut callback functions
	// for the rotation user-interface.
	// 
	glutIdleFunc(animate);
	glutMouseFunc(gsrc_mousebutton);
	glutMotionFunc(gsrc_mousemove);
	//
	//////////////////////////////////////////////////////////////////
	glutDisplayFunc(drawscene);   // put everything you wish to draw in drawscene
	glutMainLoop();
}