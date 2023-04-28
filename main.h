#pragma once
#include"glew.h"
#include"freeglut.h"
#include"glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include<iostream>
#include <fstream>
#include<sstream>
#include <vector>

#define deg2rad(x) ((x)*((3.1415926f)/(180.0f)))
#define rad2deg(x) ((180.0f) / ((x)*(3.1415926f)))
#define PARTNUM 2
using namespace std;
using namespace glm;
GLuint program;
GLuint mvLocation;
GLuint projLocation;
GLuint scaleLocation;
GLuint viewLocation;
vector<unsigned int>element;
vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -2.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
mat4 view(1.0);
mat4 projMatrix(1.0);
mat4 scaleMatrix(1.0);
int width = 600,  height = 600;
float aspect = width / height;
float BK = 1.0f;
float timeColor = 0;
float fov = 50.0f;
int VBOsSIZE[PARTNUM] = { NULL };//VBOs個編號使用的記憶體大小
int EBOsSIZE[PARTNUM] = { NULL };//EBOs個編號使用的記憶體大小
int offset[3] = { 0 };
int totalSize[3] = { 0 };
GLuint VAO;
GLuint VAOs[PARTNUM] = { NULL };
GLuint VBO;
GLuint VBOs[PARTNUM] ;
GLuint EBO;
GLuint EBOs[PARTNUM];

