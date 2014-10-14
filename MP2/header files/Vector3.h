#include <iostream>
#include <math.h>
#include "Point3.h"

//This class represents a 3-coordinate system Vector
//with all the functionalities of a 3D vector
class Vector3{

public:
	double x;
	double y;
	double z;

	//Default Constructor
	Vector3(){
		x = y = z = 0;
	}

	//Parameterized Constructor
	Vector3(double a, double b, double c){

		x = a;
		y = b;
		z = c;
	}


	/*
	Name: vector3Set(double, double, double)
	Description: This functon can be used to change the x,y and z values of a vector.
	Parameters: (double, double, double)
	Return Type: void
	*/
	void vector3Set(double a, double b, double c){

		x = a;
		y = b;
		z = c;
	}


	/*
	Name: vector3Addition(Vector3)
	Description: This is function exists to emulate the 3D coordinate system
	vector addition.
	Parameters: Vector3
	Return Type: Vector3
	*/
	Vector3 vector3Addition(Vector3 b){
		Vector3 a;
		a.x = x + b.x;
		a.y = y + b.y;
		a.z = z + b.z;

		return a;
	}


	/*
	Name: vector3Subtraction(Vector3)
	Description: This is function exists to emulate the 3D coordinate system
	vector subtraction.
	Parameters: Vector3
	Return Type: Vector3
	*/
	Vector3 vector3Subtraction(Vector3 b){
		Vector3 a;
		a.x = x - b.x;
		a.y = y - b.y;
		a.z = z - b.z;

		return a;
	}


	/*
	Name: vector3Dot(Point3)
	Description: This functon is used to emulate the Vector Dot Product.
	Parameters: Vector3
	Return Type: double (Dot Product)
	*/
	Vector3 vector3Cross(Vector3 b){
		Vector3 a;

		a.x = (y * b.z) - (z * b.y);
		a.y = (z * b.x) - (x * b.z);
		a.z = (x * b.y) - (y * b.x);

		return a;
	}


	/*
	Name: vector3Dot(Vector3)
	Description: This functon is used to emulate the Vector Dot Product.
	Parameters: Vector3
	Return Type: double (Dot Product)
	*/
	double vector3Dot(Vector3 b){

		return ((x * b.x) + (y * b.y) + (z * b.z));

	}


	/*
	Name: vector3Reverse()
	Description: Takes a Vector and procudes a vector which is the reverse of the given vector.
	Essentially a mirror back image of the vector.
	Note: Its present because I got carried away with the Vector3 class and I
	wanted to create as many functions for Vectors as possible to complete a proper
	class. This function is however never used in this program, but it could be for some other
	flying tricks.
	Parameters: -none-
	Return Type: Vector3
	*/
	Vector3 vector3Reverse(){

		Vector3 a;

		a.x = -x;
		a.y = -y;
		a.z = -z;

		return a;
	}


	/*
	Name: vector3Magnitude()
	Description: Takes in a Vector3 and returns th emagnitude of that vector
	Parameters: -none-
	Return Type: double (magnitude)
	*/
	double vector3Magnitude(){

		//Calculation for the magnitude of the vector
		double magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

		return magnitude;
	}


	/*
	Name: vector3Normalize()
	Description: For any vector used for this function, this function creates a unit
	vector (Magnitude 1) along the direction of the orignal vector.
	Essentially Normailizing the vector
	Parameters: -none-
	Return Type: Vector3
	*/
	Vector3 vector3Normalize(){

		Vector3 a;
		double magnitude = vector3Magnitude();

		a.x = (double)x / magnitude;
		a.y = (double)y / magnitude;
		a.z = (double)z / magnitude;

		return a;
	}


	/*
	Name: vector3GetPositionVectorOfAPoint(Point3)
	Description: Input is a 3-Coordinate Point (Point3) and the function
	creates a position vector for that point and returns the Vector.
	Parameters: (Point3)
	Return Type: Vector3
	*/
	static Vector3 vector3GetPositionVec(Point3 p){

		Vector3 ans(p.x, p.y, p.z);
		return ans;
	}

};