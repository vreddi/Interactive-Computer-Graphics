#include "Vector3.h"

#define PI  3.141592654
#define TWOPI 6.28318531

boolean rotation_mode = true;
boolean axis = true;
boolean texture_mode = true;
int choice = 0;
boolean light = true;
boolean loadNoTextureModel = false;

//Application Window Details
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const char* WINDOW_TITLE = "Would you like some tea sir?";


//This class contains 3 numbers.
//Each number relates to a vertex and 3 numbers(vertices)
//would help us create a triangle polygon
class triangle{
public:
	int a;
	int b;
	int c;

	triangle(){

	}
};


//Struct to represent an OBJECT
class object{

public:
	//Object name, max size allowed is 30 characters.
	char name[30];

	//For storing the total number of vertices and faces in the OBJ file.
	int tot_Vertices;
	int tot_Faces;

	Vector3* vertex;

	triangle* face;

	Vector3* normalPerFace;
	Vector3* normalPerVertex;

	object(){

	}

};

