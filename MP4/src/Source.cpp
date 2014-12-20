//------------------------------------------------------------------------------------------------------//
/*
*	MP-4 (Subdivison Surfaces)	
*	Title: Subdivision Surfaces	        
*	    
*	Course: CS 418	
*	Author: Vishrut Reddi	
*	Net ID: vreddi2	
*	Created: November 2014	    
*/
//------------------------------------------------------------------------------------------------------//


#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "mp4utility.h"
#include <GL\glew.h>
#include <glut.h>
#include "imageloader.h"

//Usabe in MSVS ONLY!
#pragma comment(lib, "glew32")


using namespace std;

//For texture ID
GLuint textureID;

/*
*	Name: printAllVertices(std::vector<HE_vert*>)
*	Description: Prints all the coordinate values of the vertices in the console
*				 (Used for verifying values and debugging)
*/
void printAllVertices(std::vector<HE_vert*> &vertexVector){

	std::vector<HE_vert*>::iterator i;

	for (i = vertexVector.begin(); i < vertexVector.end(); i++){
		cout << endl;
		cout << (*i)->x << " " << (*i)->y << " " << (*i)->z << endl;
	}

}
/**
*	Name: faceCreator(HE_vert*, HE_vert*, HE_vert*, HE_vert*, std::vector<HE_face*>, std::vector<HE_edge*>)
*	Description: This function is used to create a face. It inputs 4 vertices which
*				 in turn end up becoming the vertices of a QUAD face and then later 
*				 that face is added in the global face vector/list.
*/
void faceCreator(HE_vert* v1, HE_vert* v2, HE_vert* v3, HE_vert* v4, std::vector<HE_face*> &faceVector, std::vector<HE_edge*> &edgeVector){

	//Create a new face
	HE_face* face = new HE_face();

	//Giving vertex values
	face->v1 = v1;
	face->v2 = v2;
	face->v3 = v3;
	face->v4 = v4;

	//Each face also has 4 Half Edges
	HE_edge* edge1 = new HE_edge();
	HE_edge* edge2 = new HE_edge();
	HE_edge* edge3 = new HE_edge();
	HE_edge* edge4 = new HE_edge();

	//Give edges a start point/head value
	edge1->start = face->v1;
	edge2->start = face->v2;
	edge3->start = face->v3;
	edge4->start = face->v4;

	//Give edges a end point/tail value
	edge1->end = face->v2;
	edge2->end = face->v3;
	edge3->end = face->v4;
	edge4->end = face->v1;
	
	//Associating each vertex with an emanating edge
	v1->vertEdge = edge1;
	v2->vertEdge = edge2;
	v3->vertEdge = edge3;
	v4->vertEdge = edge4;

	//Giving each Vertex their Normal (for lighting)
	Vector3 vect1;
	Vector3 vect2;
	//Used to get the vectors from start to end and not from origin to end
	Vector3 vectorHelper;

	vect1.x = edge1->end->x;
	vect1.y = edge1->end->y;
	vect1.z = edge1->end->z;
	vect2.x = edge3->end->x;
	vect2.y = edge3->end->y;
	vect2.z = edge3->end->z;
	vectorHelper.x = edge1->start->x;
	vectorHelper.y = edge1->start->y;
	vectorHelper.z = edge1->start->z;
	vect1 = vect1.vector3Subtraction(vectorHelper);
	vect2 = vect2.vector3Subtraction(vectorHelper);
	v1->normal = vect1.vector3Cross(vect2).vector3Normalize();

	vect1.x = edge2->end->x;
	vect1.y = edge2->end->y;
	vect1.z = edge2->end->z;
	vect2.x = edge4->end->x;
	vect2.y = edge4->end->y;
	vect2.z = edge4->end->z;
	vectorHelper.x = edge2->start->x;
	vectorHelper.y = edge2->start->y;
	vectorHelper.z = edge2->start->z;
	vect1 = vect1.vector3Subtraction(vectorHelper);
	vect2 = vect2.vector3Subtraction(vectorHelper);
	v2->normal = vect1.vector3Cross(vect2).vector3Normalize();

	vect1.x = edge3->end->x;
	vect1.y = edge3->end->y;
	vect1.z = edge3->start->z;
	vect2.x = edge1->end->x;
	vect2.y = edge1->end->y;
	vect2.z = edge1->end->z;
	vectorHelper.x = edge3->start->x;
	vectorHelper.y = edge3->start->y;
	vectorHelper.z = edge3->start->z;
	vect1 = vect1.vector3Subtraction(vectorHelper);
	vect2 = vect2.vector3Subtraction(vectorHelper);
	v3->normal = vect1.vector3Cross(vect2).vector3Normalize();

	vect1.x = edge4->end->x;
	vect1.y = edge4->end->y;
	vect1.z = edge4->end->z;
	vect2.x = edge2->end->x;
	vect2.y = edge2->end->y;
	vect2.z = edge2->end->z;
	vectorHelper.x = edge4->start->x;
	vectorHelper.y = edge4->start->y;
	vectorHelper.z = edge4->start->z;
	vect1 = vect1.vector3Subtraction(vectorHelper);
	vect2 = vect2.vector3Subtraction(vectorHelper);
	v4->normal = vect1.vector3Cross(vect2).vector3Normalize();

	//All these 4 edges have an associated face
	edge1->face = face;
	edge2->face = face;
	edge3->face = face;
	edge4->face = face;

	//Associating the next edge in line
	edge1->next = edge2;
	edge2->next = edge3;
	edge3->next = edge4;
	edge4->next = edge1;

	//Associating a HE wih the face
	face->faceEdge = edge1;

	//Add face to the Vector/List
	faceVector.push_back(face);

	//Add the 4 edges to the edge list
	edgeVector.push_back(edge1);
	edgeVector.push_back(edge2);
	edgeVector.push_back(edge3);
	edgeVector.push_back(edge4);
}



