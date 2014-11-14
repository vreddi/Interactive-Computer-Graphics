//------------------------------------------------------------------------------------------------------//
/**																										//
*	MP-3 (Teapot Contest)																				//
*	Title: Would you like some tea sir?																        				//
*																									    //
*	Course: CS 418																						//
*	Author: Vishrut Reddi																				//
*	Net ID: vreddi2																						//
*	Created: November 2014																			    //
*/																							     		//
//------------------------------------------------------------------------------------------------------//

#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <conio.h>
#include <GL/glew.h>
#include <math.h>
#include <glut.h>
#include "mp3utility.h"
#include "camera.h"
#include "imageloader.h"


using namespace std;

//Variable that holds the model loaded from an .OBJ file
object model;

//For viewing control
Camera cam;

//Texture ID
GLuint textureID;
GLuint textureID2;


//Rotation angle for the teapot
int angle = 0;

/**
* Name: perVertexNormal()
* Description:
* Parameters: -none-
*/
//FACT: A normal is a vector that defines how a surface responds to lighting.
void calcNormalPerFace(){


	//2 vectors that store 2 co-planar vectors from a triangle face
	Vector3 vector1;
	Vector3 vector2;

	//Three points/Vertices forming a triangle face
	Vector3 v1, v2, v3;

	//Traversing through each face
	for (int i = 0; i < model.tot_Faces; i++){

		//Confusing notation? (Read Further)
		//We need a vertex number(getting from triangle array) adn then accessing its x, y and z components to form a Point3

		//First Vertex/Point in the Face
		v1.x = model.vertex[model.face[i].a - 1].x;
		v1.y = model.vertex[model.face[i].a - 1].y;
		v1.z = model.vertex[model.face[i].a - 1].z;

		//Second Vertex/Point in the Face
		v2.x = model.vertex[model.face[i].b - 1].x;
		v2.y = model.vertex[model.face[i].b - 1].y;
		v2.z = model.vertex[model.face[i].b - 1].z;
		
		//Third Vertex/Point in the Face
		v3.x = model.vertex[model.face[i].c - 1].x;
		v3.y = model.vertex[model.face[i].c - 1].y;
		v3.z = model.vertex[model.face[i].c - 1].z;


		vector1.x = v2.x - v1.x;
		vector1.y = v2.y - v1.y;
		vector1.z = v2.z - v1.z;

		vector2.x = v3.x - v1.x;
		vector2.y = v3.y - v1.y;
		vector2.z = v3.z - v1.z;

		//Normaling the faceNormal vector to obtain proper lighting
		model.normalPerFace[i].x = vector1.vector3Cross(vector2).vector3Normalize().x;
		model.normalPerFace[i].y = vector1.vector3Cross(vector2).vector3Normalize().y;
		model.normalPerFace[i].z = vector1.vector3Cross(vector2).vector3Normalize().z;	
	}

}


void calcNormalPerVertex(){
	//Now calculating normal per Vertex

	//Getting cleared values
	for (int i = 0; i < model.tot_Vertices; i++){
	model.normalPerVertex[i].x = 0;
	model.normalPerVertex[i].y = 0;
	model.normalPerVertex[i].z = 0;
	}
	
	//Another possible way of doing things
	/*
	int i, j;
	Vector3 temp;
	int numOfFaces = 0;

	//Traversing through each Face
	for (i = 0; i < model.tot_Vertices; i++){
		for (j = 0; j < model.tot_Faces; j++){
		
			if ((model.face[i].a - 1) == j || (model.face[i].a - 1) == j || (model.face[i].a - 1) == j){
				temp.x += model.normalPerFace[j].x;
				temp.y += model.normalPerFace[j].y;
				temp.z += model.normalPerFace[j].z;
				numOfFaces++;
			}
				
		}

		model.normalPerVertex[i].x = (temp.x)/numOfFaces;
		model.normalPerVertex[i].y = (temp.y) / numOfFaces;
		model.normalPerVertex[i].z = (temp.z) / numOfFaces;

		//RESET
		numOfFaces = 0;
		temp.x = 0;
		temp.y = 0;
		temp.z = 0;
	}
	*/

	
	for (int i = 0; i < model.tot_Faces; i++){

	model.normalPerVertex[model.face[i].a - 1].x += (model.normalPerFace[i]).x;
	model.normalPerVertex[model.face[i].a - 1].y += (model.normalPerFace[i]).y;
	model.normalPerVertex[model.face[i].a - 1].z += (model.normalPerFace[i]).z;


	model.normalPerVertex[model.face[i].b - 1].x += (model.normalPerFace[i]).x;
	model.normalPerVertex[model.face[i].b - 1].y += (model.normalPerFace[i]).y;
	model.normalPerVertex[model.face[i].b - 1].z += (model.normalPerFace[i]).z;


	model.normalPerVertex[model.face[i].c - 1].x += (model.normalPerFace[i]).x;
	model.normalPerVertex[model.face[i].c - 1].y += (model.normalPerFace[i]).y;
	model.normalPerVertex[model.face[i].c - 1].z += (model.normalPerFace[i]).z;
	}

	//Normalizing Time
	for (int i = 0; i < model.tot_Vertices; i++){
	model.normalPerVertex[i].x = model.normalPerVertex[i].vector3Normalize().x;
	model.normalPerVertex[i].y = model.normalPerVertex[i].vector3Normalize().y;
	model.normalPerVertex[i].z = model.normalPerVertex[i].vector3Normalize().z;
	}
	
	
}

