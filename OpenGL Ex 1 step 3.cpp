////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Specification:
//   Display a 31 x 31 quadrilateral mesh for PLANE in perspective projection.
//   Added an axis-angle rotation user-interface, such that the mesh can be rotated by draging the screen.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "freeglut.h"

//////////////////////////////////////////////////////////////////
// 
// Include the header file of our rotation user-interface.
// 
#include "gsrc.h"
// 
//////////////////////////////////////////////////////////////////
#define LIU 1
#define PI 3.141592654
#define GRIDSIZE 31
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

void displayobject (void)
{
  int i, j;
	int K = GRIDSIZE-1;

  //////////////////////////////////////////////////////////////////
  // 
  // Setup perspective projection and the rotation
  // 
  GLint viewport[4];
  glGetIntegerv( GL_VIEWPORT, viewport ); // viewport is by default the display window
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45, double(viewport[2])/viewport[3], 0.1, 10 );
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0,0,3, 0,0,0, 0,1,0 );
    glMultMatrixf( gsrc_getmo() );  // get the rotation matrix from the rotation user-interface
  //
  //////////////////////////////////////////////////////////////////

	
	/*  Enable Z buffer method for visibility determination. */
	//  Z buffer code starts
	
    glClear (GL_DEPTH_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);
	
	// Z buffer code ends */

	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);  // Clear display window.

	glColor3f(1,0,0);  // Set line segment color to red.
	// Advice: draw as few lines as possible. Eliminate all redundant drawing.
	for (i=0; i< K; i++)
		for (j=0; j< K; j++)
		{			
			glBegin(GL_LINES);
				glVertex3f(mesh[i][j].x,mesh[i][j].y,mesh[i][j].z);
				glVertex3f(mesh[i][j+1].x,mesh[i][j+1].y,mesh[i][j+1].z);

				glVertex3f(mesh[i][j].x,mesh[i][j].y,mesh[i][j].z);
				glVertex3f(mesh[i+1][j].x,mesh[i+1][j].y,mesh[i+1][j].z);
			glEnd();
		}

	for (i=0; i< K; i++)
	{
		glBegin(GL_LINES);
			glVertex3f(mesh[i][K].x,mesh[i][K].y,mesh[i][K].z);
			glVertex3f(mesh[i+1][K].x, mesh[i+1][K].y,mesh[i+1][K].z);
		glEnd();
	}

	for (j=0; j< K; j++)
	{
		glBegin(GL_LINES);
			glVertex3f(mesh[K][j].x,mesh[K][j].y,mesh[K][j].z);
			glVertex3f(mesh[K][j+1].x, mesh[K][j+1].y,mesh[K][j+1].z);
		glEnd();
	}

	glutSwapBuffers();
}

void main (int argc, char** argv)
{

  calculateplane();   // calculate data for the planar mesh

  glutInit (&argc, argv);                                      // Initialize GLUT
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );  // Set display mode.
  glutInitWindowPosition( WIN_POSX, WIN_POSY );                // Set display-window position at (WIN_POSX, WIN_POSY) 
                                                               // where (0, 0) is top left corner of monitor screen
  glutInitWindowSize( WIN_WIDTH, WIN_HEIGHT );		           // Set display-window width and height.
  glutCreateWindow( "OpenGL Program for Quadrilateral Mesh" ); // Create display window.

  //////////////////////////////////////////////////////////////////
  // 
  // Register mouse-click and mouse-move glut callback functions
  // for the rotation user-interface.
  // 
  glutMouseFunc( gsrc_mousebutton );
  glutMotionFunc( gsrc_mousemove );
  //
  //////////////////////////////////////////////////////////////////

  glutDisplayFunc( displayobject );	 // Send planar mesh to display window.
  glutMainLoop();			               // Display everything and wait.
}