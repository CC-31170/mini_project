#include "freeglut.h"

void cube()
// draw a standard 2 x 2 x 2 cube whose center is at (0, 1, 0)
{

	/* The use of glPushMatrix and glPopMatrix here protects the glRotatef from
	   exercising its influence on the relative transformation beyond this function */
	glPushMatrix();

	glTranslatef(0, 1, 0);
	glutSolidCube(2);

	glPopMatrix();

}
void draw_base(void)
// draw base : robotic arm base with circle joint
{
	GLUquadricObj* pObj0;
	pObj0 = gluNewQuadric();
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(55, 7.5, 35);
	cube();
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(pObj0, 30, 30, 30, 20, 20);
	glTranslatef(0, 0, 30);
	gluDisk(pObj0, 0, 30, 20, 20);
	glPopMatrix();

}