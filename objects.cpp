#include "freeglut.h"
#include "object.h"
void cube(){
// draw a standard 2 x 2 x 2 cube whose center is at (0, 1, 0)
	/* The use of glPushMatrix and glPopMatrix here protects the glRotatef from
	   exercising its influence on the relative transformation beyond this function */
	glPushMatrix();

	glTranslatef(0, 1, 0);
	glutSolidCube(2);

	glPopMatrix();

}
void wheel(GLUquadricObj* pObj0) {
	glColor3f(1, 0, 0);//red chassis wheel
	gluCylinder(pObj0, 30, 30, 30, 20, 20);  //r=30 h=30
	gluDisk(pObj0, 0, 30, 20, 20);
}
void draw_base(void){
// draw base : robotic arm base with circle joint
	GLUquadricObj* pObj0;
	pObj0 = gluNewQuadric();
	//glPushMatrix();
	glPopMatrix();
	glTranslatef(0, 0, -120);
	glPushMatrix();
	glColor3f(0.38, 0.38, 0.38); //dark grey
	glScalef(55, 7.5, 35);
	cube();
	
	glPopMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(pObj0, 30, 30, 30, 20, 20);  //r=30 h=30
	glTranslatef(0, 0, 30);
	gluDisk(pObj0, 0, 30, 30, 20);
	
	
}
void draw_arm_1(void){
	glPopMatrix();
	GLUquadricObj* pObj1;
	pObj1 = gluNewQuadric();
	glTranslatef(0.0, 30.0, 0.0);
	glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);//grey
	glScalef(21, 25.0, 21);
	cube();
	glPopMatrix();
	//glPushMatrix();
	glColor3f(0.66, 0.66, 0.66);
	glTranslatef(10.0, 32.0, 0.0);
	glRotatef(60.0, 0.0, 0.0, 1.0);
	glScalef(21, 65.0, 21);
	cube();
	//glPopMatrix();
	/*glPushMatrix();*/
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-100, 125.5, -30);
	gluCylinder(pObj1, 21, 21, 60, 20, 20);
	gluDisk(pObj1, 0, 21, 21, 20);
	glTranslatef(0, 0, 60);
	gluDisk(pObj1, 0, 21, 21, 20);
}

void draw_arm_2() {
	// animation
		GLUquadricObj* pObj2;
		pObj2 = gluNewQuadric();
		//glRotatef(angle, 0.0, 0.0, 1.0); // first joint rotation
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
void draw_arm_3() {
	//glRotatef(angle, 0.0, 0.0, 1.0); // third arm
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

void draw_robotic_arm() {
	draw_base();
	//glRotatef(theta, 0.0, 1.0, 0.0); // first joint rotation
	draw_arm_1();
	//draw_arm_2();
	//draw_arm_3();
	//glPopMatrix();
}

void draw_chassis() {
	GLUquadricObj* pObj0;
	pObj0 = gluNewQuadric();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
	glPushMatrix();
		glColor3f(0.66, 0.66, 0.66);//grey chassis body
		glTranslatef(0.0, 50.0, 0.0);
		glPushMatrix();
		glScalef(300, 50, 300);
		glutSolidCube(1);
	
		glColor3f(0.38, 0.38, 0.38);//grey chassis body
		glPopMatrix();
		glTranslatef(0.0, 25+5.0, 0.0);
		glPushMatrix();
		glScalef(300, 10, 300);
		glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();
	glTranslatef(-120.0, 30.0, 120.0); // front left wheel
	wheel(pObj0);   
	glPopMatrix();
	glTranslatef(120.0, 30.0, 120.0); //back left wheel
	wheel(pObj0);
	glPopMatrix();
	glTranslatef(-120.0, 30.0, -150.0); //front right wheel
	wheel(pObj0);
	glPopMatrix();
	glTranslatef(120.0, 30.0, -150.0); //front right wheel
	wheel(pObj0);
	// lifting rays
	glPopMatrix();
	glColor3f(0.66, 0.66, 0.66);
	glTranslatef(100.0, 420, 0.0);
	glScalef(60, 700, 150);
	glutSolidCube(1);
	glPopMatrix();
	glColor3f(0.38, 0.38, 0.38);
	glTranslatef(55.0, 420, 0.0);
	glScalef(30, 700, 60);
	glutSolidCube(1);
	
}
void draw_lifting_platform() {
	GLUquadricObj* pObj0;
	pObj0 = gluNewQuadric();
	glColor3f(1, 0, 0);
	glTranslatef(-20.0, 400, 0.0);
	glPushMatrix();
	glPushMatrix();// robot arm start
	glScalef(150, 100, 150);
	glutSolidCube(1);
	glPopMatrix();
	glColor3f(0.38, 0.38, 0.38);
	glTranslatef(-20.0, 50, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(pObj0, 30, 30, 80, 20, 20);
	glColor3f(0.66, 0.66, 0.66);
	glTranslatef(0.0, 0, 100.0);
	gluSphere(pObj0, 60, 20, 20);
	glColor3f(0, 1, 0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	gluCylinder(pObj0, 30, 20, 80, 20, 20);
}