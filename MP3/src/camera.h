#include <iostream>
#include <conio.h>
#include <math.h>
#include <glut.h>

#ifndef POINT3_H
#define POINT3_H

#ifndef VECTOR3_H
#define VECTOR3_H

using namespace std;


//This class represents the Camera or the cockpit view of the aircraft.
class Camera{

public:

	Point3 position;
	Vector3 i;				//RIGHT vector
	Vector3 j;				//UP vector
	Vector3 k;				//FORWARD vector

	//Initial Camera Position and settings
	Camera(){
		position.x = -2.42005;
		position.y = 2.02841;
		position.z = 8.85226;

		i.x = 0.962961;
		i.y = 0.0173788;
		i.z = 0.269078;

		j.x = -0.00775981;
		j.y = 0.999294;
		j.z = -0.0367706;

		k.x = -0.26952;
		k.y = 0.0333207;
		k.z = 0.962417;
	}

	/*
	Name: setView()
	Description: Changes the model View matrix to reflect a new Camera View
	Parameters: -none-
	return: void
	*/
	void setView(void){
		// 4x4 Matrix for final view load
		double mat4[16];

		//Position Vector for the position of the Camera
		Vector3 camPosition(position.x, position.y, position.z);

		//OpenGL uses coloumn matrix

		/*
		|  i.x   i.y   i.z   -camPosition.i	   |
		|						 			   |
		|  j.x   j.y   j.z   -camPosition.j    |
		|	 								   |
		|  k.x   k.y   k.z   -camPosition.k    |
		|					                   |
		|   0     0     0          1           |


		(note) . -> DOT PRODUCT
		*/

		mat4[0] = i.x;
		mat4[1] = j.x;
		mat4[2] = k.x;
		mat4[3] = 0;
		mat4[4] = i.y;
		mat4[5] = j.y;
		mat4[6] = k.y;
		mat4[7] = 0;
		mat4[8] = i.z;
		mat4[9] = j.z;
		mat4[10] = k.z;
		mat4[11] = 0;
		mat4[12] = -camPosition.vector3Dot(i);
		mat4[13] = -camPosition.vector3Dot(j);
		mat4[14] = -camPosition.vector3Dot(k);
		mat4[15] = 1;

		//Values are loaded in the matrix, Launch Time
		glMatrixMode(GL_MODELVIEW);

		//Loaded in the Coloumn Matrix
		glLoadMatrixd(mat4);
	}


	/*
	Name: roll(double)
	Description: Given an angle to roll by, this function helps the camera roll left or right
	depending on a positive or a negetive angle passed in the parameter. Here the Right vector
	is rotated and the Up Vector is rotated.
	Parameters: double (angle)
	Return Type: void
	*/
	void roll(double angle){

		double cosine = cos((angle / 180) * 3.1415926535);
		double sine = sin((angle / 180) * 3.1415926535);

		Vector3 temp = i;	//saving  vector

		//Changing Right Vector
		i.vector3Set((cosine * temp.x) - (sine * j.x), (cosine * temp.y) - (sine * j.y), (cosine * temp.z) - (sine * j.z));

		//Changing Up Vector
		j.vector3Set((sine * temp.x) + (cosine * j.x), (sine * temp.y) + (cosine * j.y), (sine * temp.z) + (cosine * j.z));

		//Setting the new view
		setView();

		//For Debugging
		cout << "Position x :" << position.x << "  " << "Right x :" << i.x << "  " << "Up x : " << j.x << "  " << "Forward x : " << k.x << endl;
		cout << "Position y :" << position.y << "  " << "Right y :" << i.y << "  " << "Up y : " << j.y << "  " << "Forward y : " << k.y << endl;
		cout << "Position z :" << position.z << "  " << "Right z :" << i.z << "  " << "Up z : " << j.z << "  " << "Forward z : " << k.z << endl << endl;
	}


