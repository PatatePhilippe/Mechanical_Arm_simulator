#define ALEXER_IMPLEMENTATION
#include <stdio.h>
#include <alexer.h>
#include <unistd.h>

#include <errno.h>
#include "OBJ_parser.h"

#include "cglm/ivec3.h"

typedef enum {
    PUNCT_POINT,
    PUNCT_MINUS,
    PUNCT_DOUBLE_SLASH,
    COUNT_PUNCTS,
} Punct_Index;

static_assert(COUNT_PUNCTS == 3, "Amount of puncts have changed");
const char *puncts[COUNT_PUNCTS] = {
    [PUNCT_POINT]           = ".",
    [PUNCT_MINUS]           = "-",
    [PUNCT_DOUBLE_SLASH]    = "//",
};

typedef enum {
    KEYWORD_POINT,
    KEYWORD_NORMAL,
    KEYWORD_VERTEX,
    KEYWORD_S,
    KEYWORD_MTL,
    KEYWORD_G,
    KEYWORD_USE,
    COUNT_KEYWORDS,
} Keyword_Index;

static_assert(COUNT_KEYWORDS == 7, "Amount of keywords have changed");
const char *keywords[COUNT_KEYWORDS] ={
    [KEYWORD_POINT]      = "v",
    [KEYWORD_NORMAL]     = "vn",
    [KEYWORD_VERTEX]     = "f",
    [KEYWORD_G]          = "g",
    [KEYWORD_S]          = "s",
    [KEYWORD_MTL]        = "mtllib",
    [KEYWORD_USE]        = "usemtl",
};


const char *sl_comments[] = {
    "#"
};

typedef struct {
    Alexer lexer;
    Alexer_Token token;
    vertex *vertices;
    char *file_material;//TODO : change name later when used
    char *usage_material;//TODO : change name later when used
    size_t vertex_count;
    size_t vertex_capacity;
} Parsed_object;


uint64_t start_tokens[]={ALEXER_ID(ALEXER_KEYWORD,KEYWORD_VERTEX),
                        ALEXER_ID(ALEXER_KEYWORD,KEYWORD_MTL),
                        ALEXER_ID(ALEXER_KEYWORD,KEYWORD_G),
                        ALEXER_ID(ALEXER_KEYWORD,KEYWORD_NORMAL),
                        ALEXER_ID(ALEXER_KEYWORD,KEYWORD_POINT),
                        ALEXER_ID(ALEXER_KEYWORD,KEYWORD_VERTEX),
                        ALEXER_ID(ALEXER_KEYWORD,KEYWORD_S),
                        ALEXER_ID(ALEXER_KEYWORD,KEYWORD_USE),
                        ALEXER_END};
uint64_t start_double[]={ALEXER_ID(ALEXER_PUNCT,PUNCT_MINUS),
                        ALEXER_INT};


ivec3 trianglesIndexs[500] = {0};
vec3 vertexList[300] = {0};
int cptTriangles = 0;
int cptVertexs = 0;

bool double_parser(float *output,Alexer_Token *t,Alexer *l){
    bool signed_bool=false;
    if (t->id==ALEXER_ID(ALEXER_PUNCT,PUNCT_MINUS)){
        alexer_get_token(l, t );
        signed_bool=true;
    }
    if (!(alexer_expect_id(l,*t, ALEXER_INT))) return false;

    char whole_number[t->end - t->begin];
    memcpy(&whole_number,t->begin,(t->end - t->begin)*sizeof(char));
    alexer_get_token(l, t );

    if (!alexer_expect_id(l,*t,ALEXER_ID(ALEXER_PUNCT,PUNCT_POINT))) return false ;
    alexer_get_token(l, t );

    if (!alexer_expect_id(l,*t,ALEXER_INT)) return false;
    char decimal_number[t->end - t->begin];
    memcpy(&decimal_number,t->begin,(t->end - t->begin)*sizeof(char));

    char str[32];
    snprintf(str, sizeof(str), "%s.%s", whole_number,decimal_number);
    *output = strtod(str, NULL);
    if (signed_bool) *output*=-1;
    return true;
}

