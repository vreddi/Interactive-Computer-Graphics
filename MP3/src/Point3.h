#include <math.h>
#include <iostream>

//This class represents a 3-coordinate system Point
class Point3{

public:
	double x;
	double y;
	double z;

	//Origin by Default
	Point3(){
		x = y = z = 0;
	}

	//Parametrized constructor
	Point3(double a, double b, double c){

		x = a;
		y = b;
		z = c;
	}

};