/*
*	Name: calcHalfEdgePairs(std::vector<HE_edge*>)
*	Description: Finds the other hald edge for every edge and then completes the pair
*				 by associating the pair edge with the other half edge pair in the
*				 Data Structure.
*/
void calcHalfEdgePairs(std::vector<HE_edge*> &edgeVector){

	std::vector<HE_edge*>::iterator i;
	std::vector<HE_edge*>::iterator j;

	for (i = edgeVector.begin(); i < edgeVector.end(); i++){
		for (j = edgeVector.begin(); j < edgeVector.end(); j++){

			//check if they pairs
			if ((*i)->start == (*j)->end && (*j)->start == (*i)->end){

				(*i)->pair = (*j);
				(*j)->pair = (*i);
			}
		}
	}

	//Check if a pair is still null, Hopefully all HEs got their mates
	for (i = edgeVector.begin(); i < edgeVector.end(); i++){

		if ((*i)->pair == nullptr)
			std :: cout << "We Failed!"<<endl;
	}
}


/*
*	Name: calcFacePoints(std::vector<HE_face*>, std::vector<HE_vert*>)
*	Description: This function for all the faces calculates the face points and then add
*				 those points to the vertexVector list of vertices. Also this function 
*				 associates each face with its face point.
*/
void calcFacePoints(std::vector<HE_face*> &faceVector, std::vector<HE_vert*> &vertexVector){

	std::vector<HE_face*>::iterator i;


	for (i = faceVector.begin(); i < faceVector.end(); i++){
	
		//create new face point
		HE_vert* facePoint = new HE_vert();

		//Calculate the face point coordinates
		(*facePoint).x = ((*i)->v1->x + (*i)->v2->x + (*i)->v3->x + (*i)->v4->x) / 4;
		(*facePoint).y = ((*i)->v1->y + (*i)->v2->y + (*i)->v3->y + (*i)->v4->y) / 4;
		(*facePoint).z = ((*i)->v1->z + (*i)->v2->z + (*i)->v3->z + (*i)->v4->z) / 4;

		(*i)->facePt = facePoint;

		cout << endl;
		cout << (*i)->v1->y << " " << (*i)->v2->y << " " << (*i)->v3->y << " " << (*i)->v4->y << " ==>" << (*i)->facePt->x << "," << (*i)->facePt->y << ","<< (*i)->facePt->z<<endl;
		//Add the face point in the list of vertices
		vertexVector.push_back((*i)->facePt);

	}

}