void load_Obj(char* filename){

	ifstream obj_file;
	
	obj_file.open(filename);


	//Unable to open the file
	if (!obj_file.is_open()){
		std :: cout << "failed!";
	}

	char word[50];

	//Stores total number of vertices in the .OBJ file
	int no_of_vertices = 0;

	//Stores total number of faces in the .OBJ file
	int no_of_faces = 0;

	//Calculating total vertics and faces in the .OBJ file
	while (obj_file.good()){

		obj_file >> word;

		if (word[0] == 'v'){
			no_of_vertices++;
		}

		else if (word[0] == 'f'){
			no_of_faces++;
		}
	}

	//Re-open the file
	obj_file.close();
	obj_file.open(filename);

	//Unable to open the file
	if (!obj_file.is_open()){
		std::cout << "failed!";
	}

	model.normalPerFace = new Vector3[no_of_faces];	
	model.normalPerVertex = new Vector3[no_of_vertices];
	model.vertex = new Vector3[no_of_vertices];
	model.face = new triangle[no_of_faces];
	model.tot_Vertices = no_of_vertices;
	model.tot_Faces = no_of_faces;

	//traversal variable of the vertex array
	int i = 0;

	//traversal variable of the face array
	int j = 0;

	//Loop through words
	while (obj_file.good()){

		if (word[0] == 'v'){
			
			//Storing the individual components of the vertex
			//see category -> move to the next word and store in x value and simultaneously for others
			//stof() convert string to float value
			obj_file >> word;
			model.vertex[i].x = stod(word);

			obj_file >> word;
			model.vertex[i].y = stod(word);

			obj_file >> word;
			model.vertex[i].z = stod(word);			

			i++;
		}

		

		else if (word[0] == 'f'){
			
			//Storing the individual components of the face
			//see category -> move to the next word and store in 'a' value and simultaneously for others
			// stof() convert string to float value
			obj_file >> word;
			model.face[j].a = stof(word);

			obj_file >> word;
			model.face[j].b = stof(word);

			obj_file >> word;
			model.face[j].c = stof(word);
		
			j++;
		}
		else{
			obj_file >> word;
		}

	}
	std  :: cout << no_of_vertices << " " << no_of_faces;
}


