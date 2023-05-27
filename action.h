#pragma once
#include"main.h"
mat4 Identity(1.0);
void InitialModuleAngle()
{
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.005f;
	for (int i = 0; i < PARTNUM; i++)
	{
		ModuleMove[i] = mat4(1.0f);
	}
	//Body
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, 2, 0));
	//Head
	ModuleMove[Head] = translate(ModuleMove[Body], vec3(0, 1, 0));
	//Rigt up arm
	ModuleMove[RightUpperArm] = translate(ModuleMove[Body], vec3(0.6, 0.2, 0));
	//right low arm
	ModuleMove[RightLowerArm]= translate(ModuleMove[RightUpperArm], vec3(1.1 ,-0.9, 0));
	//right hand
	ModuleMove[RightHand] = translate(ModuleMove[RightLowerArm], vec3(0.9, -1.2, 0.2));
	
	//right tight
	ModuleMove[RightThigh] = translate(ModuleMove[Body], vec3(0.4, -2.5, 0.5));

	//right claf
	ModuleMove[RightCalf] = translate(ModuleMove[RightThigh], vec3(0.25, -1.7, -0.2));
	


	//left up arm
	ModuleMove[LeftUpperArm] = translate(ModuleMove[Body], vec3(-0.6, 0.2, 0));
	//ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(20), vec3(0, 0, 1));
	//left lower arm
	ModuleMove[LeftLowerArm] = translate(ModuleMove[LeftUpperArm], vec3(-1.1, -0.9, 0));
	//left hand
	ModuleMove[LeftHand] = translate(ModuleMove[LeftLowerArm], vec3(-0.9, -1.2, 0.2));
	//left tight
	ModuleMove[LeftThigh] = translate(ModuleMove[Body], vec3(-0.4, -2.5, 0.5));
	//left claf
	ModuleMove[LeftCalf] = translate(ModuleMove[LeftThigh], vec3(-0.2, -1.7, -0.3));

}
void walk1() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.005f;
	for (int i = 0; i < PARTNUM; i++)
	{
		ModuleMove[i] = mat4(1.0f);
	}
	//Body
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, 2, 0));
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, abs(cos(currentTime)) / 2, 0));
	//Head
	ModuleMove[Head] = translate(ModuleMove[Body], vec3(0, 1, 0));
	//Rigt up arm
	ModuleMove[RightUpperArm] = translate(ModuleMove[Body], vec3(0.6, 0.2, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-20), vec3(0, 0, 1));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(sin(currentTime)*70), vec3(1, 1, 0));
	//right low arm
	ModuleMove[RightLowerArm] = translate(ModuleMove[RightUpperArm], vec3(1.1, -0.9, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(angle[RightLowerArm]), vec3(1, 1, 0));
	//right hand
	ModuleMove[RightHand] = translate(ModuleMove[RightLowerArm], vec3(0.9, -1.2, 0.2));
	ModuleMove[RightHand] = rotate(ModuleMove[RightHand], deg2rad(angle[RightHand]), vec3(1, 0, 0));
	//right tight
	ModuleMove[RightThigh] = translate(ModuleMove[Body], vec3(0.4, -2.5, 0.5));
	ModuleMove[RightThigh] = rotate(ModuleMove[RightThigh], deg2rad(-sin(currentTime) * 50), vec3(1, 0, 0));
	//right claf
	ModuleMove[RightCalf] = translate(ModuleMove[RightThigh], vec3(0.25, -1.7, -0.2));
	ModuleMove[RightCalf] = rotate(ModuleMove[RightCalf], deg2rad(angle[RightCalf]), vec3(1, 0, 0));


	//left up arm
	ModuleMove[LeftUpperArm] = translate(ModuleMove[Body], vec3(-0.6, 0.2, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(20), vec3(0, 0, 1));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(-sin(currentTime) * 70), vec3(1, -1, 0));
	//left lower arm
	ModuleMove[LeftLowerArm] = translate(ModuleMove[LeftUpperArm], vec3(-1.1, -0.9, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(angle[LeftLowerArm]), vec3(1, 0, 0));
	//left hand
	ModuleMove[LeftHand] = translate(ModuleMove[LeftLowerArm], vec3(-0.9, -1.2, 0.2));
	ModuleMove[LeftHand] = rotate(ModuleMove[LeftHand], deg2rad(angle[LeftHand]), vec3(1, 0, 0));
	//left tight
	ModuleMove[LeftThigh] = translate(ModuleMove[Body], vec3(-0.4, -2.5, 0.5));
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftThigh], deg2rad(sin(currentTime) * 50), vec3(1, 0, 0));
	//left claf
	ModuleMove[LeftCalf] = translate(ModuleMove[LeftThigh], vec3(-0.2, -1.7, -0.3));
	ModuleMove[LeftCalf] = rotate(ModuleMove[LeftCalf], deg2rad(angle[LeftCalf]), vec3(1, 0, 0));
}
void jumpingJack2() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.005f;
	for (int i = 0; i < PARTNUM; i++)
	{
		ModuleMove[i] = mat4(1.0f);
	}
	//Body
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, 2, 0));
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, abs(cos(currentTime))/2, 0));
	//Head
	ModuleMove[Head] = translate(ModuleMove[Body], vec3(0, 1, 0));
	//Rigt up arm
	ModuleMove[RightUpperArm] = translate(ModuleMove[Body], vec3(0.6, 0.2, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(sin(currentTime) * 70+30), vec3(0, 0, 1));
	//right low arm
	ModuleMove[RightLowerArm] = translate(ModuleMove[RightUpperArm], vec3(1.1, -0.9, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(180), vec3(0, 1, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(-90), vec3(0, 0, 1));
	//right hand
	ModuleMove[RightHand] = translate(ModuleMove[RightLowerArm], vec3(0.9, -1.2, 0.2));
	ModuleMove[RightHand] = rotate(ModuleMove[RightHand], deg2rad(angle[RightHand]), vec3(1, 0, 0));
	//right tight
	ModuleMove[RightThigh] = translate(ModuleMove[Body], vec3(0.4, -2.5, 0.0));
	ModuleMove[RightThigh] = rotate(ModuleMove[RightThigh], deg2rad(sin(currentTime) * 20+20), vec3(0, 0, 1));
	//right claf
	ModuleMove[RightCalf] = translate(ModuleMove[RightThigh], vec3(0.25, -1.7, -0.2));
	ModuleMove[RightCalf] = rotate(ModuleMove[RightCalf], deg2rad(angle[RightCalf]), vec3(1, 0, 0));


	//left up arm
	ModuleMove[LeftUpperArm] = translate(ModuleMove[Body], vec3(-0.6, 0.2, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(-sin(currentTime) * 70 - 30), vec3(0, 0, 1));
	
	
	//left lower arm
	ModuleMove[LeftLowerArm] = translate(ModuleMove[LeftUpperArm], vec3(-1.1, -0.9, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(angle[LeftLowerArm]), vec3(1, 0, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(180), vec3(0, 1, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(90), vec3(0, 0, 1));
	//left hand
	ModuleMove[LeftHand] = translate(ModuleMove[LeftLowerArm], vec3(-0.9, -1.2, 0.2));
	ModuleMove[LeftHand] = rotate(ModuleMove[LeftHand], deg2rad(angle[LeftHand]), vec3(1, 0, 0));
	//left tight
	ModuleMove[LeftThigh] = translate(ModuleMove[Body], vec3(-0.4, -2.5, 0.0));
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftThigh], deg2rad(-sin(currentTime) * 20-20), vec3(0, 0, 1));
	//left claf
	ModuleMove[LeftCalf] = translate(ModuleMove[LeftThigh], vec3(-0.2, -1.7, -0.3));
	ModuleMove[LeftCalf] = rotate(ModuleMove[LeftCalf], deg2rad(angle[LeftCalf]), vec3(1, 0, 0));

}
void squat3() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.003f;
	for (int i = 0; i < PARTNUM; i++)
	{
		ModuleMove[i] = mat4(1.0f);
	}
	ModuleMove[RightCalf] = translate(ModuleMove[RightCalf], vec3(0.65, -2, 0));

	//R tigh
	ModuleMove[RightThigh] = rotate(ModuleMove[RightCalf], deg2rad(sin(currentTime)*45-45), vec3(1, 0, 0));
	ModuleMove[RightThigh] = translate(ModuleMove[RightThigh], vec3(-0.25, 1.7, 0.3));
	//BODY
	ModuleMove[Body] = rotate(ModuleMove[RightThigh], deg2rad(-sin(currentTime) * 60+60), vec3(1, 0, 0));
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(-0.4, 2.5, -0.5));
	//HEAD
	ModuleMove[Head] = translate(ModuleMove[Body], vec3(0, 1, 0));
	ModuleMove[Head] = rotate(ModuleMove[Head], deg2rad(sin(currentTime) * 20 -20 ), vec3(1, 0, 0));
	//R up arm
	ModuleMove[RightUpperArm] = translate(ModuleMove[Body], vec3(0.6, 0.2, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-30), vec3(0, 0, 1));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(sin(currentTime) * 30 - 30), vec3(1, 1, 0));
	//R lowe arm
	ModuleMove[RightLowerArm] = translate(ModuleMove[RightUpperArm], vec3(1.1, -0.9, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(sin(currentTime) * 45 - 22), vec3(1, 1, 0));
	//R hand 
	ModuleMove[RightHand] = translate(ModuleMove[RightLowerArm], vec3(0.9, -1.2, 0.2));
	ModuleMove[RightHand] = rotate(ModuleMove[RightHand], deg2rad(angle[RightHand]), vec3(1, 0, 0));

	//L Claf
	ModuleMove[LeftCalf] = translate(ModuleMove[LeftCalf], vec3(-0.65, -2, 0));
	//L Tigh
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftCalf], deg2rad(sin(currentTime) * 45 - 45), vec3(1, 0, 0));
	ModuleMove[LeftThigh] = translate(ModuleMove[LeftThigh], vec3(0.2, 1.7, 0.3));
	//L up arm
	ModuleMove[LeftUpperArm] = translate(ModuleMove[Body], vec3(-0.6, 0.2, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(30), vec3(0, 0, 1));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(sin(currentTime) * 30 - 30), vec3(1, -1, 0));
	//left lower arm
	ModuleMove[LeftLowerArm] = translate(ModuleMove[LeftUpperArm], vec3(-1.1, -0.9, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(sin(currentTime) * 45 - 22), vec3(1, -1, 0));
	//left hand
	ModuleMove[LeftHand] = translate(ModuleMove[LeftLowerArm], vec3(-0.9, -1.2, 0.2));
	ModuleMove[LeftHand] = rotate(ModuleMove[LeftHand], deg2rad(angle[LeftHand]), vec3(1, 0, 0));
}
float reminder = 0;
void moonWalk4() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.004f;
	for (int i = 0; i < PARTNUM; i++)
	{
		ModuleMove[i] = mat4(1.0f);
	}

	//Body
	if (reminder > 16) {
		reminder = 0;
	}
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(-8+ reminder, 2, 0));
	reminder += abs(cos(currentTime))*0.1;
	//ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, abs(cos(currentTime)) /6, 0));
	ModuleMove[Body] = rotate(ModuleMove[Body], deg2rad(-90), vec3(0, 1, 0));
	//Head
	ModuleMove[Head] = translate(ModuleMove[Body], vec3(0, 0.95, (sin(currentTime)+1.5)*0.15));
	//Rigt up arm
	ModuleMove[RightUpperArm] = translate(ModuleMove[Body], vec3(0.6, 0.2, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-20), vec3(0, 0, 1));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-sin(currentTime) * 15), vec3(1, 1, 0));
	//right low arm
	ModuleMove[RightLowerArm] = translate(ModuleMove[RightUpperArm], vec3(1.1, -0.9, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(angle[RightLowerArm]), vec3(1, 1, 0));
	//right hand
	ModuleMove[RightHand] = translate(ModuleMove[RightLowerArm], vec3(0.9, -1.2, 0.2));
	ModuleMove[RightHand] = rotate(ModuleMove[RightHand], deg2rad(angle[RightHand]), vec3(1, 0, 0));
	//right tight
	ModuleMove[RightThigh] = translate(ModuleMove[Body], vec3(0.4, -2.5, 0.5));
	ModuleMove[RightThigh] = rotate(ModuleMove[RightThigh], deg2rad(sin(currentTime) * 15 ), vec3(1, 0, 0));
	//right claf
	ModuleMove[RightCalf] = translate(ModuleMove[RightThigh], vec3(0.25, -1.7, -0.2));
	ModuleMove[RightCalf] = rotate(ModuleMove[RightCalf], deg2rad(sin(currentTime) * 15+15), vec3(1, 0, 0));


	//left up arm
	ModuleMove[LeftUpperArm] = translate(ModuleMove[Body], vec3(-0.6, 0.2, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(20), vec3(0, 0, 1));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(sin(currentTime) * 15), vec3(1, -1, 0));
	//left lower arm
	ModuleMove[LeftLowerArm] = translate(ModuleMove[LeftUpperArm], vec3(-1.1, -0.9, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(angle[LeftLowerArm]), vec3(1, 0, 0));
	//left hand
	ModuleMove[LeftHand] = translate(ModuleMove[LeftLowerArm], vec3(-0.9, -1.2, 0.2));
	ModuleMove[LeftHand] = rotate(ModuleMove[LeftHand], deg2rad(angle[LeftHand]), vec3(1, 0, 0));
	//left tight
	ModuleMove[LeftThigh] = translate(ModuleMove[Body], vec3(-0.4, -2.5, 0.5));
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftThigh], deg2rad(-sin(currentTime) * 15), vec3(1, 0, 0));
	//left claf
	ModuleMove[LeftCalf] = translate(ModuleMove[LeftThigh], vec3(-0.2, -1.7, -0.3));
	ModuleMove[LeftCalf] = rotate(ModuleMove[LeftCalf], deg2rad(-sin(currentTime) * 15 + 15), vec3(1, 0, 0));
}
void SitUps5() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.005f;
	for (int i = 0; i < PARTNUM; i++)
	{
		ModuleMove[i] = mat4(1.0f);
	}
	mat4 origin(1.0);
	//Body
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, -5, -5));
	ModuleMove[Body] = rotate(ModuleMove[Body], deg2rad(-90), vec3(1, 0, 0));
	origin = ModuleMove[Body];
	ModuleMove[Body] = rotate(ModuleMove[Body], deg2rad(sin(currentTime) * 45+45), vec3(1, 0, 0));
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, 2.5, -0.4));
	//Head
	ModuleMove[Head] = translate(ModuleMove[Body], vec3(0, 1, 0));
	//Rigt up arm
	ModuleMove[RightUpperArm] = translate(ModuleMove[Body], vec3(0.6, 0.2, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(20), vec3(0, 0, 1));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-120), vec3(1, 0, 0));

	//right low arm
	ModuleMove[RightLowerArm] = translate(ModuleMove[RightUpperArm], vec3(1.1, -0.9, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(-120), vec3(1, 1, 0));
	//right hand
	ModuleMove[RightHand] = translate(ModuleMove[RightLowerArm], vec3(0.9, -1.2, 0.2));
	//right tight
	ModuleMove[RightThigh] = translate(origin, vec3(0.4, -0.2, 0.5));
	ModuleMove[RightThigh] = rotate(ModuleMove[RightThigh], deg2rad(-60), vec3(1, 0, 0));
	//right claf
	ModuleMove[RightCalf] = translate(ModuleMove[RightThigh], vec3(0.25, -1.7, -0.2));
	ModuleMove[RightCalf] = rotate(ModuleMove[RightCalf], deg2rad(100), vec3(1, 0, 0));

	//left up arm
	ModuleMove[LeftUpperArm] = translate(ModuleMove[Body], vec3(-0.6, 0.2, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(-20), vec3(0, 0, 1));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(-120), vec3(1, 0, 0));
	//left lower arm
	ModuleMove[LeftLowerArm] = translate(ModuleMove[LeftUpperArm], vec3(-1.1, -0.9, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(-120), vec3(1, -1, 0));
	//left hand
	ModuleMove[LeftHand] = translate(ModuleMove[LeftLowerArm], vec3(-0.9, -1.2, 0.2));
	
	//left tight
	ModuleMove[LeftThigh] = translate(origin, vec3(-0.4, -0.2, 0.5));
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftThigh], deg2rad(-60), vec3(1, 0, 0));
	//left claf
	ModuleMove[LeftCalf] = translate(ModuleMove[LeftThigh], vec3(-0.2, -1.7, -0.3));
	ModuleMove[LeftCalf] = rotate(ModuleMove[LeftCalf], deg2rad(100), vec3(1, 0, 0));
}
void pushUp6() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.005f;
	for (int i = 0; i < PARTNUM; i++)
	{
		ModuleMove[i] = mat4(1.0f);
	}
	
	//R hand
	ModuleMove[RightHand] = translate(ModuleMove[RightHand], vec3(1.7, 0, -5));
	ModuleMove[RightHand] = rotate(ModuleMove[RightHand], deg2rad(100), vec3(0, 0, 1));
	ModuleMove[RightHand] = rotate(ModuleMove[RightHand], deg2rad(-90), vec3(1, 0, 0));
	//R lower arm
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightHand],deg2rad(sin(currentTime)*30-90), vec3(0, 0, 1));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(45), vec3(0, 1, 0));
	ModuleMove[RightLowerArm] = translate(ModuleMove[RightLowerArm], vec3(-0.9, 1.2, -0.2));
	//Body
	ModuleMove[Body] = rotate(ModuleMove[Body], deg2rad(90), vec3(1, 0, 0));
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, -5.2, sin(currentTime)-1.9));
	//R up arm
	ModuleMove[RightUpperArm] = translate(ModuleMove[Body], vec3(0.6, 0.2, 0.2));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(sin(currentTime)*40-40), vec3(1, 0, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-25), vec3(0, 0, 1));
	//Head
	ModuleMove[Head] = translate(ModuleMove[Body], vec3(0,1,0));
	//right tight
	ModuleMove[RightThigh] = translate(ModuleMove[Body], vec3(0.4, -2.5, 0.5));
	ModuleMove[RightThigh] = rotate(ModuleMove[RightThigh], deg2rad(sin(currentTime) * 10 -5), vec3(1, 0, 0));
	//right claf
	ModuleMove[RightCalf] = translate(ModuleMove[RightThigh], vec3(0.25, -1.7, -0.2));

	//L hand
	ModuleMove[LeftHand] = translate(ModuleMove[LeftHand], vec3(-1.7, 0, -5));
	ModuleMove[LeftHand] = rotate(ModuleMove[LeftHand], deg2rad(-100), vec3(0, 0, 1));
	ModuleMove[LeftHand] = rotate(ModuleMove[LeftHand], deg2rad(-90), vec3(1, 0, 0));
	//L lower arm
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftHand], deg2rad(-sin(currentTime) * 30 + 90), vec3(0, 0, 1));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(-45), vec3(0, 1, 0));
	ModuleMove[LeftLowerArm] = translate(ModuleMove[LeftLowerArm], vec3(0.9, 1.2, -0.2));

	
	//L up arm
	ModuleMove[LeftUpperArm] = translate(ModuleMove[Body], vec3(-0.6, 0.2, 0.2));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(sin(currentTime) * 40 - 40), vec3(1, 0, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(-25), vec3(0, 0, -1));
	
	//L tight
	ModuleMove[LeftThigh] = translate(ModuleMove[Body], vec3(-0.4, -2.5, 0.5));
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftThigh], deg2rad(sin(currentTime) * 10 - 5), vec3(1, 0, 0));
	//L claf
	ModuleMove[LeftCalf] = translate(ModuleMove[LeftThigh], vec3(-0.25, -1.7, -0.2));


}
void dance7() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.005f;
	for (int i = 0; i < PARTNUM; i++)
	{
		ModuleMove[i] = mat4(1.0f);
	}
	//Body
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, 2, -5));
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, abs(cos(currentTime)), 0));
	//Head
	ModuleMove[Head] = translate(ModuleMove[Body], vec3(0, 1, 0));
	//Rigt up arm
	ModuleMove[RightUpperArm] = translate(ModuleMove[Body], vec3(0.6, 0.2, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(20), vec3(0, 0, 1));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(50), vec3(1, -1, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-30), vec3(1, 0, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-60), vec3(1, 0, 0));
	
	//right low arm
	ModuleMove[RightLowerArm] = translate(ModuleMove[RightUpperArm], vec3(1.1, -0.9, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(-45), vec3(1, 1, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(-45), vec3(0, 0, 1));
	//right hand
	ModuleMove[RightHand] = translate(ModuleMove[RightLowerArm], vec3(0.9, -1.2, 0.2));
	ModuleMove[RightHand] = rotate(ModuleMove[RightHand], deg2rad(abs(cos(currentTime))*45-45), vec3(0, 0, 1));
	//right tight
	ModuleMove[RightThigh] = translate(ModuleMove[Body], vec3(0.4, -2.5, 0.5));
	ModuleMove[RightThigh] = rotate(ModuleMove[RightThigh], deg2rad(90), vec3(0, 1, 0));
	ModuleMove[RightThigh] = rotate(ModuleMove[RightThigh], deg2rad(sin(currentTime)*15 - 60), vec3(1, 0, 0));
	//right claf
	ModuleMove[RightCalf] = translate(ModuleMove[RightThigh], vec3(0.25, -1.7, -0.2));
	ModuleMove[RightCalf] = rotate(ModuleMove[RightCalf], deg2rad(-sin(currentTime) * 15+60), vec3(1, 0, 0));

	//left up arm
	ModuleMove[LeftUpperArm] = translate(ModuleMove[Body], vec3(-0.6, 0.2, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(-20), vec3(0, 0, 1));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(60), vec3(1, 1, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(-30), vec3(1, 0, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(-60), vec3(1, 0, 0));
	//left lower arm
	ModuleMove[LeftLowerArm] = translate(ModuleMove[LeftUpperArm], vec3(-1.1, -0.9, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(-45), vec3(1, -1, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(45), vec3(0, 0, 1));
	//left hand
	ModuleMove[LeftHand] = translate(ModuleMove[LeftLowerArm], vec3(-0.9, -1.2, 0.2));
	ModuleMove[LeftHand] = rotate(ModuleMove[LeftHand], deg2rad(-abs(cos(currentTime)) * 45 + 45), vec3(0, 0, 1));
	//left tight
	ModuleMove[LeftThigh] = translate(ModuleMove[Body], vec3(-0.4, -2.5, 0.5));
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftThigh], deg2rad(-90), vec3(0, 1, 0));
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftThigh], deg2rad(sin(currentTime) * 15 - 60), vec3(1, 0, 0));
	//left claf
	ModuleMove[LeftCalf] = translate(ModuleMove[LeftThigh], vec3(-0.2, -1.7, -0.3));
	ModuleMove[LeftCalf] = rotate(ModuleMove[LeftCalf], deg2rad(-sin(currentTime) * 15 + 60), vec3(1, 0, 0));
}
void dance8()
{
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.005f;
	for (int i = 0; i < PARTNUM; i++)
	{
		ModuleMove[i] = mat4(1.0f);
	}
	//Body
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, 2, -5));
	ModuleMove[Body] = translate(ModuleMove[Body], vec3(0, abs(cos(currentTime)), 0));
	//Head
	ModuleMove[Head] = translate(ModuleMove[Body], vec3(0, 1, 0));
	//Rigt up arm
	ModuleMove[RightUpperArm] = translate(ModuleMove[Body], vec3(0.6, 0.2, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(20), vec3(0, 0, 1));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(50), vec3(1, -1, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-30), vec3(1, 0, 0));
	ModuleMove[RightUpperArm] = rotate(ModuleMove[RightUpperArm], deg2rad(-60), vec3(1, 0, 0));

	//right low arm
	ModuleMove[RightLowerArm] = translate(ModuleMove[RightUpperArm], vec3(1.1, -0.9, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(-45), vec3(1, 1, 0));
	ModuleMove[RightLowerArm] = rotate(ModuleMove[RightLowerArm], deg2rad(-45), vec3(0, 0, 1));
	//right hand
	ModuleMove[RightHand] = translate(ModuleMove[RightLowerArm], vec3(0.9, -1.2, 0.2));
	ModuleMove[RightHand] = rotate(ModuleMove[RightHand], deg2rad(abs(cos(currentTime)) * 45 - 45), vec3(0, 0, 1));
	//right tight
	ModuleMove[RightThigh] = translate(ModuleMove[Body], vec3(0.4, -2.5, 0.5));
	ModuleMove[RightThigh] = rotate(ModuleMove[RightThigh], deg2rad(90), vec3(0, 1, 0));
	ModuleMove[RightThigh] = rotate(ModuleMove[RightThigh], deg2rad(sin(currentTime) * 15 - 60), vec3(1, 0, 0));
	//right claf
	ModuleMove[RightCalf] = translate(ModuleMove[RightThigh], vec3(0.25, -1.7, -0.2));
	ModuleMove[RightCalf] = rotate(ModuleMove[RightCalf], deg2rad(-sin(currentTime) * 15 + 60), vec3(1, 0, 0));

	//left up arm
	ModuleMove[LeftUpperArm] = translate(ModuleMove[Body], vec3(-0.6, 0.2, 0));
	ModuleMove[LeftUpperArm] = rotate(ModuleMove[LeftUpperArm], deg2rad(-90), vec3(1, 0, 0));
	

	//left lower arm
	ModuleMove[LeftLowerArm] = translate(ModuleMove[LeftUpperArm], vec3(-1.1, -0.9, 0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(-60), vec3(1,-1,0));
	ModuleMove[LeftLowerArm] = rotate(ModuleMove[LeftLowerArm], deg2rad(-currentTime*90), vec3(1, 3, 0));
	//left hand
	ModuleMove[LeftHand] = translate(ModuleMove[LeftLowerArm], vec3(-0.9, -1.2, 0.2));
	ModuleMove[LeftHand] = rotate(ModuleMove[LeftHand], deg2rad(currentTime * 90), vec3(0, 1, 0));
	//left tight
	ModuleMove[LeftThigh] = translate(ModuleMove[Body], vec3(-0.4, -2.5, 0.5));
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftThigh], deg2rad(-90), vec3(0, 1, 0));
	ModuleMove[LeftThigh] = rotate(ModuleMove[LeftThigh], deg2rad(sin(currentTime) * 15 - 60), vec3(1, 0, 0));
	//left claf
	ModuleMove[LeftCalf] = translate(ModuleMove[LeftThigh], vec3(-0.2, -1.7, -0.3));
	ModuleMove[LeftCalf] = rotate(ModuleMove[LeftCalf], deg2rad(-sin(currentTime) * 15 + 60), vec3(1, 0, 0));
}