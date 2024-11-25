#pragma once
#ifndef OBJECTS_H
#define OBJECTS_H

void cube(void);
void wheel(GLUquadricObj* pObj0);
void draw_base(void);
void draw_arm_1(double joint1);
void draw_arm_2(double joint2);
void draw_arm_3(double joint3);
void draw_robotic_arm_R(double joint1,double joint2,double joint3);
void draw_robotic_arm_L(double joint1,double joint2,double joint3);
void draw_chassis(void);
void draw_lifting_platform(void);
#endif 