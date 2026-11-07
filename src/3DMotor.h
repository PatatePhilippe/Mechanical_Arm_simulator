//
// Created by alexis on 12/07/2026.
//

#ifndef MOTEUR_GRAPHIQUE_H
#define MOTEUR_GRAPHIQUE
#include <stddef.h>

#include "cglm/ivec3.h"
//TODO: replace this part by an object struct to have separate coords later on
#pragma once
typedef struct {//make a heap list of objects
    vec3 angles,pos,color,center_point;
    mat3 triangles[8];
} object_3D;

#pragma once
typedef struct {
    vec3 angles;
    vec3 pos;
} Camera;


extern const int fovX ;
extern const double fovY;
extern const double zFar;
extern const double zNear;
extern const float screenW;
extern const float screenH;
extern const float fovXRad;


void mat3_rot_y(double angle,mat3 out);
void mat3_rot_x(double angle,mat3 out);
void mat3_rot_z(double angle,mat3 out);
void mat3_mul(mat3 m, vec3 v,vec3 res);

//Cube  cube_make(double size);
void  rotate_obj(mat3 mat_proj,mat3 *in,mat3 *dest,size_t size);

void move_cam(Camera *cam, char dir, int amount);
void turn_cam(Camera *cam, char dir, float amount);
void triangle_final(mat3 triangle,mat3 dest, mat4 *projection3D);
void move_obj(mat3 *polys ,float dist,int indexOfAxe,long unsigned int size);
void projectionMatrix(mat4 dest);






#endif //MOTEUR_GRAPHIQUE_H