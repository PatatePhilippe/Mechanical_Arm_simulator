//
// Created by alexis on 12/07/2026.
//

#include "3DMotor.h"
#include <math.h>
#include <stdio.h>

#include "cglm/ivec3.h"
#include "cglm/mat3.h"
#include "cglm/mat4.h"
#include "cglm/call/mat4.h"
const int fovX = 30;
const double fovY = 50.0;
const double zFar = 10;
const double zNear = 0.5;
const float screenW=1200.0f;
const float screenH=900.0f;
const float fovXRad = (float)fovX * (3.14159265359F / 180.0F);

void mat3_rot_x(double angle, mat3 dest) {
    dest[0][0] = 1.0f; dest[1][0] = 0.0f;               dest[2][0] = 0.0f;
    dest[0][1] = 0.0f; dest[1][1] = cosf((float)angle);  dest[2][1] = -sinf((float)angle);
    dest[0][2] = 0.0f; dest[1][2] = sinf((float)angle);  dest[2][2] = cosf((float)angle);
}

void mat3_rot_y(double angle, mat3 dest) {
    dest[0][0] = cosf((float)angle);  dest[1][0] = 0.0f; dest[2][0] = sinf((float)angle);
    dest[0][1] = 0.0f;                dest[1][1] = 1.0f; dest[2][1] = 0.0f;
    dest[0][2] = -sinf((float)angle); dest[1][2] = 0.0f; dest[2][2] = cosf((float)angle);
}

void mat3_rot_z(double angle, mat3 dest) {
    dest[0][0] = cosf((float)angle); dest[1][0] = -sinf((float)angle); dest[2][0] = 0.0f;
    dest[0][1] = sinf((float)angle); dest[1][1] = cosf((float)angle);  dest[2][1] = 0.0f;
    dest[0][2] = 0.0f;               dest[1][2] = 0.0f;                dest[2][2] = 1.0f;
}


void projectionMatrix(mat4 dest){
    glm_mat4_zero(dest);

    dest[0][0] = (1.0F / tanf(fovXRad / 2.0F)) * (screenH / screenW);
    dest[1][1] = 1.0F / tanf(fovXRad / 2.0F);

    dest[2][2] = (float)(zFar / (zFar - zNear));
    dest[2][3] = 1.0f;
    dest[3][2] = (float)-((zFar * zNear) / (zFar - zNear));
}

void triangle_final(mat3 triangle,mat3 dest,mat4 *projection3D) { //TODO : change name to something like vertexVisual projection
    printf("calcul fin \n");
    for(int id =0 ; id < 3; id++){
        vec4 temp_vec={triangle[id][0],triangle[id][1],triangle[id][2],1.0f};
        glmc_mat4_mulv(*projection3D,temp_vec,temp_vec);
        printf("x %f,y %f,z %f \n",temp_vec[0],temp_vec[1],temp_vec[2]);
        if (temp_vec[3]!=0.0F){
            dest[id][0]=(temp_vec[0]/temp_vec[2])/temp_vec[3];
            dest[id][1]=(temp_vec[1]/temp_vec[2])/temp_vec[3];
            dest[id][2]=temp_vec[2]/temp_vec[3];
        }else{
            dest[id][0]=temp_vec[0]/temp_vec[2];
            dest[id][1]=temp_vec[1]/temp_vec[2];
            dest[id][2]=temp_vec[2];
        }
    }
}

void rotate_obj(mat3 matProjection, mat3 *in, mat3 *dest, size_t size){
    for(int i =0 ; i < size; i++) {//TODO : not working
        glm_mat3_mul(matProjection,in[i],dest[i]);
    }
}

void move_cam(Camera *cam,char dir,int amount) {
    if (dir == 'f') {
        cam->pos[0]+=amount;
    }
    if (dir == 's') {
        cam->pos[1]+=amount;
    }
}

void move_obj(mat3 *polys ,float dist,int indexOfAxe,long unsigned int size) {//TODO : change var name it's not really explicit
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < 3; ++j){
            polys[i][j][indexOfAxe] += dist;
        }
    }
}

void turn_cam(Camera *cam, char dir, float amount) {
    if (dir == 'y') {
        cam->angles[1] += amount;
        if (cam->angles[1] > 6.28) cam->angles[1] -= 6.28;
        if (cam->angles[1] < 0)    cam->angles[1] += 6.28;
    }
    if (dir == 'x') {
        cam->angles[0] += amount;
        if (cam->angles[0] > 6.28) cam->angles[0] -= 6.28;
        if (cam->angles[0] < 0)    cam->angles[0] += 6.28;
    }
    if (dir == 'z') {
        cam->angles[2] += amount;
        if (cam->angles[2] > 6.28) cam->angles[2] -= 6.28;
        if (cam->angles[2] < 0)    cam->angles[2] += 6.28;
    }
}