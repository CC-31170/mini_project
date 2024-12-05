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
double theta, phi, alpha,beta_R,beta_R_last,beta_L,gama_R,gama_L,omega;
bool isRunning = true;
int animationState = 0;
int count = 0;
//shadow on plane parameter
float Xs = 300, Ys = 1800, Zs = 300;
//GLfloat light1PosType[] = { Xs, Ys, Zs, 1.0 };
float shadowColour[] = { 0.1, 0.1, 0.1 };
GLfloat M[16];
//quadrilateral texture mapping
void drawFloor(void)
{
	int i = 0;
	glPushMatrix();
	for (float z = 1500.0; z > -1500.0; z -= 100.0)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (float x = -1500.0; x < 1500.0; x += 100.0)
		{
			if ((i ) % 2 == 0 ) glColor3f(0.9, 0.6, 0.4); 
			else glColor3f(0.6, 0.3, 0.1); 
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
// draw no color objects (shadow)
void displayobject(void)
{
	glPushMatrix();
	glTranslatef(-omega, 0, 0.0);
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
		draw_robotic_arm_nc_R(alpha, beta_R, gama_R);
		glPopMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(0, 75, 0);
		draw_robotic_arm_nc_L(alpha, beta_L, gama_L);
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
	glTranslatef(-omega, 0, 0.0);
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
		draw_robotic_arm_R(alpha,beta_R,gama_R);
		glPopMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(0, 75, 0);
		draw_robotic_arm_L(alpha,beta_L,gama_L);
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
	drawFloor();
	glPopMatrix();

	for (int i = 0; i < 16; i++)
		M[i] = 0;
	M[0] = M[5] = M[10] = 1;//shadow perspective matrix
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
		double lift_length = 100.0, movement_x=600;
		double joint_1 = 90,joint_lf_3 = 90, joint_rg_3 = 90;
		double joint_2 = 40;
		double swing_time = 1000.0;
		double waving_time = 1000;
		
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
		case 3://turn wrist
			gama_R = joint_lf_3 * pow(sin(PI * t / (2 * swing_time)), 2);
			gama_L = 0;
			if (gama_R>=joint_lf_3 - 1)
			{
				gama_R = joint_lf_3;
				animationState = 4;
				t_prev = glutGet(GLUT_ELAPSED_TIME);
			}
			break;
		case 4://waving arm
			beta_R = joint_2 *sin(PI * t / (waving_time));
			beta_L = 0;
			if (t>=4*waving_time)
			{
				animationState = 5;
				t_prev = glutGet(GLUT_ELAPSED_TIME);
			}
			break;
		case 5://reset
			gama_R = -joint_lf_3 * pow(cos(PI * t / (2 * swing_time)), 2);
			alpha = joint_1 * pow(cos(PI * t / (2 * swing_time)), 2);
			if (gama_R >=- 1)
			{
				gama_R = 0;
				animationState = 6;
				t_prev = glutGet(GLUT_ELAPSED_TIME);
			}
			break;
		case 6:
			omega = movement_x * pow(sin(PI * t / (3 * swing_time)), 2);
			if (phi >= movement_x )
			{
				phi = movement_x;
				animationState = 7;
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
	glutInit(&argc, argv);			                     
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowPosition(WIN_POSX, WIN_POSY);         
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);		  
	glutCreateWindow("mini project");					 
	t_prev = glutGet(GLUT_ELAPSED_TIME);
	theta = 0; phi = 0; alpha = 0,beta_R=0,beta_L=0,gama_R=0,gama_L=0,omega=0;
	glutIdleFunc(animate);
	glutMouseFunc(gsrc_mousebutton);
	glutMotionFunc(gsrc_mousemove);
	glutDisplayFunc(drawscene);   
	glutMainLoop();
}