void drawModel()
{
	glewInit();

	if (light){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}

	if (rotation_mode)
	{
		angle = angle + 1;

		if (angle > 360)
			angle -= 360;
		else if (angle < 0)
			angle += 360;
	}
	//Clear the Color Buffer, Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glLineWidth(2.0);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Set Material Properties
	GLfloat black[] = { 0.2, 0.2, 0.2, 5.0 };
	GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);


	//Textures
	glEnable(GL_TEXTURE_2D);
	if (choice == 2){
		
		loadNoTextureModel = false;

		glBindTexture(GL_TEXTURE_2D, textureID2);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	else if (choice == 1 || choice == 3){

		loadNoTextureModel = false;
		
		glBindTexture(GL_TEXTURE_2D, textureID);

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);

		//Blocky texture mapping
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Blurry texture mapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		

	}

	else if (choice == 0){
		loadNoTextureModel = true;

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}

	//Switch to drawing perspective
	glMatrixMode(GL_MODELVIEW);
	//Reset the Drawing Perspective/ Clear the Stack
	glLoadIdentity();
	
	//cam.moveForward(-0.01);
	cam.setView();

	
	glPushMatrix();

	if (axis)
		glRotatef(angle, 0, 1, 0);

	else
		glRotatef(angle, 1, 0.5, 0);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glShadeModel(GL_SMOOTH);

	if (loadNoTextureModel){
		glBegin(GL_TRIANGLES);

		glColor3f(0.5, 0.5, 0.5);
		for (int i = 0; i < model.tot_Faces; i++){

			glColor3f(0.5, 0.5, 0.5);
		//	theta = atan2(model.vertex[model.face[i].a - 1].z, model.vertex[model.face[i].a - 1].x);
			glNormal3f(model.normalPerVertex[model.face[i].a - 1].x, model.normalPerVertex[model.face[i].a - 1].y, model.normalPerVertex[model.face[i].a - 1].z);
		//	glTexCoord2f((theta + PI) / (TWOPI), (model.vertex[model.face[i].a - 1].y / 2.0));
			glVertex3f(model.vertex[model.face[i].a - 1].x, model.vertex[model.face[i].a - 1].y, model.vertex[model.face[i].a - 1].z);

			glColor3f(0.5, 0.5, 0.5);
		//	theta = atan2(model.vertex[model.face[i].b - 1].z, model.vertex[model.face[i].b - 1].x);
			glNormal3f(model.normalPerVertex[model.face[i].b - 1].x, model.normalPerVertex[model.face[i].b - 1].y, model.normalPerVertex[model.face[i].b - 1].z);
		//	glTexCoord2f((theta + PI) / (TWOPI), (model.vertex[model.face[i].b - 1].y / 2.0));
			glVertex3f(model.vertex[model.face[i].b - 1].x, model.vertex[model.face[i].b - 1].y, model.vertex[model.face[i].b - 1].z);


			glColor3f(0.5, 0.5, 0.5);
		//	theta = atan2(model.vertex[model.face[i].c - 1].z, model.vertex[model.face[i].c - 1].x);
			glNormal3f(model.normalPerVertex[model.face[i].c - 1].x, model.normalPerVertex[model.face[i].c - 1].y, model.normalPerVertex[model.face[i].c - 1].z);
		//	glTexCoord2f((theta + PI) / (TWOPI), (model.vertex[model.face[i].c - 1].y / 2.0));
			glVertex3f(model.vertex[model.face[i].c - 1].x, model.vertex[model.face[i].c - 1].y, model.vertex[model.face[i].c - 1].z);

		}
		glEnd();
	}
	else{
		glBegin(GL_TRIANGLES);

		float theta;
		glColor3f(0.5, 0.5, 0.5);
		for (int i = 0; i < model.tot_Faces; i++){

			theta = atan2(model.vertex[model.face[i].a - 1].z, model.vertex[model.face[i].a - 1].x);
			glNormal3f(model.normalPerVertex[model.face[i].a - 1].x, model.normalPerVertex[model.face[i].a - 1].y, model.normalPerVertex[model.face[i].a - 1].z);
			glTexCoord2f((theta + PI) / (TWOPI), (model.vertex[model.face[i].a - 1].y / 2.0));
			glVertex3f(model.vertex[model.face[i].a - 1].x, model.vertex[model.face[i].a - 1].y, model.vertex[model.face[i].a - 1].z);


			theta = atan2(model.vertex[model.face[i].b - 1].z, model.vertex[model.face[i].b - 1].x);
			glNormal3f(model.normalPerVertex[model.face[i].b - 1].x, model.normalPerVertex[model.face[i].b - 1].y, model.normalPerVertex[model.face[i].b - 1].z);
			glTexCoord2f((theta + PI) / (TWOPI), (model.vertex[model.face[i].b - 1].y / 2.0));
			glVertex3f(model.vertex[model.face[i].b - 1].x, model.vertex[model.face[i].b - 1].y, model.vertex[model.face[i].b - 1].z);



			theta = atan2(model.vertex[model.face[i].c - 1].z, model.vertex[model.face[i].c - 1].x);
			glNormal3f(model.normalPerVertex[model.face[i].c - 1].x, model.normalPerVertex[model.face[i].c - 1].y, model.normalPerVertex[model.face[i].c - 1].z);
			glTexCoord2f((theta + PI) / (TWOPI), (model.vertex[model.face[i].c - 1].y / 2.0));
			glVertex3f(model.vertex[model.face[i].c - 1].x, model.vertex[model.face[i].c - 1].y, model.vertex[model.face[i].c - 1].z);

		}
		glEnd();
	}


	glPopMatrix();

	//Swaps the buffers of the current window if double buffered.
	glutSwapBuffers();
	glFlush();

	glutPostRedisplay();

}

/**
* Function: drawModel()
* Description: This function is called when the Window is resized.
*
* Parameters: int width :: current width of the window
*			  int height :: current height of the window
*/
void resize(int width, int height)
{
	//Handing error case of dividing by zero (i.e aspect_ratio = width/height) 
	if (height == 0)
		height = 1;

	float aspect_ratio = (float)width / height;
	


	//for scalaing
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, width, height);

	gluPerspective(45, aspect_ratio, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
}

