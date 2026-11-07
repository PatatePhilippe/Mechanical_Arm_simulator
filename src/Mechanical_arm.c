//
// Created by pat on 04/11/2026.
//
#include "Mechanical_arm.h"
#include <stdio.h>
#include "cglm/vec3.h"

const float length=6;
const float length2=4;
mechanical_arm_part map1={
    {0,0,0},
    {0,0,0},
    {1,1,1},
    {0,0,0},
    {
    {{-1,-1,1},
    {1,-1,1},
    {-1,1,1}},

    {{1,-1,1},
    {1,1,1},
    {-1,1,1}},

    {{-1,-1,1+length},
    {1,-1,1+length},
    {-1,1,1+length}},

    {{1,-1,1+length},
    {1,1,1+length},
    {-1,1,1+length}},

    {{-1,-1,1+length},
    {1,-1,1+length},
    {1,-1,1}},

    {{1,-1,1},
    {-1,-1,1},
    {-1,-1,1+length}},

    {{1,1,1},
    {1,-1,1},
    {1,-1,1+length}},

    {{1,1,1},
    {1,-1,1+length},
    {1,1,1+length}}
    },
    6
};

mechanical_arm_part map2={
    {0,0,0},
    {0,0,0},
    {1,1,1},
    {0,0,0},
    {
        {{-1,-1,1},
        {1,-1,1},
        {-1,1,1}},

        {{1,-1,1},
        {1,1,1},
        {-1,1,1}},

        {{-1,-1,1+length2},
        {1,-1,1+length2},
        {-1,1,1+length2}},

        {{1,-1,1+length2},
        {1,1,1+length2},
        {-1,1,1+length2}},

        {{-1,-1,1+length2},
        {1,-1,1+length2},
        {1,-1,1}},

        {{1,-1,1},
        {-1,-1,1},
        {-1,-1,1+length2}},

        {{1,1,1},
        {1,-1,1},
        {1,-1,1+length2}},

        {{1,1,1},
        {1,-1,1+length2},
        {1,1,1+length2}}
    },
    6
};

void arm_simulation()
{

    vec3 point_init={0,0,1};
    vec3 point_final={3,5,0};

    double hypotenuse = sqrt(
        pow(point_final[0]-point_init[0],2)+
        pow(point_final[1]-point_init[1],2)+
        pow(point_final[2]-point_init[2],2)
        );
    double adjacent = sqrt(
    pow(point_final[1]-point_init[1],2)+
    pow(point_final[2]-point_init[2],2)
    );
    float base_angle = acosf(adjacent / hypotenuse);
    printf("base angle %f\n",base_angle);

    //point without the end of the arm which is straigth
    vec3 point_final_bis={3,5,2};

    float A=4;
    float B=6;
    double C=sqrt(pow(point_final_bis[0]-point_init[0],2)+
        pow(point_final_bis[1]-point_init[1],2)+
        pow(point_final_bis[2]-point_init[2],2));
    double D=sqrt(pow(point_final[0]-point_init[0],2)+
     pow(point_final[1]-point_init[1],2)+
     pow(point_final[2]-point_init[2],2));
    //how much is the arm exept the last stabilizing part above the ground
    float E=point_final_bis[2];
    //how much is the start of the arm is above ground
    float M=point_init[2];
    float N=E-M;
    //the point for the original angle
    vec3 point_final_rect={3,5,M};

    float K=sqrt(pow(point_final_rect[0]-point_init[0],2)+
     pow(point_final_rect[1]-point_init[1],2)+
     pow(point_final_rect[2]-point_init[2],2));

    float angleI=acosf((A*A)-(B*B)+(C*C)/(2.0F*A*C));
    float angleF=acosf((A*A)+(B*B)-(C*C)/(2.0F*A*B));
    float angleH=acosf((B*B)-(A*A)+(C*C)/(2.0F*B*C));
    float angleJ=acosf((N*N)-(K*K)+(C*C)/(2.0F*N*C));
    float angleG=acosf((K*K)-(N*N)+(C*C)/(2.0F*C*K));
    printf("%f",angleI);

    printf("I: %f F: %f (H,J: %f %f somme: %f\n",angleI,angleF,angleH,angleJ,angleJ+angleH);
    //1.248302I: 1.248302 F: 1.208773 (H,J: 0.684517 1.400950 somme: 2.085467
}

