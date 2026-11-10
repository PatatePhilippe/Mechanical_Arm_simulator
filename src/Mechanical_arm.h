//
// Created by pat on 04/11/2026.
//

#ifndef MECHA_ARM
#define MECHA_ARM
#include "3DMotor.h"
#include "cglm/mat3.h"

typedef struct {
    vec3 angles,pos,joint_point,center_point;
    mat3 triangles[12];
    float length;
} mechanical_arm_part;

typedef struct {
    float total_length,
    base_length;
    unsigned int arm_count;
    mechanical_arm_part arm_parts[2];
    //mechanical_arm_part* arm_end;
} mechanical_arm;

extern mechanical_arm_part map1;
extern mechanical_arm_part map2;
extern mechanical_arm_part map3;

extern vec3 point_init;
extern vec3 point_final;

void arm_simulation();

#endif //MECHA_ARM