//Function used to control the aircraft
void controls(int key, int x, int y){

	if (key == GLUT_KEY_UP + GLUT_KEY_LEFT){
		cam.pitch(2);
		cam.roll(2);
	}

	if (key == GLUT_KEY_UP + GLUT_KEY_RIGHT)
	{
		cam.pitch(2);
		cam.roll(-2);
	}

	if (key == GLUT_KEY_DOWN + GLUT_KEY_LEFT){
		cam.pitch(-2);
		cam.roll(2);
	}

	if (key == GLUT_KEY_DOWN + GLUT_KEY_RIGHT)
	{
		cam.pitch(-2);
		cam.roll(-2);
	}

	if (key == GLUT_KEY_UP)
		cam.pitch(2);


	if (key == GLUT_KEY_DOWN)
		cam.pitch(-2);

	if (key == GLUT_KEY_LEFT)
		cam.roll(2);

	if (key == GLUT_KEY_RIGHT)
		cam.roll(-2);

	glutPostRedisplay();
}

//Some basic map manipulation controls and yaw controls
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		//Key-Q to yaw to the left
	case 'q':
		cam.yaw(-2);
		break;

		//Key-W to yaw to the right
	case 'w':
		cam.yaw(2);
		break;

		//Teapot Rotation Mode
	case 'r':
		rotation_mode = !rotation_mode;
		break;

		//Change Axis of Rotation
	case 'a':
		axis = !axis;
		break;

	case 't':
		choice = (choice + 1)%4;
		break;

	case'l':
		light = !light;
		break;

	case 27:
		exit(0);
		break;
	}

	glutPostRedisplay();
}

/**
* Name: loadTexture(Image*)
* Description: Converts the input Image to a texture and returns the  Texture ID
* Parameters: Image :: *image
*/
GLuint loadTexture(Image* image){
	GLuint texID;
	
	//New texture create
	glGenTextures(1, &texID);

	//Grab hold of the Texture to use
	glBindTexture(GL_TEXTURE_2D, texID);

	//mapping hte image to the texture
	//Last parameter is the actual pixel data array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

	return texID;
}

GLuint loadEnvironmentTexture(Image* image){
	GLuint texID;
	
	//New texture create
	glGenTextures(1, &texID);

	//Grab hold of the Texture to use
	glBindTexture(GL_TEXTURE_2D, texID);

	//mapping hte image to the texture
	//Last parameter is the actual pixel data array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

	return texID;
}


void init(void){

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -3.0, 3.0);

	//Now Setting up Lighting
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	//Setting light insensity and color
	GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	//Setting the position of the Light
	//{ x, y , z , 1}
	GLfloat lightPos[] = { 0.0, 1.0, -0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	Image* image = loadBMP("texture_tiles.bmp");
	textureID = loadTexture(image);
	Image* image2 = loadBMP("environment.bmp");
	textureID2 = loadEnvironmentTexture(image2);
	//Free memory
	delete image;
	delete image2;
	
}

int main(int argc, char** argv){
	//Initialize GLUT and OpenGL
	glutInit(&argc, argv);

	//Initializing Window Position on the screen
	glutInitWindowPosition(0, 0);

	//Initializing Window Size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//Initializing the Initial Display Mode :: RGBA, Double Buffered, Depth (for 3D)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//Setting Up Window Title
	glutCreateWindow(WINDOW_TITLE);

	//Clearing the color Buffer to set the background color in the GLUT Window
	glClearColor(1, 1, 1, 1);

	model.tot_Faces = 0;
	model.tot_Vertices = 0;
	model.face = NULL;
	model.vertex = NULL;
	model.normalPerVertex = NULL;
	model.normalPerFace = NULL;

	//Loading up the .OBJ file and storing the file details in objext_st struct
	load_Obj("teapot_0.obj");

	//Now time to calulate that per Face Normals
	calcNormalPerFace();

	//Now time to calulate that per Vertex Normals
	calcNormalPerVertex();

	init();
	//Setup GLUT Callback Functions
	glutDisplayFunc(drawModel);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(controls);


	//Initialize GLEW
	GLenum e = glewInit();
	if (e != GLEW_OK)
	{
		cout << endl;
		cout << "GLEW unable to Initialize " << endl;
		system("pause");
		exit(1);
	}
	else if(e == GLEW_OK){
		cout << endl; 
		cout << "GLEW Initialized " << endl;
	}
	else{
		cout << endl;
		cout << "GLEW unable to Initialize " << endl;
		system("pause");
		exit(1);
	}
	
	//Enter Main Loop
	glutMainLoop();

	//free the memory
	delete[] model.vertex;
	delete[] model.face;
	delete[] model.normalPerFace;
	delete[] model.normalPerVertex;
	model.vertex = NULL;
	model.face = NULL;
	model.normalPerVertex = NULL;
	model.normalPerFace = NULL;

	system("pause");
	return 0;
}

