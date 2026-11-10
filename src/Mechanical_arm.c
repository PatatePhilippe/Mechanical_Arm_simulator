//
// Created by pat on 04/11/2026.
//
#include "Mechanical_arm.h"
#include <stdio.h>
#include "cglm/vec3.h"

const float length=6;
const float length2=4;
const float length3=2;
const float diamArm=0.5;
mechanical_arm_part map1={
    {0,0,0},
    {0,1,0},
    {0,0,length},
    {0,0,0},
    {
        // Face inférieure (Z = 1) -> Normale vers le bas (0, 0, -1)
    {{-diamArm, diamArm, -1}, {diamArm, diamArm, -1}, {diamArm, -diamArm, -1}},
    {{-diamArm, diamArm, -1}, {diamArm, -diamArm, -1}, {-diamArm, -diamArm, -1}},

    // Face supérieure (Z = 1 + length) -> Normale vers le haut (0, 0, 1)
    {{-diamArm, -diamArm, -1 + length}, {diamArm, -diamArm, -1 + length}, {diamArm, diamArm, -1 + length}},
    {{-diamArm, -diamArm, -1 + length}, {diamArm, diamArm, -1 + length}, {-diamArm, diamArm, -1 + length}},

    // Face avant (Y = -1) -> Normale vers l'avant (0, -1, 0)
    {{-diamArm, -diamArm, -1}, {diamArm, -diamArm, -1}, {diamArm, -diamArm, -1 + length}},
    {{-diamArm, -diamArm, -1}, {diamArm, -diamArm, -1 + length}, {-diamArm, -diamArm, -1 + length}},

    // Face arrière (Y = 1) -> Normale vers l'arrière (0, 1, 0)
    {{diamArm, diamArm, -1}, {-diamArm, diamArm, -1}, {-diamArm, diamArm, -1 + length}},
    {{diamArm, diamArm, -1}, {-diamArm, diamArm, -1 + length}, {diamArm, diamArm, -1 + length}},

    // Face droite (X = 1) -> Normale vers la droite (1, 0, 0)
    {{diamArm, -diamArm, -1}, {diamArm, diamArm, -1}, {diamArm, diamArm, -1 + length}},
    {{diamArm, -diamArm, -1}, {diamArm, diamArm, -1 + length}, {diamArm, -diamArm, -1 + length}},

    // Face gauche (X = -1) -> Normale vers la gauche (-1, 0, 0)
    {{-diamArm, diamArm, -1}, {-diamArm, -diamArm, -1}, {-diamArm, -diamArm, -1 + length}},
    {{-diamArm, diamArm, -1}, {-diamArm, -diamArm, -1 + length}, {-diamArm, diamArm, -1 + length}}
    },
    6
};

mechanical_arm_part map2={
    {0,0,0},
    {0,0,0},
    {0,0,length},
    {0,0,0},
{
    // Face inférieure (Z = 1) -> Normale vers le bas (0, 0, -1)
            {{-diamArm, diamArm, -1}, {diamArm, diamArm, -1}, {diamArm, -diamArm, -1}},
            {{-diamArm, diamArm, -1}, {diamArm, -diamArm, -1}, {-diamArm, -diamArm, -1}},

            // Face supérieure (Z = 1 + length) -> Normale vers le haut (0, 0, 1)
            {{-diamArm, -diamArm, -1 + length2}, {diamArm, -diamArm, -1 + length2}, {diamArm, diamArm, -1 + length2}},
            {{-diamArm, -diamArm, -1 + length2}, {diamArm, diamArm, -1 + length2}, {-diamArm, diamArm, -1 + length2}},

            // Face avant (Y = -1) -> Normale vers l'avant (0, -1, 0)
            {{-diamArm, -diamArm, -1}, {diamArm, -diamArm, -1}, {diamArm, -diamArm, -1 + length2}},
            {{-diamArm, -diamArm, -1}, {diamArm, -diamArm, -1 + length2}, {-diamArm, -diamArm, -1 + length2}},

            // Face arrière (Y = 1) -> Normale vers l'arrière (0, 1, 0)
            {{diamArm, diamArm, -1}, {-diamArm, diamArm, -1}, {-diamArm, diamArm, -1 + length2}},
            {{diamArm, diamArm, -1}, {-diamArm, diamArm, -1 + length2}, {diamArm, diamArm, -1 + length2}},

            // Face droite (X = 1) -> Normale vers la droite (1, 0, 0)
            {{diamArm, -diamArm, -1}, {diamArm, diamArm, -1}, {diamArm, diamArm, -1 + length2}},
            {{diamArm, -diamArm, -1}, {diamArm, diamArm, -1 + length2}, {diamArm, -diamArm, -1 + length2}},

            // Face gauche (X = -1) -> Normale vers la gauche (-1, 0, 0)
            {{-diamArm, diamArm, -1}, {-diamArm, -diamArm, -1}, {-diamArm, -diamArm, -1 + length2}},
            {{-diamArm, diamArm, -1}, {-diamArm, -diamArm, -1 + length2}, {-diamArm, diamArm, -1 + length2}}
},
    4
};
mechanical_arm_part map3={
    {0,0,0},
    {0,0,0},
    {0,0,length},
{0,0,0},
{
    // Face inférieure (Z = 1) -> Normale vers le bas (0, 0, -1)
        {{-diamArm, diamArm, -1}, {diamArm, diamArm, -1}, {diamArm, -diamArm, -1}},
        {{-diamArm, diamArm, -1}, {diamArm, -diamArm, -1}, {-diamArm, -diamArm, -1}},

        // Face supérieure (Z = 1 + length) -> Normale vers le haut (0, 0, 1)
        {{-diamArm, -diamArm, -1 + length3}, {diamArm, -diamArm, -1 + length3}, {diamArm, diamArm, -1 + length3}},
        {{-diamArm, -diamArm, -1 + length3}, {diamArm, diamArm, -1 + length3}, {-diamArm, diamArm, -1 + length3}},

        // Face avant (Y = -1) -> Normale vers l'avant (0, -1, 0)
        {{-diamArm, -diamArm, -1}, {diamArm, -diamArm, -1}, {diamArm, -diamArm, -1 + length3}},
        {{-diamArm, -diamArm, -1}, {diamArm, -diamArm, -1 + length3}, {-diamArm, -diamArm, -1 + length3}},

        // Face arrière (Y = 1) -> Normale vers l'arrière (0, 1, 0)
        {{diamArm, diamArm, -1}, {-diamArm, diamArm, -1}, {-diamArm, diamArm, -1 + length3}},
        {{diamArm, diamArm, -1}, {-diamArm, diamArm, -1 + length3}, {diamArm, diamArm, -1 + length3}},

        // Face droite (X = 1) -> Normale vers la droite (1, 0, 0)
        {{diamArm, -diamArm, -1}, {diamArm, diamArm, -1}, {diamArm, diamArm, -1 + length3}},
        {{diamArm, -diamArm, -1}, {diamArm, diamArm, -1 + length3}, {diamArm, -diamArm, -1 + length3}},

        // Face gauche (X = -1) -> Normale vers la gauche (-1, 0, 0)
        {{-diamArm, diamArm, -1}, {-diamArm, -diamArm, -1}, {-diamArm, -diamArm, -1 + length3}},
        {{-diamArm, diamArm, -1}, {-diamArm, -diamArm, -1 + length3}, {-diamArm, diamArm, -1 + length3}}
    },
    2
};

