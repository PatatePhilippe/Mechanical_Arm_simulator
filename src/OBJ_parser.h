//
// Created by pat on 28/10/2026.
//
#ifndef OBJ_parser
#define OBJ_parser
#include "cglm/ivec3.h"

typedef struct {
    unsigned int *verticules;
} triangle;

typedef struct {
    double coords[3];
} vertex;

extern ivec3 trianglesIndexs[500];
extern vec3 vertexList[300];
extern int cptTriangles;  // ou size_t selon votre type actuel
extern int cptVertexs;    // ou size_t selon votre type actuel
int parser(char* content);

#endif //OBJ_parser
