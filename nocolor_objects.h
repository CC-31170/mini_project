#pragma once
#ifndef NOCOLOR_OBJECTS_H
#define NOCOLOR_OBJECTS_H
#include "freeglut.h"
void wheel_nc(GLUquadricObj* pObj0);
void draw_base_nc(void);
void draw_arm_1_nc(double joint1);
void draw_arm_2_nc(void);
void draw_arm_3_nc(void);
void draw_robotic_arm_nc(double joint1);
void draw_chassis_nc();
void draw_lifting_platform_nc(void);
#endif // !NOCOLOR_OBJECTS_H
