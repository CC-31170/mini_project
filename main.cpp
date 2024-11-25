////////////////////////////////////////////////////////////////////////////////////////////////////
// Specification:
//   An animation is a robot with chassis and vertical Lifting mechanism 
//   and two robotic arms with 
//   Copy right of Liu Yunju 2024-10-13  yunjuliu2-c@my.cityu.edu.hk
//	 Department of Electronic Engineering  City University of HongKong
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "glew.h"
#include "freeglut.h"
#include "objects.h"
#include "gsrc.h"
#include "object.h"
#include "nocolor_objects.h"

#define PI 3.141592654
#define WIN_POSX   50
#define WIN_POSY   100
#define WIN_WIDTH  800
#define WIN_HEIGHT 600

//animation parameters
double t_prev;                  
double theta, phi, alpha,beta,gama;
bool isRunning = true;
int animationState = 0;
//shadow on plane parameter
float Xs = 300, Ys = 1800, Zs = 300;
GLfloat light1PosType[] = { Xs, Ys, Zs, 1.0 };
float shadowColour[] = { 0.1, 0.1, 0.1 };
GLfloat M[16];
//quadrilateral texture mapping
void drawCheckeredFloor(void)
{
	int i = 0;
	glPushMatrix();
	for (float z = 1000.0; z > -1000.0; z -= 100.0)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (float x = -1000.0; x < 1000.0; x += 100.0)
		{
			if (i % 2) glColor3f(0.2, 0.185, 0.136);
			else glColor3f(0.5, 1.0, 1.0);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(x, 0.0, z - 100.0);
			glVertex3f(x, 0.0, z);
			i++;
		}
		glEnd();
		i++;
	}
	glPopMatrix();
}
// draw no color objects
void displayobject(void)
{
	glPushMatrix();
	glRotatef(theta, 0.0, 1.0, 0.0);
		glPushMatrix();
		draw_chassis_nc();
		glPopMatrix();
		glTranslatef(-20.0, 300, 0.0);
		glTranslatef(-20.0, phi * 2, 0.0);//case 1
		draw_lifting_platform_nc();
		glPopMatrix();
		glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0, 75, 0);
		draw_robotic_arm_nc(alpha);
		glPopMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(0, 75, 0);
		draw_robotic_arm_nc(alpha);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-600.0, 0.0, 600.0);
	glColor3f(0, 0, 0);//gripper1
	glScalef(100, 100, 100);
	cube();
	glPopMatrix();
	
}
// draw colorful objects
void displayobject2(void)
{

	glPushMatrix();
	glRotatef(theta, 0.0, 1.0, 0.0);//case 0
		glPushMatrix();
		draw_chassis();
		glPopMatrix();
		glTranslatef(-20.0, 300, 0.0);
		glTranslatef(-20.0, phi * 2, 0.0);//case 1
		draw_lifting_platform();
		glPopMatrix();
		glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0, 75, 0);
		draw_robotic_arm(alpha);
		glPopMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(0, 75, 0);
		draw_robotic_arm(alpha);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-600.0, 0.0, 600.0);
	glColor3f(0.4, 0.265, 0.02);//gripper1
	glScalef(100, 100, 100);
	cube();
	glPopMatrix();
}
void drawscene(void)
{
	GLint viewport[4];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Set display-window color to white.
	glGetIntegerv(GL_VIEWPORT, viewport); // viewport is by default the display window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, double(viewport[2]) / viewport[3], 0.1, 2200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 800, 1200, 0, 0, 0, 0, 1, 0);
	glMultMatrixf(gsrc_getmo());

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0.0, -2, 0.0);
	drawCheckeredFloor();
	glPopMatrix();

	for (int i = 0; i < 16; i++)
		M[i] = 0;
	M[0] = M[5] = M[10] = 1;
	M[7] = -1.0 / Ys;

	displayobject2();
	glTranslatef(Xs, Ys, Zs); // Mwc
	glMultMatrixf(M); // perspective project
	glTranslatef(-Xs, -Ys, -Zs); // Ms
	glColor3fv(shadowColour); // 
	displayobject();
	glPopMatrix(); // restore state
	glutSwapBuffers();
}

void animate(void)
{
	
		double	t, rt, cosang;
		double rotate_angle = 90.0;
		double lift_length = 100.0;
		double joint_1 = 90,joint_lf_1 = 90, joint_rg_2 = 90;
		double swing_time = 1000.0;
		
		t = glutGet(GLUT_ELAPSED_TIME) - t_prev;
		switch (animationState)
		{
		case 0:
			theta = rotate_angle * pow(sin(PI * t / (2 * swing_time)), 2);
			if (theta >= rotate_angle-1) // -1 for avoid not detecting because high speed
			{
				theta = rotate_angle;
				animationState = 1;
				t_prev = glutGet(GLUT_ELAPSED_TIME); // Reset time for next animation
			}
			break;
		case 1:
			phi = lift_length * pow(sin(PI * t / (2 * swing_time)), 2);
			if (phi >= lift_length-1)
			{
				phi = lift_length;
				animationState = 2;
				t_prev = glutGet(GLUT_ELAPSED_TIME); 
			}
			break;
		case 2:
			alpha = joint_1 * pow(sin(PI * t / (2 * swing_time)), 2);
			if (alpha >= joint_1 - 1)
			{
				alpha = joint_1;
				animationState = 3;
				t_prev = glutGet(GLUT_ELAPSED_TIME);
			}
			break;
		default:
			
			break;
		}
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
	theta = 0; phi = 0; alpha = 0,beta=0,gama=0;
	glutIdleFunc(animate);
	glutMouseFunc(gsrc_mousebutton);
	glutMotionFunc(gsrc_mousemove);
	glutDisplayFunc(drawscene);   
	glutMainLoop();
}