/*
*	Name: calcEdgePoints(std::vector<HE_edge*>, std::vector<HE_vert*>)
*	Description: This function calculates edge points for each edge and 
*				 then associtates that edge point with each edge. After all 
*				 that the edge point vertex is added to the vertexVector list
*/
void calcEdgePoints(std::vector<HE_edge*> &edgeVector, std::vector<HE_vert*> &vertexVector){

	std::vector<HE_edge*>::iterator i;

	for (i = edgeVector.begin(); i < edgeVector.end(); i++){

		//if value is already calculated then no point creating new edge point
		if ((*i)->pair->edgePt != nullptr)
			(*i)->edgePt = (*i)->pair->edgePt;

		else{
			//create new edge point
			HE_vert* edgePoint = new HE_vert();

			//Calculate the edge point for every edge
			(*edgePoint).x = ((*i)->start->x + (*i)->end->x + (*i)->face->facePt->x + (*i)->pair->face->facePt->x) / 4;
			(*edgePoint).y = ((*i)->start->y + (*i)->end->y + (*i)->face->facePt->y + (*i)->pair->face->facePt->y) / 4;
			(*edgePoint).z = ((*i)->start->z + (*i)->end->z + (*i)->face->facePt->z + (*i)->pair->face->facePt->z) / 4;

			(*i)->edgePt = edgePoint;

			//Add edge point to the vertexVector list
			vertexVector.push_back((*i)->edgePt);
		}

	}
}


/*
*	Name: adjustOldVertices(std::vector<HE_vert*>, std::vector<HE_edge*>, std::vector<HE_face*>)
*	Description: This function calculates the new ajusted position for the old
*				 vertices and then gives those vertices a new adjusted position for 
*				 the new mesh.
*/
void adjustOldVertices(std::vector<HE_vert*> &oldVertexVector, std::vector<HE_edge*> &edgeVector, std::vector<HE_face*> &faceVector){

	std::vector<HE_vert*>::iterator i;

	//Face Point Average and Edge point Average for each Vertex
	HE_vert facePtAvg;
	HE_vert edgePtAvg;
	
	HE_vert * current;
	
	int faceCount;
	int edgeCount;

	HE_edge* adjEdge;

	for (i = oldVertexVector.begin(); i < oldVertexVector.end(); i++){
		
		//Current Vertex
		current = *i;

		faceCount = 0;
		edgeCount = 0;
		

		edgePtAvg.x = 0;
		edgePtAvg.y = 0;
		edgePtAvg.z = 0;

		facePtAvg.x = 0;
		facePtAvg.y = 0;
		facePtAvg.z = 0;

		adjEdge = current->vertEdge;
		
		do{
			faceCount++;
			edgeCount++;

			edgePtAvg.x += adjEdge->edgePt->x;
			edgePtAvg.y += adjEdge->edgePt->y;
			edgePtAvg.z += adjEdge->edgePt->z;

			facePtAvg.x += adjEdge->face->facePt->x;
			facePtAvg.y += adjEdge->face->facePt->y;
			facePtAvg.z += adjEdge->face->facePt->z;

			//Get the next adjacent ede
			adjEdge = adjEdge->pair->next;


		} while (adjEdge != current->vertEdge);

		//Getting Final Edge Point Average Value
		edgePtAvg.x = (edgePtAvg.x) / edgeCount;
		edgePtAvg.y = (edgePtAvg.y) / edgeCount;
		edgePtAvg.z = (edgePtAvg.z) / edgeCount;

		//Getting Final Face Point Average Value
		facePtAvg.x = (facePtAvg.x) / faceCount;
		facePtAvg.y = (facePtAvg.y) / faceCount;
		facePtAvg.z = (facePtAvg.z) / faceCount;

		int n = edgeCount;

		if (n = 3)
			n = 4;

		///Adjusting the old vertex 
		current->x = (facePtAvg.x + (2 * edgePtAvg.x) + ((n - 3)*current->x)) / n;
		current->y = (facePtAvg.y + (2 * edgePtAvg.y) + ((n - 3)*current->y)) / n;
		current->z = (facePtAvg.z + (2 * edgePtAvg.z) + ((n - 3)*current->z)) / n;

	}

}