bool polygon_parser(Alexer_Token *t,Alexer *l){

    unsigned int tempPos[5];
    for (int index = 0; index < 3; ++index){

        if (!(alexer_expect_id(l,*t, ALEXER_INT)))return false;
        char p1[t->end - t->begin];
        memcpy(&p1,t->begin,(t->end - t->begin)*sizeof(char));
        tempPos[index]=(int)strtol(p1, NULL, 10)-1;
        alexer_get_token(l, t );

        if (!alexer_expect_id(l,*t,ALEXER_ID(ALEXER_PUNCT,PUNCT_DOUBLE_SLASH)))return false;
        alexer_get_token(l, t );
        if (!(alexer_expect_id(l,*t, ALEXER_INT))) return false;
        alexer_get_token(l, t );
    }
    if (t->id==ALEXER_INT){

        if (!(alexer_expect_id(l,*t, ALEXER_INT))) return false;
        char p1[t->end - t->begin];
        memcpy(&p1,t->begin,(t->end - t->begin)*sizeof(char));
        tempPos[3]=(int)strtol(p1, NULL, 10)-1;
        alexer_get_token(l, t );
        if (!alexer_expect_id(l,*t,ALEXER_ID(ALEXER_PUNCT,PUNCT_DOUBLE_SLASH))) return false;
        alexer_get_token(l, t );
        if (!(alexer_expect_id(l,*t, ALEXER_INT))) return false;
        //TODO temporary method because i assumed that there was only triangles in the polygon parser check what are the polygons possible an make a more robust solution
        alexer_get_token(l, t );

        if (t->id==ALEXER_INT){
            if (!(alexer_expect_id(l,*t, ALEXER_INT))) return false;
            char p1[t->end - t->begin];
            memcpy(&p1,t->begin,(t->end - t->begin)*sizeof(char));
            tempPos[4]=(int)strtol(p1, NULL, 10)-1;
            alexer_get_token(l, t );
            if (!alexer_expect_id(l,*t,ALEXER_ID(ALEXER_PUNCT,PUNCT_DOUBLE_SLASH))) return false;
            alexer_get_token(l, t );
            if (!(alexer_expect_id(l,*t, ALEXER_INT))) return false;
            alexer_get_token(l, t );
            //calculation of a new average point a the center of the polygone to divide him into triangles

            
            trianglesIndexs[cptTriangles][0]=tempPos[0];
            trianglesIndexs[cptTriangles][1]=tempPos[1];
            trianglesIndexs[cptTriangles][2]=tempPos[3];
            cptTriangles++;
            trianglesIndexs[cptTriangles][0]=tempPos[1];
            trianglesIndexs[cptTriangles][1]=tempPos[2];
            trianglesIndexs[cptTriangles][2]=tempPos[3];
            cptTriangles++;
            trianglesIndexs[cptTriangles][0]=tempPos[3];
            trianglesIndexs[cptTriangles][1]=tempPos[4];
            trianglesIndexs[cptTriangles][2]=tempPos[0];
            cptTriangles++;
        }else{
            memcpy(trianglesIndexs[cptTriangles],&tempPos,3*sizeof(unsigned int));
            cptTriangles++;
            trianglesIndexs[cptTriangles][0]=tempPos[2];
            trianglesIndexs[cptTriangles][1]=tempPos[3];
            trianglesIndexs[cptTriangles][2]=tempPos[0];
            cptTriangles++;

        }
    }else{
        if(!alexer_expect_one_of_ids(l,*t,start_tokens,9))return false;
        memcpy(trianglesIndexs[cptTriangles],&tempPos,3*sizeof(unsigned int));//TODO : replace with vec copy
        cptTriangles++;
    }
    return true;
}

//TODO : change name to it's usage later
bool g_parser(Alexer_Token *t,Alexer *l){//TODO : the result is verified but not used for now
    if (!alexer_expect_id(l,*t,ALEXER_SYMBOL)) return false;
    alexer_get_token(l, t );
    if (!alexer_expect_id(l,*t,ALEXER_ID(ALEXER_PUNCT,PUNCT_POINT))) return false;
    alexer_get_token(l, t );
    if (!alexer_expect_id(l,*t, ALEXER_INT)) return false;
    alexer_get_token(l, t );
    return true;
}//TODO : the result is verified but not used for now

bool material_file_parser(Alexer_Token *t,Alexer *l){
    if (!alexer_expect_id(l,*t,ALEXER_SYMBOL)) return false;
    alexer_get_token(l, t );
    if (!alexer_expect_id(l,*t,ALEXER_ID(ALEXER_PUNCT,PUNCT_POINT))) return false;
    alexer_get_token(l, t );
    if (!alexer_expect_id(l,*t, ALEXER_SYMBOL)) return false;
    if (access("../Goldfish_01.mtl", F_OK) != 0) {
        puts( strerror( errno ) );
        //return false;//TODO : change the path part later
    }
    alexer_get_token(l, t );
    return true;
}//TODO : the result is verified but not used for now