	/*
	Name: yaw(double)
	Description: Given an angle to yaw by, this function helps the camera look left or right
	depending on a positive or a negetive angle passed in the parameter. Here the Right vector
	is rotated and the Forward Vector is rotated.
	Parameters: double (angle)
	Return Type: void
	*/
	void yaw(double angle){

		double cosine = cos((angle / 180) * 3.1415926535);
		double sine = sin((angle / 180) * 3.1415926535);

		Vector3 temp = i;	//saving  vector

		//Changing Right Vector
		i.vector3Set((cosine * temp.x) + (sine * k.x), (cosine * temp.y) + (sine * k.y), (cosine * temp.z) + (sine * k.z));

		//Changing Forward Vector
		k.vector3Set((-sine * temp.x) + (cosine * k.x), (-sine * temp.y) + (cosine * k.y), (-sine * temp.z) + (cosine * k.z));

		//Setting the new view
		setView();

		//For Debugging
		//To check the vector value sin the console
		cout << "Position x :" << position.x << "  " << "Right x :" << i.x << "  " << "Up x : " << j.x << "  " << "Forward x : " << k.x << endl;
		cout << "Position y :" << position.y << "  " << "Right y :" << i.y << "  " << "Up y : " << j.y << "  " << "Forward y : " << k.y << endl;
		cout << "Position z :" << position.z << "  " << "Right z :" << i.z << "  " << "Up z : " << j.z << "  " << "Forward z : " << k.z << endl << endl;

	}


	/*
	Name: pitch(double)
	Description: Given an angle to pitch by, this function helps the camera look up or down
	depending on a positive or a negetive angle passed in the parameter. Here the Forward vector
	is rotated and the Up Vector is rotated.
	Parameters: double (angle)
	Return Type: void
	*/
	void pitch(double angle){

		//Collecting cosine and sine values in radians
		double cosine = cos((angle / 180) * 3.1415926535);
		double sine = sin((angle / 180) * 3.1415926535);

		Vector3 temp = k;	//saving  vector

		//Changing Forward Vector
		k.vector3Set((cosine * temp.x) + (sine * j.x), (cosine * temp.y) + (sine * j.y), (cosine * temp.z) + (sine * j.z));

		//Changing Up Vector
		j.vector3Set((-sine * temp.x) + (cosine * j.x), (-sine * temp.y) + (cosine * j.y), (-sine * temp.z) + (cosine * j.z));

		//Setting the new view
		setView();

		//For Debugging
		//To check the vector value sin the console
		cout << "Position x :" << position.x << "  " << "Right x :" << i.x << "  " << "Up x : " << j.x << "  " << "Forward x : " << k.x << endl;
		cout << "Position y :" << position.y << "  " << "Right y :" << i.y << "  " << "Up y : " << j.y << "  " << "Forward y : " << k.y << endl;
		cout << "Position z :" << position.z << "  " << "Right z :" << i.z << "  " << "Up z : " << j.z << "  " << "Forward z : " << k.z << endl << endl;

	}


	/*
	Name: moveForward(double)
	Description: Given a constant distance to move, this function helps the camera
	move in the forward view direction with a specific distance amount(parameter).
	Parameters: double (moveDist)
	Return Type: void
	*/
	void moveForward(double moveDist){

		//Get unit direction vector
		Vector3 forwardDir = k.vector3Normalize();
		Vector3 positionVec = Vector3::vector3GetPositionVec(position);

		forwardDir.x = moveDist * forwardDir.x;
		forwardDir.y = moveDist * forwardDir.y;
		forwardDir.z = moveDist * forwardDir.z;

		//Creating new Position for the Camera by the vector Addition function
		position.x = positionVec.vector3Addition(forwardDir).x;
		position.y = positionVec.vector3Addition(forwardDir).y;
		position.z = positionVec.vector3Addition(forwardDir).z;

		//Updating View
		setView();

	}

};

#endif
#endif