#pragma once
#ifndef NOCOLOR_OBJECTS_H
#define NOCOLOR_OBJECTS_H
#include "freeglut.h"
void wheel_nc(GLUquadricObj* pObj0);
void draw_base_nc(void);
void draw_arm_1_nc(double joint1);
void draw_arm_2_nc(double joint2);
void draw_arm_3_nc(double joint3);
void draw_robotic_arm_nc_R(double joint1,double joint2,double joint3);
void draw_robotic_arm_nc_L(double joint1, double joint2, double joint3);
void draw_chassis_nc();
void draw_lifting_platform_nc(void);
#endif // !NOCOLOR_OBJECTS_H
