#include <signal.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "3DMotor.h"
#include<unistd.h>
#include "fileReader.h"
#include "OBJ_parser.h"
#include "cglm/cglm.h"
#include "Mechanical_arm.h"


vec3 light_vec={0.0F,0.0F,-1.0F};
//TODO : use typedef struct {struct objet} Camera; to extend object for exemple

void visual_proj_obj(SDL_Renderer *rendu,mat3 *polys,Camera *cam,mat4 *visual_proj,size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        vec3 vecN,vecA,vecB;
        glm_vec3_sub(polys[i][1],polys[i][0],vecA);
        glm_vec3_sub(polys[i][2],polys[i][0],vecB);
        for (int j = 0; j < 3; ++j){
            vecN[j]=vecA[(j+1)%3]*vecB[(j+2)%3]-vecA[(j+2)%3]*vecB[(j+1)%3];
        }
        //normalise vector : vecN = vecN / ||vecN||
        glm_vec3_normalize(vecN);
        double facing =
            vecN[0] * (polys[i][2][0] - cam->pos[0]) +
            vecN[1] * (polys[i][2][1] - cam->pos[1]) +
            vecN[2] * (polys[i][2][2] - cam->pos[2]);

        if (facing<0){
            double dotProduct=glm_vec3_dot(vecN,light_vec);
            //showing my vertex
            mat3 rep;
            triangle_final(polys[i],rep,visual_proj);
            SDL_Vertex test[3];
            for (int h = 0; h < 3; ++h){
                test[h].position.x = (rep[h][0]+0.5)*((float)screenW);
                test[h].position.y = (0.5-rep[h][1])*((float)screenH);
                test[h].color.r = dotProduct;
                test[h].color.g = dotProduct;
                test[h].color.b = dotProduct;
                test[h].color.a = 1.0;

                //lines to show the faces better
                SDL_RenderLine(rendu,
                    (rep[h][0]+0.5f)*screenW,
                    (0.5f-rep[h][1])*screenH,
                    (rep[(h+1)%3][0]+0.5f)*screenW,
                    (0.5f-rep[(h+1)%3][1])*screenH);

            }
            SDL_RenderGeometry(rendu, NULL, test, 3, NULL, 0);
        }
    }
}

//TODO : change name to something clearer
void proj_obj(mat3 *poly_in,Camera *cam,mat4 *visual_proj,SDL_Renderer *rendu,long unsigned int size){
    mat3 proj_angle;
    mat3 pol_copy[cptTriangles];
    //printf("%f %f %f",cam->angles[0],cam->angles[1],cam->angles[2]);
    mat3_rot_x( cam->angles[0],proj_angle);
    rotate_obj(proj_angle,poly_in,pol_copy, size);
    mat3_rot_y(cam->angles[1] ,proj_angle);
    rotate_obj(proj_angle,pol_copy,pol_copy, size);
    mat3_rot_z(cam->angles[2] ,proj_angle);
    rotate_obj(proj_angle,pol_copy,pol_copy, size);

    move_obj(pol_copy,10,2,size);//temporary move to see the object clearly
    //TODO:always moove by the parameter of the object ?
    visual_proj_obj(rendu,pol_copy,cam,visual_proj,size);
}

//TODO : cam in global variable ?
void sdlEventCommands(Camera *cam,SDL_Event *e,int *isOpen)
{
    if (e->type == SDL_EVENT_QUIT) {
        *isOpen=0;
    }
    if (e->type == SDL_EVENT_KEY_DOWN) {
        switch (e->key.key){
        case SDLK_ESCAPE:
            *isOpen=0;
            break;
            //camera rotation
        case SDLK_Q:
            turn_cam( cam, 'y', 0.03f);
            //projC2=calculCube(c2,&cam,proj3D);
            break;
        case SDLK_D:
            turn_cam( cam, 'y', -0.03f);
            break;
        case SDLK_Z:
            turn_cam( cam, 'x', 0.03f);
            //printf("angle %f \n",cam->angles[0]);
            break;
        case SDLK_S:
            turn_cam( cam, 'x', -0.03f);
            break;
        //TODO : camera moving forward, bakcward ...

        default:
            break;
        }
    }
}

bool screen_init(SDL_Window *fenetre,SDL_Renderer *rendu){
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return false;
    }
    if (!fenetre) {
        printf("Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    if (!rendu) {
        printf("Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return false;
    }
    SDL_SetRenderLogicalPresentation(rendu,screenW,screenH,SDL_LOGICAL_PRESENTATION_STRETCH);
    return true;
}

int main(int argc, char *argv[]) {
    //init screen
    SDL_Window *fenetre=SDL_CreateWindow("Ma fenêtre SDL",screenW, screenH,SDL_WINDOW_RESIZABLE);;
    SDL_Renderer *rendu = SDL_CreateRenderer(fenetre, "openGL");
    SDL_Event e;
    if (!screen_init(fenetre,rendu)) return 1;
    int isOpen = 0;

    //3D object init
    mat4 visual_proj;
    projectionMatrix(visual_proj);
    Camera cam = {{0,0,0},{0,0,0}};

    //creation of the triangles
    char* OBJfile = read3dFile();
    if (parser(OBJfile)==1)return 1;
    free(OBJfile);//TODO : maybe put it in the OBJfile
    mat3 pol_orig[cptTriangles];
    map1;


    arm_simulation();

    unsigned int coordSize=3*sizeof(double);
    for (int i = 0; i < cptTriangles; ++i){
        for (int y = 0; y < 3; ++y){
            unsigned int targetVertex = trianglesIndexs[i][y];
            memcpy(&pol_orig[i][y],//TODO : fix later with glm functions
                   &vertexList[targetVertex],
                   coordSize);
        }
    }

    proj_obj(pol_orig,&cam,&visual_proj,rendu,cptTriangles);//TODO:
    glm_vec3_normalize(light_vec);

    while (isOpen!=0)
    {
        //treat sdl events (windows interactions and keyboard for now)
        while (SDL_PollEvent(&e)) {
            sdlEventCommands(&cam,&e,&isOpen);
        }
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderClear(rendu);
        SDL_SetRenderDrawColor(rendu, 200, 200, 200, 255);
        proj_obj(pol_orig,&cam,&visual_proj,rendu,cptTriangles);//TODO: change rendu t english name
        SDL_RenderPresent(rendu);
        turn_cam( &cam, 'x', 0.03f);
        usleep(50000);
    }
    // 5. Libération de la mémoire et fermeture
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    //TODO : don't forget to free the memory that needs to be free
    return 0;
}
