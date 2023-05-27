#pragma once
#include"GL/glew.h"
#include"GL/freeglut.h"
#include"GLM/glm/glm.hpp"
#include"GLM/glm/gtc/matrix_transform.hpp"
#include"GLM/glm/mat4x4.hpp"
#include<iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include<map>

#define deg2rad(x) ((x)*((3.1415926f)/(180.0f)))
#define rad2deg(x) ((180.0f) / ((x)*(3.1415926f)))
#define PARTNUM 12
#define IDLE 0;
#define WALK 1;
#define JUMPINGINGJACK 2;
#define SQUAT 3;
#define MOONWALK 4;
#define SITUPS 5;
#define PUSHUPS 6;
#define DANCE 7;
#define DANCE_2 8;
using namespace std;
using namespace glm;
GLuint drawingmode = GL_TRIANGLES;
bool displaySkyBox = true;
bool roundMode = false;

unsigned int loadCubemap(vector<std::string> faces);
unsigned int skyboxVAO, skyboxVBO, cubemapTexture;
GLuint program;
GLuint program2;
GLuint mvLocation;
GLuint projLocation;
GLuint scaleLocation;
GLuint viewLocation;
GLuint KaLocation;
GLuint KdLocation;
GLuint KsLocation;
vector<unsigned int>element;
vec3 cameraPos = vec3(0.0f, 0.0f, 30.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -2.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
mat4 view(1.0);
mat4 projMatrix(1.0);
mat4 scaleMatrix(1.0);
int width = 600,  height = 600;
float aspect = width / height;
float BK = 1.0f;
float timeColor = 0;
float fov = 20.0f;
int VBOsSIZE[PARTNUM] ;//VBOs個編號使用的記憶體大小
int EBOsSIZE[PARTNUM] ;//EBOs個編號使用的記憶體大小
int offset[3] = { 0 };
int totalSize[3] = { 0 };

GLuint VAOs[PARTNUM];
GLuint VBOs[PARTNUM];
GLuint EBOs[PARTNUM];
GLuint nEBOs[PARTNUM];

GLuint uVAOs[PARTNUM];
GLuint uVBOs[PARTNUM];

GLuint nVAOs[PARTNUM];
GLuint nVBOs[PARTNUM];
vector<string> material[PARTNUM];
map<string, vec3> KAs;//mtl-name&Ka
map<string, vec3> KDs;//mtl-name&Kd
map<string, vec3> KSs;//mtl-name&Ks
mat4 ModuleMove[PARTNUM];
float angle[PARTNUM] ;
int action;
enum robotparts
{
	Body = 0,
	Head = 1,
	RightUpperArm = 2,
	RightLowerArm = 3,
	RightHand = 4,
	LeftUpperArm = 5,
	LeftLowerArm = 6,
	LeftHand = 7,
	RightThigh = 8,
	RightCalf = 9,
	LeftThigh = 10,
	LeftCalf = 11
};
