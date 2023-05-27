#include "main.h"
#include "action.h"
#include"Module.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
const char* vsSource = R"glsl(
	#version 400
	uniform mat4 projMatrix;
	uniform mat4 view;
	uniform mat4 scaleMatrix;
	uniform mat4 mvMatrix;
	layout (location = 0) in vec3 position;
	layout (location = 1) in vec3 vertexNormal;
	vec3 vLightPosition = vec3(0,0,-1);
	out vec3 vVaryingNormal;
	out vec3 vVaryingLightDir;
	
	out vec3 FragPos; 
	out vec3 Normal;
	
	void main()
	{
		FragPos = vec3(view*mvMatrix * vec4(position, 1.0));
		Normal = vertexNormal;

			
		gl_Position =  normalize(projMatrix*view*mvMatrix*scaleMatrix * vec4(position,1.0));
		
		mat4 MV = view*mvMatrix;
		mat3 normalMatrix = mat3(MV);
		vVaryingNormal = normalMatrix * vertexNormal;
		vec4 vPosition4 = MV * vec4(position,1);
		vec3 vPosition3 = vPosition4.xyz / vPosition4.w;
		
		vVaryingLightDir = normalize(vLightPosition - vPosition3);
		
	}
)glsl";
const char* fsSource = R"glsl(
	#version 400

	uniform vec3 Ka;
	uniform vec3 Kd;
	uniform vec3 Ks;
	out vec4  color;
	//lighting color
	vec4    ambientColor = vec4(0.1,0.1,0.1,1);
	vec4    diffuseColor = vec4(0.8,0.8,0.8,1);   
	vec4    specularColor = vec4(1,1,1,1);
	in vec3 vVaryingNormal;
	in vec3 vVaryingLightDir;
	in vec2 UV;
	float Shininess = 256.0;//for material specular

	in vec3 FragPos;
	in vec3 Normal;
	vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);
	void main()
	{
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * vec3(1,1,1);
		float ambientStrength = 0.1;
		vec3 ambient = vec3(0.1,0.1,0.1);

		vec3 result = (ambient + diffuse) * Kd;
		color = vec4(result, 1.0);
	}
)glsl";
const char* SkyBoxVsSource = R"glsl(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	out vec3 TexCoords;
	uniform mat4 projMatrix;
	uniform mat4 view;

	void main()
	{
		TexCoords = aPos;
		vec4 pos = projMatrix * view * vec4(aPos, 1.0);
		gl_Position = pos.xyww;
	}  
)glsl";
const char* SkyBoxFsSource = R"glsl(
	#version 400
	out vec4 FragColor;
	in vec3 TexCoords;
	uniform samplerCube skybox;
	void main()
	{    
		FragColor = texture(skybox, TexCoords);
	}
)glsl";
unsigned int loadCubemap(vector<string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
void myInit()
{
	glClearColor(BK, BK, BK, 1.0f);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	//Initialize shaders
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(vs);
	glCompileShader(fs);
	GLchar info[512];
	cout << "vs" << endl;
	glGetShaderInfoLog(vs, 512, NULL, info);
	printf("%s", info);
	cout << "fs" << endl;
	glGetShaderInfoLog(fs, 512, NULL, info);
	printf("%s", info);
	//Attach Shader to program
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glUseProgram(program);
	///
	cout << "元件總數 " << PARTNUM << endl << endl;
	LoadMTLFile("./robotParts/material.mtl");
	Module body("./robotParts/body.obj", Body);
	Module head("./robotParts/head.obj", Head);
	Module right_top_arm("./robotParts/right_top_arm.obj", RightUpperArm);
	Module right_down_arm("./robotParts/right_down_arm.obj", RightLowerArm);
	Module right_hand("./robotParts/right_hand.obj", RightHand);
	Module left_top_arm("./robotParts/left_top_arm.obj", LeftUpperArm);
	Module left_down_arm("./robotParts/left_down_arm.obj", LeftLowerArm);
	Module left_hand("./robotParts/left_hand.obj", LeftHand);
	Module right_top_leg("./robotParts/right_top_leg.obj", RightThigh);
	Module right_leg("./robotParts/right_leg.obj", RightCalf);
	Module left_top_leg("./robotParts/left_top_leg.obj", LeftThigh);
	Module left_leg("./robotParts/left_leg.obj", LeftCalf);
	// 
	// 
	//0 for VBO //1 for EBO 
	/*for (int i = 0; i < PARTNUM; i++) 
	{
		totalSize[0] += VBOsSIZE[i];
		totalSize[1] += EBOsSIZE[i];
	}
	cout <<"總面數 " << totalSize[1] / sizeof(Face) << endl;*/

	

	mvLocation = glGetUniformLocation(program, "mvMatrix");
	projLocation = glGetUniformLocation(program, "projMatrix");
	scaleLocation = glGetUniformLocation(program, "scaleMatrix");
	viewLocation = glGetUniformLocation(program, "view");
	KaLocation = glGetUniformLocation(program, "Ka");
	KdLocation = glGetUniformLocation(program, "Kd");
	KsLocation = glGetUniformLocation(program, "Ks");
	InitialModuleAngle();
}
void InitSkyBox()
{
	cout << "InitSkyBox Shader" << endl;
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vs, 1, &SkyBoxVsSource, NULL);
	glShaderSource(fs, 1, &SkyBoxFsSource, NULL);
	glCompileShader(vs);
	glCompileShader(fs);
	GLchar info[512];
	glGetShaderInfoLog(vs, 512, NULL, info);
	printf("%s", info);
	glGetShaderInfoLog(fs, 512, NULL, info);
	printf("%s", info);
	//Attach Shader to program
	program2 = glCreateProgram();
	glAttachShader(program2, vs);
	glAttachShader(program2, fs);
	glLinkProgram(program2);
	glUseProgram(program2);
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	vector<string> faces
	{
		"skybox/right.jpg",
		"skybox/left.jpg",
		"skybox/top.jpg",
		"skybox/bottom.jpg",
		"skybox/front.jpg",
		"skybox/back.jpg"
	};
	//set skybox vao vbo 
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//
	cubemapTexture = loadCubemap(faces);
}
void My_Display()
{
	
	glutPostRedisplay();
	glClearColor(BK, BK, BK, 1.0f);
	
	glUseProgram(program);
	if (roundMode)
	{
		float radius = 10.0f;
		float camX = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * radius;
		float camZ = cos(glutGet(GLUT_ELAPSED_TIME) * 0.001) * radius;
		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	}
	else
	{
		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}
	
	scaleMatrix = scale(scaleMatrix, vec3(1, 1, 1));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.01f;
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projMatrix[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(scaleLocation, 1, GL_FALSE, &scaleMatrix[0][0]);
	for (int i = 0; i < PARTNUM; i++) 
	{
		glUniformMatrix4fv(mvLocation, 1, GL_FALSE, &ModuleMove[i][0][0]);
		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
	
		glBindBuffer(GL_ARRAY_BUFFER, nVBOs[i]);
		
		int drawingOffset = 0;
		
		string currentUsingMaterial;
		for (int j = 0; j < material[i].size(); j++)
		{
			
			currentUsingMaterial = material[i][j];
			glUniform3fv(KaLocation, 1, &KAs[currentUsingMaterial][0]);
			glUniform3fv(KdLocation, 1, &KDs[currentUsingMaterial][0]);
			glUniform3fv(KsLocation, 1, &KSs[currentUsingMaterial][0]);
			glDrawElements(drawingmode, 3, GL_UNSIGNED_INT, (void*)(drawingOffset * 3 * sizeof( int)));
			drawingOffset++;

		}
		
	}
	if (displaySkyBox)
	{
		glDepthFunc(GL_LEQUAL);  
		glUseProgram(program2);
		view = mat4(mat3(view));
		glUniformMatrix4fv(glGetUniformLocation(program2, "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program2, "projMatrix"), 1, GL_FALSE, &projMatrix[0][0]);
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); 
	}
	
	///////////////////////////	
	glutSwapBuffers();
	//system("pause");
}
void My_Reshape(int width, int height)
{
	float aspect = width / height;
	glViewport(0, 0, width, height);
	projMatrix = perspective(deg2rad(fov), aspect, 0.1f, 100.0f);
}
void keyin(unsigned char key, int x, int y)
{

	float cameraSpeed = 0.1;
	float speed = 5;
	switch (key)
	{
	
	case 'w':
		cameraPos += speed*cameraSpeed * cameraFront;
		cout << "press" << endl;
		break;
	case 'a':
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		cout << "press" << endl;
		break;
	case 's':
		cameraPos -= speed*cameraSpeed * cameraFront;
		cout << "press" << endl;
		break;
	case 'd':
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		cout << "press" << endl;
		break;
	default:
		break;
	}
}
float yaw;
float pitch;
float lastX=0 , lastY=0 ;
bool first = true;
float xoffset ;
float yoffset ;
void myMouse(int button, int state, int x, int y)
{
	
	if (button == GLUT_LEFT_BUTTON)
	{

		if (state == GLUT_DOWN)
		{
			lastX = x;
			lastY = y;
		}
	}
	else if (button == 3)
	{
		if (fov > 5) {
			fov -= 5;
			projMatrix = perspective(deg2rad(fov), aspect, 0.1f, 100.0f);
			//cout << fov << endl;
		}
			
		
	}
	else if (button == 4)
	{
		if (fov < 95) {
			fov += 5;
			projMatrix = perspective(deg2rad(fov), aspect, 0.1f, 100.0f);
			//cout << fov << endl;
		}
		
	}
}
void myMouseMoving(int x, int y)
{

	xoffset = x - lastX;
	yoffset = lastY - y; // reversed since y-coordinates go from bottom to top
	lastX = x;
	lastY = y;

	float sensitivity = 0.5f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	//cout << lastX << "   " << lastY << endl;

}
void menuEvents(int option) {

}
void ActionMenuEvents(int option) {
	switch (option) {
	case 0:
		action = IDLE;
		break;
	case 1:
		action = WALK;
		cout << "WALK" << endl;
		break;
	case 2:
		action = JUMPINGINGJACK;
		cout << "JUMPINGINGJACK" << endl;
		break;
	case 3:
		action = SQUAT;
		cout << "SQUAT" << endl;
		break;
	case 4:
		action = MOONWALK;
		cout << "moonWalk" << endl;
		break;
	case 5:
		action = SITUPS;
		cout << "sitUps" << endl;
		break;
	case 6:
		action = PUSHUPS;
		cout << "pushUps" << endl;
		break;
	case 7:
		action = DANCE;
		cout << "dance" << endl;
		break;
	case 8:
		action = DANCE_2;
		cout << "dance_2" << endl;
		break;
	case 10:
		
		system("pause");
		break;
	}
}
void ModeMenuEvents(int option)
{
	switch (option)
	{
	case 0:
		
		drawingmode= GL_LINES;
		break; 
	case 1:
		
		drawingmode = GL_TRIANGLES;
		break;
	case 2:

		drawingmode = GL_POINTS;
		break;
	case 3:

		roundMode = true;
		break;
	case 4:

		roundMode = false;
		break;
	}
}
void skyboxMenuEvents(int option)
{
	switch (option)
	{
	case 0:

		displaySkyBox = true;
		break;
	case 1:

		displaySkyBox = false;
		break;
	case 2:

		BK = 0;
		break;
	case 3:

		BK = 1;
		break;

	}
}
void My_Timer(int val)
{
	//std::cout << val << std::endl;
	switch (action)
	{
	case 0:
		InitialModuleAngle();
		break;
	case 1:
		walk1();
		break;
	case 2:
		jumpingJack2();
		break;
	case 3:
		squat3();
		break;
	case 4:
		moonWalk4();
		break;
	case 5:
		SitUps5();
		break;
	case 6:
		pushUp6();
		break;
	case 7:
		dance7();
		break;
	case 8:
		dance8();
		break;

	default:
		break;
	}
	glutPostRedisplay(); // 使程式於下次迴圈執行時更新畫面
	glutTimerFunc(1, My_Timer, val);


}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(800, 300);
	glutInitWindowSize(width, height);
	glutCreateWindow("Loadobj test"); // You cannot use OpenGL functions before this line; The OpenGL context must be created first by glutCreateWindow()!
	//Call custom initialize function
	myInit();
	InitSkyBox();
	//Register GLUT callback functions
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	glutKeyboardFunc(keyin);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMouseMoving);
	int ActionMenu, ModeMenu, skyboxMenu;
	ActionMenu = glutCreateMenu(ActionMenuEvents);//建立右鍵菜單
	//加入右鍵物件
	glutAddMenuEntry("idle", 0);
	glutAddMenuEntry("walk", 1);
	glutAddMenuEntry("jumpingjack", 2);
	glutAddMenuEntry("squat", 3);
	glutAddMenuEntry("moonwalk", 4);
	glutAddMenuEntry("situps", 5);
	glutAddMenuEntry("pushups", 6);
	glutAddMenuEntry("dance", 7);
	glutAddMenuEntry("dance_2", 8);
	glutAddMenuEntry("stop", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯
	ModeMenu = glutCreateMenu(ModeMenuEvents);//建立右鍵菜單
	glutAddMenuEntry("Line", 0);
	glutAddMenuEntry("Fill", 1);
	glutAddMenuEntry("Point", 2);
	glutAddMenuEntry("roundMode", 3);
	glutAddMenuEntry("stop roundMode", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯

	skyboxMenu = glutCreateMenu(skyboxMenuEvents);//建立右鍵菜單
	glutAddMenuEntry("enable", 0);
	glutAddMenuEntry("disable", 1);
	glutAddMenuEntry("black", 2);
	glutAddMenuEntry("white", 3);
	glutCreateMenu(menuEvents);//建立右鍵菜單
	//加入右鍵物件
	glutAddSubMenu("action", ActionMenu);
	glutAddSubMenu("mode", ModeMenu);
	glutAddSubMenu("background", skyboxMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);	//與右鍵關聯
	glutTimerFunc(1, My_Timer, 0);
	// Enter main event loop.
	glutMainLoop();
	

	return 0;
}