/*
*	Name: getNewModel(std::vector<HE_vert*>, std::vector<HE_edge*>, std::vector<HE_face*>)
*	Description: Creates a new Sub-Divised model with new faces, new vertices and new edges
*
*/
void getNewModel(std::vector<HE_face*> &faceVector, std::vector<HE_face*> &newFaceVector, std::vector<HE_edge*> &newEdgeVector){

	//Each original face would be divided into 4 new faces
	std::vector<HE_face*>::iterator i;

	//Let the folowing be the main half edges of a face
	HE_edge* edge1;
	HE_edge* edge2;
	HE_edge* edge3;
	HE_edge* edge4;

	//Traversing through all the faces
	for (i = faceVector.begin(); i < faceVector.end(); i++){

		//Lets grab the 4 Half Edges of the current face
		edge1 = (*i)->faceEdge;
		edge2 = edge1->next;
		edge3 = edge2->next;
		edge4 = edge3->next;

		//Create 4 new faces and add them to the Vector Lists for new Faces and new Edges
		faceCreator(edge1->start, edge1->edgePt, edge1->face->facePt, edge1->next->next->next->edgePt, newFaceVector, newEdgeVector);

		faceCreator(edge2->start, edge2->edgePt, edge2->face->facePt, edge2->next->next->next->edgePt, newFaceVector, newEdgeVector);

		faceCreator(edge3->start, edge3->edgePt, edge3->face->facePt, edge3->next->next->next->edgePt, newFaceVector, newEdgeVector);

		faceCreator(edge4->start, edge4->edgePt, edge4->face->facePt, edge4->next->next->next->edgePt, newFaceVector, newEdgeVector);

	}


}

