#include "freeglut.h"
#include "objects.h"
#include "nocolor_objects.h"
void wheel_nc(GLUquadricObj* pObj0) {
	
	gluCylinder(pObj0, 30, 30, 30, 20, 20);  //r=30 h=30
	gluDisk(pObj0, 0, 30, 20, 20);
}

void draw_base_nc(void) {
	// draw base : robotic arm base with circle joint
	GLUquadricObj* pObj0;
	pObj0 = gluNewQuadric();
	//glPushMatrix();

	glPushMatrix();

	glScalef(55, 7.5, 35);
	cube();

	glPopMatrix();

	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(pObj0, 30, 30, 30, 20, 20);  //r=30 h=30
	glTranslatef(0, 0, 30);
	gluDisk(pObj0, 0, 30, 30, 20);


}
void draw_arm_1_nc(void) {
	glPopMatrix();
	GLUquadricObj* pObj1;
	pObj1 = gluNewQuadric();
	glTranslatef(0.0, 30.0, 0.0);
	glPushMatrix();
	
	glScalef(21, 25.0, 21);
	cube();
	glPopMatrix();
	//glPushMatrix();

	glTranslatef(10.0, 32.0, 0.0);
	glPushMatrix();
	glRotatef(60.0, 0.0, 0.0, 1.0);
	glScalef(21, 65.0, 21);
	cube();
	glPopMatrix();
	/*glPushMatrix();*/

	glTranslatef(-110, 65, -30); // -100 125.5 -30
	gluCylinder(pObj1, 21, 21, 60, 20, 20);
	gluDisk(pObj1, 0, 21, 21, 20);
	glTranslatef(0, 0, 60);
	gluDisk(pObj1, 0, 21, 21, 20);

}

void draw_arm_2_nc(void) {
	// animation
	GLUquadricObj* pObj2;
	pObj2 = gluNewQuadric();
	//glRotatef(angle, 0.0, 0.0, 1.0); // first joint rotation
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	//front slab

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

	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glTranslatef(-30, 0, 120);
	gluCylinder(pObj2, 16, 16, 40, 20, 20);// the third joint
	glTranslatef(0, 0, 40);//r=16 h=40
	gluDisk(pObj2, 0, 16, 16, 20);
}
void draw_arm_3_nc(void) {
	//glRotatef(angle, 0.0, 0.0, 1.0); // third arm
	glPushMatrix();
	glTranslatef(0.0, -20.0, 30.0);

	glScalef(20, 20, 30);
	cube();
	glPopMatrix();
	glPushMatrix();

	glTranslatef(0.0, -10.0, 60.0);
	glScalef(40, 10, 10);
	cube();
	glPopMatrix();
	glPushMatrix();

	glTranslatef(-25.0, -10.0, 85.0);
	glScalef(10, 10, 15);
	cube();
	glPopMatrix();

	glTranslatef(25.0, -10.0, 85.0);
	glScalef(10, 10, 15);
	cube();
}

void draw_robotic_arm_nc() {
	draw_base_nc();
	//glRotatef(theta, 0.0, 1.0, 0.0); // first joint rotation
	draw_arm_1_nc();
	draw_arm_2_nc();
	draw_arm_3_nc();
	//glPopMatrix();
}

void draw_chassis_nc() {
	GLUquadricObj* pObj0;
	pObj0 = gluNewQuadric();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();

	glTranslatef(0.0, 50.0, 0.0);
	glPushMatrix();
	glScalef(300, 50, 300);
	glutSolidCube(1);


	glPopMatrix();
	glTranslatef(0.0, 25 + 5.0, 0.0);
	glPushMatrix();
	glScalef(300, 10, 300);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glTranslatef(-120.0, 30.0, 120.0); // front left wheel
	wheel_nc(pObj0);
	glPopMatrix();
	glTranslatef(120.0, 30.0, 120.0); //back left wheel
	wheel_nc(pObj0);
	glPopMatrix();
	glTranslatef(-120.0, 30.0, -150.0); //front right wheel
	wheel_nc(pObj0);
	glPopMatrix();
	glTranslatef(120.0, 30.0, -150.0); //front right wheel
	wheel_nc(pObj0);
	// lifting rays
	glPopMatrix();

	glTranslatef(100.0, 420, 0.0);
	glScalef(60, 700, 150);
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(55.0, 420, 0.0);
	glScalef(30, 700, 60);
	glutSolidCube(1);

}
void draw_lifting_platform_nc() {
	GLUquadricObj* pObj0;
	pObj0 = gluNewQuadric();

	glTranslatef(-20.0, 600, 0.0);
	glPushMatrix();
	glPushMatrix();// robot arm start
	glScalef(150, 100, 150);
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(-20.0, 50, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(pObj0, 30, 30, 80, 20, 20);

	glTranslatef(0.0, 0, 100.0);
	gluSphere(pObj0, 60, 20, 20);

	glRotatef(-90.0, 0.0, 1.0, 0.0);
	gluCylinder(pObj0, 30, 20, 80, 20, 20);
}