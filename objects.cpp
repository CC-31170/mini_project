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

void draw_arm_2(double angle) {
	// animation
		GLUquadricObj* pObj2;
		pObj2 = gluNewQuadric();
		glRotatef(angle, 0.0, 0.0, 1.0); // first joint rotation
		glPushMatrix();
			glPushMatrix();
				glPushMatrix();
					//front slab
					glColor3f(0.66, 0.66, 0.66);
					glTranslatef(-10, -20, 10); 
					glScalef(40, 22, 10);    
					cube();
					glPopMatrix();
					//back slab
					glTranslatef(-10, -20, -70); 
					glScalef(40, 22, 10);
					cube();
					glPopMatrix();
				//middle slab
				glTranslatef(-85, -20, -30); 
				glScalef(60, 20, 30);
				cube();
				glPopMatrix();
			glColor3f(1.0, 0.0, 0.0);
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			glTranslatef(-30, 0, 120);
			gluCylinder(pObj2, 16, 16, 40, 20, 20);// the third joint
			glTranslatef(0, 0, 40);//r=16 h=40
			gluDisk(pObj2, 0, 16,16, 20);
		
}
void draw_arm_3(double angle) {
	glRotatef(angle, 0.0, 0.0, 1.0); // third arm
	glPushMatrix();
	glTranslatef(0.0, -20.0, 30.0);
	glColor3f(0.66, 0.66, 0.66);//grey
	glScalef(20, 20, 30);
	cube();
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 0, 0);// slide rail
	glTranslatef(0.0, -10.0, 60.0);
	glScalef(40, 10, 10);
	cube();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);//gripper1
	glTranslatef(-25.0, -10.0, 85.0);
	glScalef(10, 10, 15);
	cube();
	glPopMatrix();
	glColor3f(0.66, 0.66, 0.66);//gripper2
	glTranslatef(25.0, -10.0, 85.0);
	glScalef(10, 10, 15);
	cube();

}