/*
*	Name:createOriginalI()
*	Description: Create all the faces, edges and vertices of the original starting I a.k.a the "coarse mesh"
*				 add the details to all the global vectors/lists. Not this function just adds info to the 
*			     vectors/lists and does not draw the I on the screen.
*/
void createOriginalI(std::vector<HE_vert*> &vertexVector){

	//All the vertices of the front 'I' model
	HE_vert* v1f = new HE_vert();
	HE_vert* v2f = new HE_vert();
	HE_vert* v3f = new HE_vert();
	HE_vert* v4f = new HE_vert();
	HE_vert* v5f = new HE_vert();
	HE_vert* v6f = new HE_vert();
	HE_vert* v7f = new HE_vert();
	HE_vert* v8f = new HE_vert();
	HE_vert* v9f = new HE_vert();
	HE_vert* v10f = new HE_vert();
	HE_vert* v11f = new HE_vert();
	HE_vert* v12f = new HE_vert();
	HE_vert* v13f = new HE_vert();
	HE_vert* v14f = new HE_vert();
	HE_vert* v15f = new HE_vert();
	HE_vert* v16f = new HE_vert();


	//All the vertices of the back 'I' model
	HE_vert* v1b = new HE_vert();
	HE_vert* v2b = new HE_vert();
	HE_vert* v3b = new HE_vert();
	HE_vert* v4b = new HE_vert();
	HE_vert* v5b = new HE_vert();
	HE_vert* v6b = new HE_vert();
	HE_vert* v7b = new HE_vert();
	HE_vert* v8b = new HE_vert();
	HE_vert* v9b = new HE_vert();
	HE_vert* v10b = new HE_vert();
	HE_vert* v11b = new HE_vert();
	HE_vert* v12b = new HE_vert();
	HE_vert* v13b = new HE_vert();
	HE_vert* v14b = new HE_vert();
	HE_vert* v15b = new HE_vert();
	HE_vert* v16b = new HE_vert();


	//Give Values
	//Moving from points on the left to the points on the right

	//X-COOR
	v1f->x = v2f->x = v9f->x = v10f->x = v1b->x = v2b->x = v9b->x = v10b->x = -0.8;

	v4f->x = v3f->x = v12f->x = v11f->x = v4b->x = v3b->x = v12b->x = v11b->x = -0.2;

	v5f->x = v6f->x = v13f->x = v14f->x = v5b->x = v6b->x = v13b->x = v14b->x = 0.2;

	v8f->x = v7f->x = v16f->x = v15f->x = v8b->x = v7b->x = v16b->x = v15b->x = 0.8;


	//Moving from points on the top to the points on the bottom

	//Y-COOR

	v1f->y = v4f->y = v5f->y = v8f->y = v1b->y = v4b->y = v5b->y = v8b->y = 1.0;

	v2f->y = v3f->y = v6f->y = v7f->y = v2b->y = v3b->y = v6b->y = v7b->y = 0.6;

	v9f->y = v12f->y = v13f->y = v16f->y = v9b->y = v12b->y = v13b->y = v16b->y = -0.6;

	v10f->y = v11f->y = v14f->y = v15f->y = v10b->y = v11b->y = v14b->y = v15b->y = -1.0;


	//Moving from points in the front to the points in the back

	//Z-COOR

	v1f->z = v2f->z = v9f->z = v10f->z = v4f->z = v3f->z = v12f->z = v11f->z = v5f->z = v6f->z = v13f->z = v14f->z = v8f->z = v7f->z = v16f->z = v15f->z = 0.5;

	v1b->z = v2b->z = v9b->z = v10b->z = v4b->z = v3b->z = v12b->z = v11b->z = v5b->z = v6b->z = v13b->z = v14b->z = v8b->z = v7b->z = v16b->z = v15b->z = -0.5;

	//Now adding the vertices to the vertex vector/list
	vertexVector.push_back(v1f);
	vertexVector.push_back(v2f);
	vertexVector.push_back(v3f);
	vertexVector.push_back(v4f);
	vertexVector.push_back(v5f);
	vertexVector.push_back(v5f);
	vertexVector.push_back(v6f);
	vertexVector.push_back(v7f);
	vertexVector.push_back(v8f);
	vertexVector.push_back(v9f);
	vertexVector.push_back(v10f);
	vertexVector.push_back(v11f);
	vertexVector.push_back(v12f);
	vertexVector.push_back(v13f);
	vertexVector.push_back(v14f);
	vertexVector.push_back(v15f);
	vertexVector.push_back(v16f);

	vertexVector.push_back(v1b);
	vertexVector.push_back(v2b);
	vertexVector.push_back(v3b);
	vertexVector.push_back(v4b);
	vertexVector.push_back(v5b);
	vertexVector.push_back(v6b);
	vertexVector.push_back(v7b);
	vertexVector.push_back(v8b);
	vertexVector.push_back(v9b);
	vertexVector.push_back(v10b);
	vertexVector.push_back(v11b);
	vertexVector.push_back(v12b);
	vertexVector.push_back(v13b);
	vertexVector.push_back(v14b);
	vertexVector.push_back(v15b);
	vertexVector.push_back(v16b);



	//Now we create faces

	//Front ========
	faceCreator(v1f, v2f, v3f, v4f, faceVector, edgeVector);
	faceCreator(v4f, v3f, v6f, v5f, faceVector, edgeVector);
	faceCreator(v5f, v6f, v7f, v8f, faceVector, edgeVector);


	//FRONT
	// | |
	// | |
	// | |
	faceCreator(v3f, v12f, v13f, v6f, faceVector, edgeVector);


	//Front =======
	faceCreator(v9f, v10f, v11f, v12f, faceVector, edgeVector);
	faceCreator(v12f, v11f, v14f, v13f, faceVector, edgeVector);
	faceCreator(v13f, v14f, v15f, v16f, faceVector, edgeVector);



	//Back ========
	faceCreator(v2b, v1b, v4b, v3b, faceVector, edgeVector);
	faceCreator(v3b, v4b, v5b, v6b, faceVector, edgeVector);
	faceCreator(v6b, v5b, v8b, v7b, faceVector, edgeVector);

	//Back
	// | |
	// | |
	// | |
	faceCreator(v12b, v3b, v6b, v13b, faceVector, edgeVector);

	//Back =======
	faceCreator(v10b, v9b, v12b, v11b, faceVector, edgeVector);
	faceCreator(v11b, v12b, v13b, v14b, faceVector, edgeVector);
	faceCreator(v14b, v13b, v16b, v15b, faceVector, edgeVector);

	//Depth Faces
	faceCreator(v2f, v1f, v1b, v2b, faceVector, edgeVector);
	faceCreator(v1f, v4f, v4b, v1b, faceVector, edgeVector);
	faceCreator(v4f, v5f, v5b, v4b, faceVector, edgeVector);
	faceCreator(v5f, v8f, v8b, v5b, faceVector, edgeVector);
	faceCreator(v8f, v7f, v7b, v8b, faceVector, edgeVector);
	faceCreator(v7f, v6f, v6b, v7b, faceVector, edgeVector);
	faceCreator(v6f, v13f, v13b, v6b, faceVector, edgeVector);
	faceCreator(v13f, v16f, v16b, v13b, faceVector, edgeVector);
	faceCreator(v16f, v15f, v15b, v16b, faceVector, edgeVector);
	faceCreator(v15f, v14f, v14b, v15b, faceVector, edgeVector);
	faceCreator(v14f, v11f, v11b, v14b, faceVector, edgeVector);
	faceCreator(v11f, v10f, v10b, v11b, faceVector, edgeVector);
	faceCreator(v10f, v9f, v9b, v10b, faceVector, edgeVector);
	faceCreator(v9f, v12f, v12b, v9b, faceVector, edgeVector);
	faceCreator(v12f, v3f, v3b, v12b, faceVector, edgeVector);
	faceCreator(v3f, v2f, v2b, v3b, faceVector, edgeVector);

	std::cout << faceVector.size() << endl;
	std::cout << edgeVector.size();

	//Calculate and complete the half edge pairs
	calcHalfEdgePairs(edgeVector);
}


