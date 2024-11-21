#include "freeglut.h"

void cube(){
// draw a standard 2 x 2 x 2 cube whose center is at (0, 1, 0)


	/* The use of glPushMatrix and glPopMatrix here protects the glRotatef from
	   exercising its influence on the relative transformation beyond this function */
	glPushMatrix();

	glTranslatef(0, 1, 0);
	glutSolidCube(2);

	glPopMatrix();

}
void draw_base(void){
// draw base : robotic arm base with circle joint
	GLUquadricObj* pObj0;
	pObj0 = gluNewQuadric();
	glPushMatrix();
	glColor3f(0.38, 0.38, 0.38); //dark grey
	glScalef(55, 7.5, 35);
	cube();
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(pObj0, 30, 30, 30, 20, 20);  //r=30 h=30
	glTranslatef(0, 0, 30);
	gluDisk(pObj0, 0, 30, 20, 20);
	glPopMatrix();

}
void draw_arm_1(void){
	glPushMatrix();
	GLUquadricObj* pObj1;
	pObj1 = gluNewQuadric();
	glTranslatef(0.0, 30.0, 0.0);
	glColor3f(0.66, 0.66, 0.66);//grey
	glScalef(21, 25.0, 21);
	cube();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	glTranslatef(10.0, 62.0, 0.0);
	glRotatef(60.0, 0.0, 0.0, 1.0);
	glScalef(21, 65.0, 21);
	cube();
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-100, 125.5, -30);
	gluCylinder(pObj1, 21, 21, 60, 20, 20);
	gluDisk(pObj1, 0, 21, 21, 20);
	glTranslatef(0, 0, 60);
	gluDisk(pObj1, 0, 21, 21, 20);
	
	
}
void dram_arm_2(double angle) {
	// animation
	glPushMatrix();
		GLUquadricObj* pObj2;
		pObj2 = gluNewQuadric();
		glRotatef(angle, 0.0, 0.0, 1.0); // first joint rotation
		glTranslatef(-100, -20, -30);
		glColor3f(0.66, 0.66, 0.66);
		glScalef(60, 20.0, 30);
		cube();
		glPushMatrix();
			/*glColor3f(0, 1, 0);*/
			glTranslatef(1, 0, 1.3); 
			glScalef(1, 1, 0.3);
			cube();
			glTranslatef(1, 0, -1.3);
			glScalef(1, 1, 0.3);
			cube();
		glPopMatrix();
	glPopMatrix();

	

	


	
}