bool material_usage_parser(Alexer_Token *t,Alexer *l){
    while (ALEXER_KIND(t->id)!=ALEXER_KEYWORD && ALEXER_KIND(t->id)!=ALEXER_END)
    {
        alexer_get_token(l, t );
    }
    return true;
}//TODO : the result is not verified and not used for now

bool vertex_parser(Alexer_Token *t,Alexer *l){
    for (int i = 0; i < 3; ++i)
    {
        if (!double_parser(&vertexList[cptVertexs][i],t,l))return false;
        //printf("%f \n",vertexList[cptVertexs].coords[i]);
        alexer_get_token(l, t );
    }
    cptVertexs+=1;
    return true;
    //printf(" doubles : %f %f %f",x,y,z);
}

//TODO : change name to it's usage later
bool s_parser(Alexer_Token *t,Alexer *l){
    //l->diagf(t->loc, "ERROR verif", "%s: %.*s \n", alexer_kind_name(ALEXER_KIND(t->id)),t->end - t->begin, t->begin);
    alexer_get_token(l, t );
    return true;
}//TODO : the result is not verified and not used for now

bool normal_parser(Alexer_Token *t,Alexer *l){
    float tempNormal[3];
    for (int i = 0; i < 3; ++i)
    {
        if (!double_parser(&tempNormal[i],t,l))return false;
        alexer_get_token(l, t );
    }
    return true;
}//TODO : the result is verified and not used for now

void parser_init(Parsed_object *p,char *content){
    const char *file_path = "example/path"; // The file path is only needed for diagnostic message
    p->lexer=alexer_create(file_path, content, strlen(content));
    p->lexer.puncts = puncts;
    p->lexer.puncts_count = ALEXER_ARRAY_LEN(puncts);
    p->lexer.keywords = keywords;
    p->lexer.keywords_count = ALEXER_ARRAY_LEN(keywords);
    p->lexer.sl_comments = sl_comments;
    p->lexer.sl_comments_count = ALEXER_ARRAY_LEN(sl_comments);

}

int parser(char *content){
    Parsed_object p;
    parser_init(&p,content);
    bool end=false;
    //TODO: make a real init with the parser object
    uint64_t cmdToken2 = 0;
    alexer_get_token(&p.lexer, &p.token );
    while (!end){
        if (!alexer_expect_one_of_ids(&p.lexer,p.token,start_tokens,9)) return 1;

        switch (ALEXER_KIND(p.token.id)){
            case  ALEXER_KEYWORD:
                p.lexer.diagf(p.token.loc, "COMMANDE", "%s: %.*s \n", alexer_kind_name(ALEXER_KIND(p.token.id)),p.token.end - p.token.begin, p.token.begin);
                cmdToken2=p.token.id;
                alexer_get_token(&p.lexer, &p.token );
                switch (cmdToken2){
                    case ALEXER_ID(ALEXER_KEYWORD,KEYWORD_VERTEX):
                        if (!polygon_parser(&p.token,&p.lexer)) return 1;
                        break;
                    case ALEXER_ID(ALEXER_KEYWORD,KEYWORD_G):
                        if (!g_parser(&p.token,&p.lexer)) return 1;
                        break;
                    case ALEXER_ID(ALEXER_KEYWORD,KEYWORD_MTL):
                        if (!material_file_parser(&p.token,&p.lexer)) return 1;
                        break;
                    case ALEXER_ID(ALEXER_KEYWORD,KEYWORD_USE):
                        if (!material_usage_parser(&p.token,&p.lexer)) return 1;
                        break;
                    case ALEXER_ID(ALEXER_KEYWORD,KEYWORD_POINT):
                        if (!vertex_parser(&p.token,&p.lexer)) return 1;
                        break;
                    case ALEXER_ID(ALEXER_KEYWORD,KEYWORD_S):
                        if (!s_parser(&p.token,&p.lexer)) return 1;
                        break;
                    case ALEXER_ID(ALEXER_KEYWORD,KEYWORD_NORMAL):
                        if (!normal_parser(&p.token,&p.lexer)) return 1;
                        break;
                    default:
                        printf("error");
                        break;
                }
                break;
            case ALEXER_END:
                end = true;
                break;
            default:
                p.lexer.diagf(p.token.loc, "DONNEE", "%s: %.*s", alexer_kind_name(ALEXER_KIND(p.token .id)),
                       p.token.end - p.token.begin, p.token.begin);
                break;
        }
    }
    //TODO : free memory
    return 0;
}