vec3 point_init={0,1,0};
vec3 point_final={2,0,7};
vec3 point_final_bis={2,2,7};

void arm_simulation()
{


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
    //point without the end of the arm which is straigth


    float A=6;
    float B=4;
    double C=sqrt(pow(point_final_bis[0]-point_init[0],2)+
        pow(point_final_bis[1]-point_init[1],2)+
        pow(point_final_bis[2]-point_init[2],2));

    //how much is the arm exept the last stabilizing part above the ground
    float E=point_final_bis[1];
    //how much is the start of the arm is above ground
    float M=point_init[1];
    float N=E-M;
    //the point for the original angle
    vec3 point_final_rect={2,M,7};

    float K=sqrt(pow(point_final_rect[0]-point_init[0],2)+
     pow(point_final_rect[1]-point_init[1],2)+
     pow(point_final_rect[2]-point_init[2],2));

    float angleI=acosf(((A*A)-(B*B)+(C*C))/(2.0F*A*C));
    float angleF=acosf(((A*A)+(B*B)-(C*C))/(2.0F*A*B));
    float angleH=acosf(((B*B)-(A*A)+(C*C))/(2.0F*B*C));
    float angleJ=acosf(((N*N)-(K*K)+(C*C))/(2.0F*N*C));
    float angleG=acosf(((K*K)-(N*N)+(C*C))/(2.0F*C*K));

    printf("N %f",N);
    printf("base angle %f\n",base_angle);
    printf("angle premier bras %f\n",angleI+angleG);
    printf("angle deuxieme bras %f\n",angleF);
    printf("angle troisieme bras %f\n",angleH+angleJ);
    map1.angles[0]=-angleI-angleG;
    map1.angles[1]=-base_angle;
    map2.angles[0]=(3.14F-angleF)-angleI-angleG;
    map2.angles[1]=-base_angle;
    map3.angles[0]=((3.14F-(angleH+angleJ))+(3.14F-angleF)-angleI-angleG);
    map3.angles[1]=-base_angle;



    mat3 proj_angle;
    vec3 pos={0.0f,0.0f,6.0f};
    vec3 pos_end={0.0f,0.0f,4.0f};

    //calculation for the starting point of the next arm and the last one
    //it rotate the end point to make the first arm move with the second one
    mat3_rot_x(-angleI-angleG,proj_angle);
    glm_mat3_mulv(proj_angle,pos,pos);
    mat3_rot_y(-base_angle,proj_angle);
    glm_mat3_mulv(proj_angle,pos,pos);
    map2.pos[0]=pos[0];
    map2.pos[1]=pos[1];
    map2.pos[2]=pos[2];
    //calculation for the starting point of the next arm
    //it rotate the end point to make the first arm move with the second one
    mat3_rot_x((3.14F-angleF)-angleI-angleG,proj_angle);
    glm_mat3_mulv(proj_angle,pos_end,pos_end);
    mat3_rot_y(-base_angle,proj_angle);
    glm_mat3_mulv(proj_angle,pos_end,pos_end);
    map3.pos[0]=pos_end[0]+pos[0];
    map3.pos[1]=pos_end[1]+pos[1];
    map3.pos[2]=pos_end[2]+pos[2];




    //printf("I: %f F: %f (H,J: %f %f somme: %f\n",angleI,angleF,angleH,angleJ,angleJ+angleH);
    //1.248302I: 1.248302 F: 1.208773 (H,J: 0.684517 1.400950 somme: 2.085467
}