//Draws the 'I'
void drawI(){

	glewInit();

	std::vector<HE_face*>::iterator i;

	//Set Material Properties
	GLfloat black[] = { 0.2, 0.2, 0.2, 5.0 };
	GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

	if (light){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}

	//Clear the Color Buffer, Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(2.0);
	glEnable(GL_BLEND);

	//For Color with lighting
	glEnable(GL_COLOR_MATERIAL);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Switch to drawing perspective
	glMatrixMode(GL_MODELVIEW);

	//Reset the Drawing Perspective/ Clear the Stack
	glLoadIdentity();

	HE_vert cam_lookAt;

	//Calculate the camera position
	cam_lookAt.x = (pow((1 - t), 3) * p0.x) + (3 * pow((1 - t), 2) * t * p1.x) + (3 * (1 - t) * pow(t, 2) * p2.x) + (pow(t, 3) * p3.x);
	cam_lookAt.y = (pow((1 - t), 3) * p0.y) + (3 * pow((1 - t), 2) * t * p1.y) + (3 * (1 - t) * pow(t, 2) * p1.y) + (pow(t, 3) * p3.y);
	cam_lookAt.z = (pow((1 - t), 3) * p0.z) + (3 * pow((1 - t), 2) * t * p1.z) + (3 * (1 - t) * pow(t, 2) * p2.z) + (pow(t, 3) * p3.z);

	//Set bezier curve flow control
	if (t >= 1 || t <= 0)
		direction = !direction;

	if (direction)
		t += 0.001 + speed;

	else
		t -= 0.001 + speed;

	if (texture_mode)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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

	//Set Camera Position
	gluLookAt(cam_lookAt.x, cam_lookAt.y, cam_lookAt.z, 0, 0, 0, 0, 1, 0);

	glTranslatef(0, 0, 0);
	glPushMatrix();

	if (meshview)
	{

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBegin(GL_QUADS);

		//color reset
		if (color > 3)
			color = 0;

		if (color == 0)
			glColor3f(1.0, 1.0, 1.0);

		if (color == 1)
			glColor3f(1.0, 0.0, 0.0);

		if (color == 2)
			glColor3f(0.0, 1.0, .0);

		if (color == 3)
			glColor3f(0.0, 0.0, 1.0);

		//iterate through each face and draw it
		for (i = faceVector.begin(); i < faceVector.end(); i++){

			glNormal3d((*(*i)->v1).normal.x, (*(*i)->v1).normal.y, (*(*i)->v1).normal.z);
			glVertex3d((*(*i)->v1).x, (*(*i)->v1).y, (*(*i)->v1).z);

			glNormal3d((*(*i)->v2).normal.x, (*(*i)->v2).normal.y, (*(*i)->v2).normal.z);
			glVertex3d((*(*i)->v2).x, (*(*i)->v2).y, (*(*i)->v2).z);

			glNormal3d((*(*i)->v3).normal.x, (*(*i)->v3).normal.y, (*(*i)->v3).normal.z);
			glVertex3d((*(*i)->v3).x, (*(*i)->v3).y, (*(*i)->v3).z);

			glNormal3d((*(*i)->v4).normal.x, (*(*i)->v4).normal.y, (*(*i)->v4).normal.z);
			glVertex3d((*(*i)->v4).x, (*(*i)->v4).y, (*(*i)->v4).z);

			

		}
		glEnd();
	}

	else
	{

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBegin(GL_QUADS);
		
		//color reset
		if (color > 3)
			color = 0;

		if (color == 0)
			glColor3f(1.0, 1.0, 1.0);

		if (color == 1)
			glColor3f(1.0, 0.0, 0.0);

		if (color == 2)
			glColor3f(0.0, 1.0, .0);

		if (color == 3)
			glColor3f(0.0, 0.0, 1.0);

		float theta;
		//iterate through each face and draw it
		for (i = faceVector.begin(); i < faceVector.end(); i++){

			theta = atan2((*(*i)->v1).z, (*(*i)->v1).x);
			glNormal3d((*(*i)->v1).normal.x, (*(*i)->v1).normal.y, (*(*i)->v1).normal.z);
			glTexCoord2f((theta + PI) / (TWOPI), ((*(*i)->v1).y / 2.0));
			glVertex3d((*(*i)->v1).x, (*(*i)->v1).y, (*(*i)->v1).z);

			theta = atan2((*(*i)->v2).z, (*(*i)->v2).x);
			glNormal3d((*(*i)->v2).normal.x, (*(*i)->v2).normal.y, (*(*i)->v2).normal.z);
			glTexCoord2f((theta + PI) / (TWOPI), ((*(*i)->v2).y / 2.0));
			glVertex3d((*(*i)->v2).x, (*(*i)->v2).y, (*(*i)->v2).z);

			theta = atan2((*(*i)->v3).z, (*(*i)->v3).x);
			glNormal3d((*(*i)->v3).normal.x, (*(*i)->v3).normal.y, (*(*i)->v3).normal.z);
			glTexCoord2f((theta + PI) / (TWOPI), ((*(*i)->v3).y / 2.0));
			glVertex3d((*(*i)->v3).x, (*(*i)->v3).y, (*(*i)->v3).z);

			theta = atan2((*(*i)->v4).z, (*(*i)->v4).x);
			glNormal3d((*(*i)->v4).normal.x, (*(*i)->v4).normal.y, (*(*i)->v4).normal.z);
			glTexCoord2f((theta + PI) / (TWOPI), ((*(*i)->v4).y / 2.0));
			glVertex3d((*(*i)->v4).x, (*(*i)->v4).y, (*(*i)->v4).z);
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
*	Name: drawModel()
*	Description: This function is called when the Window is resized.
*	Parameters: int width :: current width of the window, int height :: current height of the window
*/
void resize(int width, int height)
{
	//Handing error case of dividing by zero (i.e aspect_ratio = width/height)
	if (height == 0)
		height = 1;

	float aspect_ratio = (float)width / height;
	asp_rat = aspect_ratio;

	//for scalaing
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45, aspect_ratio, 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);

}

//Called when key for next sub division is pressed
void nextSubDivision(){

	//A new face vector is created
	std::vector<HE_face*> newFaceVector;
	//A new edge vector is created
	std::vector<HE_edge*> newEdgeVector;
	//Used to save the old vertices because these are the vertices that need re-adjustments
	std::vector<HE_vert*> oldVertexVector;

	std::vector<HE_face*>::iterator i;

	oldVertexVector = vertexVector;

	calcHalfEdgePairs(edgeVector);

	calcFacePoints(faceVector, vertexVector);
	calcEdgePoints(edgeVector, vertexVector);

	adjustOldVertices(oldVertexVector, edgeVector, faceVector);

	//Prints face vertices on the console for debuggin purposes
	/*for (i = faceVector.begin(); i < faceVector.end(); i++){
		cout << endl;
		cout << (*i)->v1->x << " " << (*i)->v1->y << " " << (*i)->v1->z << endl;
		cout << (*i)->v2->x << " " << (*i)->v2->y << " " << (*i)->v2->z << endl;
		cout << (*i)->v3->x << " " << (*i)->v3->y << " " << (*i)->v3->z << endl;
		cout << (*i)->v4->x << " " << (*i)->v4->y << " " << (*i)->v4->z << endl;
	}*/

	//printAllVertices(vertexVector);
	
	getNewModel(faceVector, newFaceVector, newEdgeVector);
	
	//Could save these old vectors to jump back to a previosu space
	//but not doing so in this program even though its a simple edit
	//......huuhh..

	HE_face* face;
	HE_edge* edge;
	//Delete old Face and Edge Vectors/Lists
	while (!edgeVector.empty()){
		edge = edgeVector.back();
		edgeVector.pop_back();
		delete edge;
	}

	while (!faceVector.empty()){
		face = faceVector.back();
		faceVector.pop_back();
		delete face;
	}

	//old values lost.... new gained!
	faceVector = newFaceVector;
	edgeVector = newEdgeVector;

	glutPostRedisplay();

}


//Some basic map manipulation controls and yaw controls
void keyboard(unsigned char key, int x, int y)
{

	switch (key) {

	//Sub-division
	case 's': nextSubDivision();
		cout << endl << endl << endl;
		cout << "NEXT SUBDIVISION...." << endl;
		break;

	case 'm': meshview = !meshview;
		if (meshview)
			cout << "MESH-VIEW: ON" << endl;
		else
			cout << "MESH-VIEW: OFF" << endl;
		break;

	case 'l': light = !light;
		if (light)
			cout << "LIGHTS: ON" << endl;
		else
			cout << "LIGHTS: OFF" << endl;
		break;

	case 'c': color++;
		cout << "COLOR CHANGED!" << endl;
		break;

	case 't': texture_mode = !texture_mode;
		if (texture_mode)
			cout << "TEXTURE: ON" << endl;
		else
			cout << "TEXTURE: OFF" << endl;
		break;

	case '1': speed -= 0.0001;
		cout << "SPEED DECREASED!" << endl;
		break;

	case '2': speed += 0.0001;
		cout << "SPEED INCREASED!" << endl;
		break;

	case 'r': system("cls");
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

	//mapping the image to the texture
	//Last parameter is the actual pixel data array
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

	return texID;
}

void init(){

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

	delete image;
}


int main(int argc, char** argv)
{
	//Initialize GLUT and OpenGL
	glutInit(&argc, argv);

	//Initializing Window Position on the screen
	glutInitWindowPosition(0, 0);

	//Generating Random Key Points for the Bezier Curve
	//Make sure these random points are not inside the 'I'
	p0.x = -1;
	p0.y = 0;
	p0.z = 7;

	p1.x = -4;
	p1.y = 0;
	p1.z = 1;

	p2.x = 4;
	p2.y = 0; 
	p2.z = 1;

	p3.x = 1;
	p3.y = 0;
	p3.z = 7;

	Image* image = loadBMP("texture_tiles.bmp");
	textureID = loadTexture(image);

	//Initializing Window Size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//Initializing the Initial Display Mode :: RGBA, Double Buffered, Depth (for 3D)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//Setting Up Window Title
	glutCreateWindow(WINDOW_TITLE);

	//Clearing the color Buffer to set the background color in the GLUT Window
	glClearColor(0, 0, 0, 0);

	//Create Coarse Mesh
	createOriginalI(vertexVector);

	//Initialize GLEW
	GLenum e = glewInit();
	if (e != GLEW_OK)
	{
		cout << endl;
		cout << "GLEW unable to Initialize " << endl;
		system("pause");
		exit(1);
	}
	else if (e == GLEW_OK){
		cout << endl;
		cout << "GLEW Initialized " << endl;
	}
	else{
		cout << endl;
		cout << "GLEW unable to Initialize " << endl;
		system("pause");
		exit(1);
	}

	//for lighting
	init();

	//Setup GLUT Callback Functions
	glutReshapeFunc(resize);
	glutDisplayFunc(drawI);
	glutKeyboardFunc(keyboard);

	//Enter Main Loop
	glutMainLoop();

	return 0;
}