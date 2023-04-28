#include "main.h"
#include"Module.hpp"
const float cube[]{
	//
	-0.25f,  0.25f, -0.25f,
   -0.25f, -0.25f, -0.25f,
   0.25f, -0.25f, -0.25f,

   0.25f, -0.25f, -0.25f,
   0.25f,  0.25f, -0.25f,
   -0.25f,  0.25f, -0.25f,
   //
   0.25f, -0.25f, -0.25f,
   0.25f, -0.25f,  0.25f,
   0.25f,  0.25f, -0.25f, 

   0.25f, -0.25f,  0.25f, 
   0.25f,  0.25f,  0.25f, 
   0.25f,  0.25f, -0.25f,
   //
   0.25f, -0.25f,  0.25f, 
   -0.25f, -0.25f,  0.25f, 
   0.25f,  0.25f,  0.25f,

   -0.25f, -0.25f,  0.25f, 
   -0.25f,  0.25f,  0.25f, 
   0.25f,  0.25f,  0.25f, 
   //
   -0.25f, -0.25f,  0.25f,
   -0.25f, -0.25f, -0.25f, 
   -0.25f,  0.25f,  0.25f, 

   -0.25f, -0.25f, -0.25f,
   -0.25f,  0.25f, -0.25f, 
   -0.25f,  0.25f,  0.25f, 
   //
   -0.25f, -0.25f,  0.25f, 
   0.25f, -0.25f,  0.25f,
   0.25f, -0.25f, -0.25f, 

   0.25f, -0.25f, -0.25f,
   -0.25f, -0.25f, -0.25f, 
   -0.25f, -0.25f,  0.25f, 
   //
   -0.25f,  0.25f, -0.25f, 
   0.25f,  0.25f, -0.25f, 
   0.25f,  0.25f,  0.25f, 

   0.25f,  0.25f,  0.25f, 
   -0.25f,  0.25f,  0.25f, 
   -0.25f,  0.25f, -0.25f, 

};
unsigned int testIndex[]{
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
};
unsigned int test[] = { 0,1,3,2 };
const char* vsSource = R"glsl(
	#version 400
	uniform mat4 projMatrix;
	uniform mat4 view;
	uniform mat4 scaleMatrix;
	uniform mat4 mvMatrix;
	layout (location = 0) in vec3 position;
	out vec4 mycolor;
	void main()
	{
		gl_Position =  projMatrix*view*mvMatrix*scaleMatrix * vec4(position,1.0)*vec4(0.2,0.2,0.2,1);
		mycolor=vec4(position,1.0);
	}
)glsl";
const char* fsSource = R"glsl(
	#version 400

	out vec4  color;
	in vec4 mycolor;
	void main()
	{
		color = mycolor;
	}
)glsl";
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
	glGetShaderInfoLog(vs, 512, NULL, info);
	printf("%s", info);
	glGetShaderInfoLog(fs, 512, NULL, info);
	printf("%s", info);
	//Attach Shader to program
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glUseProgram(program);
	////
	
	cout << "元件總數 " << PARTNUM << endl << endl;
		
		
	Module test("armtop.obj", 0);
	
		
	//0 for VBO //1 for EBO 
	for (int i = 0; i < PARTNUM; i++) 
	{
		totalSize[0] += VBOsSIZE[i];
		totalSize[1] += EBOsSIZE[i];
	}
	cout <<"總面數 " << totalSize[1] / sizeof(Face) << endl;

		
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mvLocation = glGetUniformLocation(program, "mvMatrix");
	projLocation = glGetUniformLocation(program, "projMatrix");
	scaleLocation = glGetUniformLocation(program, "scaleMatrix");
	viewLocation = glGetUniformLocation(program, "view");
	
}
void My_Display()
{
	
	glutPostRedisplay();
	view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	scaleMatrix = scale(scaleMatrix, vec3(1, 1, 1));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float currentTime = glutGet(GLUT_ELAPSED_TIME) * 0.01f;
	mat4 mv_matrix(1.0);
	mv_matrix = rotate(mv_matrix, deg2rad(currentTime * 45.0f), vec3(0.0f, 0.0f, 1.0f));
	//mv_matrix = translate(mv_matrix, vec3(1.0, 0.0, 0.0));
	
	
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projMatrix[0][0]);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(scaleLocation, 1, GL_FALSE, &scaleMatrix[0][0]);
	glUniformMatrix4fv(mvLocation, 1, GL_FALSE, &mv_matrix[0][0]);
	for (int i = 0; i < PARTNUM; i++) 
	{
		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
		glUseProgram(program);
		int face = EBOsSIZE[i] / sizeof(Face);
		for (int j = 0; j < face; j++)
		{
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(j * 3 * sizeof(unsigned int)));
		}
	}
	
	
	///////////////////////////	
	glutSwapBuffers();

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
	switch (key)
	{
	
	case 'w':
		cameraPos += cameraSpeed * cameraFront;;
		cout << "press" << endl;
		break;
	case 'a':
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		cout << "press" << endl;
		break;
	case 's':
		cameraPos -= cameraSpeed * cameraFront;
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
			cout << fov << endl;
		}
			
		
	}
	else if (button == 4)
	{
		if (fov < 95) {
			fov += 5;
			projMatrix = perspective(deg2rad(fov), aspect, 0.1f, 100.0f);
			cout << fov << endl;
		}
		
	}
}
void myMouseMoving(int x, int y)
{

	xoffset = x - lastX;
	yoffset = lastY - y; // reversed since y-coordinates go from bottom to top
	lastX = x;
	lastY = y;

	float sensitivity = 1.0f; // change this value to your liking
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
	cout << lastX << "   " << lastY << endl;

}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(800, 300);
	glutInitWindowSize(width, height);
	glutCreateWindow("Loadobj test"); // You cannot use OpenGL functions before this line; The OpenGL context must be created first by glutCreateWindow()!
	//Call custom initialize function
	myInit();
	
	//Register GLUT callback functions
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	glutKeyboardFunc(keyin);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMouseMoving);
	// Enter main event loop.
	glutMainLoop();
	

	return 0;
}