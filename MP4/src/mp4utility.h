#include <vector>
#include "Vector3.h"

#define PI  3.141592654
#define TWOPI 6.28318531

const int WINDOW_WIDTH = 500;		//Window Default Width
const int WINDOW_HEIGHT = 500;		//Wondow Default Height
const char* WINDOW_TITLE = "Subdivision Surfaces";		//Window Title
int asp_rat;					//Variable used to store the aspect ratio of the window
bool meshview = true;			//Mesh view ON/OFF toggle
bool direction = true;			//Bezire curve direction to keep t in between [0,1]
bool light = true;				//Variable used a lighting toggle
bool texture_mode = false;			//Variable for texture mode ON/OFF
float angle = 0;
int color = 0;		//TO change color

//DS PRROTOCOLS
class HE_edge;
class HE_vert;
class HE_face;

//Bezier Curve flow controller
double t = 0.001;
double speed = 0;

//Global Vectors to store the values related to the mesh
//List of vertices
std::vector<HE_vert*> vertexVector;

//List of faces
std::vector<HE_face*> faceVector;

//List of half edges
std::vector<HE_edge*> edgeVector;


class HE_vert{
public:

	//Point/Vertex coordinates
	double x;
	double y;
	double z;

	//Edge emanating out of the vertex
	HE_edge* vertEdge;

	Vector3 normal;

	HE_vert(){

		x = y = z = 0;
	}

};

class HE_face{
public:
	//4 points/vertices forming a QUAD face
	HE_vert* v1;
	HE_vert* v2;
	HE_vert* v3;
	HE_vert* v4;

	//Face-Point associated with the face
	HE_vert* facePt;

	//One HE associated with each face
	HE_edge* faceEdge;

	HE_face(){

		v1 = v2 = v3 = v4 = facePt = nullptr;
		
	}
};

class HE_edge{
public:

	//start and end point
	HE_vert* start;
	HE_vert* end;

	//The opposite HE forming a pair
	HE_edge* pair;

	//Edge Point associated with the half edge
	HE_vert* edgePt;

	//The face the half edge is inside
	HE_face* face;

	//Next edge in the face
	HE_edge* next;

	HE_edge(){

		start = nullptr;
		end = nullptr;

		pair = nullptr;

		edgePt = nullptr;

		face = nullptr;

		next = nullptr;
	}
};


//BEZIER CURVE KEY POINTS
HE_vert p0;
HE_vert p1;
HE_vert p2;
HE_vert p3;