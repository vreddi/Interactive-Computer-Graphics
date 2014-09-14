//------------------------------------------------------------------------------------------------------//
/**																										//
*	MP-1 (Dancing 'I')																					//
*	Title: Wiggle Wiggle Wiggle																			//
*																									    //
*	Course: CS 418																						//
*	Author: Vishrut Reddi																				//
*	Net ID: vreddi2																						//
*	Created: September 2014																			    //
*/																							     		//
//------------------------------------------------------------------------------------------------------//
#include <iostream>
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include "utilityMP1.h"

using namespace std;

//Main Function
int main(int argc, char** argv){

	//Used for Displaying command in the console
	instructions();

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

	//Makign first call to the FPS printer (nneded for later use to see displayed FPS)
	displayFPS(0);

	//Setup GLUT Callback Functions
	updatedisplay(0);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(drawModel);
	glutTimerFunc(500, updateDisco, 0);

	//Enter Main Loop
	glutMainLoop();


	return 0;
}


float timeElapsed = 0;				//Current Time Elapsed after triggering animation(dancing) 

/**
* Function: timer()
* Description: Used as a timer for the dancing animation of the model
* Parameters: int value : Requirement fulfilled for glutTimerFunc()
*/
void timer(int value)
{
	if (dancing)
	{
		timeElapsed += 0.2;
		glutPostRedisplay();
		glutTimerFunc(50, timer, 0);
	}

}

float timeElapsed2 = 0;					//Current Time Elapsed after triggering animation(flying)

/**
* Function: timer2()
* Description: Used as a timer for the flying/whoosh animation of the model
* Parameters: int value : Requirement fulfilled for glutTimerFunc()
*/
void timer2(int value)
{
	if (whoosh)
	{
		timeElapsed2 += 0.1;
		glutPostRedisplay();
		glutTimerFunc(50, timer2, 0);
	}

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
	asp_rat = aspect_ratio;


	//for scalaing
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, width, height);

	gluPerspective(45, aspect_ratio, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
}


/**
* Function: drawModel()
* Description: Draing code goes in this function. This is used to draw on the screen. It is also
*			   responsible for the animation and the color change for the model.
* Parameters: (void)
*/
void drawModel()
{
	//Used to make the Model 'Wiggle'
	float sinA, sinB, sinC;
	//Used for the Model the 'Fly'
	float sinX, sinY;

	if (whoosh)
	{
		sinX = sin(timeElapsed2 - 1.5);
		sinY = sin(timeElapsed2 + 1.5);
	}
	if (dancing)
	{
		sinA = 0.2 * sin(timeElapsed - 1.5);
		sinB = 0.2 * sin(timeElapsed - 0.5);
		sinC = 0.2 * sin(timeElapsed + 0.5);
	}
	else
	{
		sinA = 0;
		sinB = 0;
		sinC = 0;
	}


	//Clear the Color Buffer, Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(2.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Switch to drawing perspective
	glMatrixMode(GL_MODELVIEW);
	//Reset the Drawing Perspective/ Clear the Stack
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -5.0);
	glPushMatrix();

	if (whoosh){

		if (zoomer > 1){
			glTranslatef(sinX, sinY, zoomer);
		}
		else if (zoomer < 1){
			glTranslatef(sinX, sinY, -zoomer);
		}
		else
		{
			glTranslatef(sinX, sinY, 0);
		}

		glPushMatrix();

	}

	//(angle to roatate by, x-axis, y-axis, z-axis) : the last 3 parameters determine the axis to rotate the model by
	glRotatef(angle, 0.0, 1.0, 0.0);		//Rotating the z-axis by "angle" degrees

	glScalef(zoomer, zoomer, 1.0);

	//displayClearMessage(0);

	if (meshview)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// ======
		glBegin(GL_TRIANGLE_FAN);
		if (color == 1)
			glColor3f(1.0, 0.0, 0.0);

		else if (color == 2)
			glColor3f(0.0, 1., 0.0);

		else if (color == 3)
			glColor3f(0.0, 0.0, 1.0);

		else if (color == 4)
			glColor3f(1.0, 0.1, 1.0);

		else if (color == 5)
			glColor3f(1.0, 0.5, 0.1);
		else
		{
			glColor3f(1.0, 0.5, 0.0);
			color = 1;
		}
		glVertex3f(-0.6, 0.8 + sinA, 0);
		glVertex3f(-0.6, 0.4 + sinA, 0);
		glVertex3f(-0.2, 0.4 + sinB, 0);

		glVertex3f(0.2, 0.4 + sinB, 0);

		glVertex3f(0.6, 0.4 + sinC, 0);

		glVertex3f(0.6, 0.8 + sinC, 0);

		glEnd();

		/*
		||
		||
		||
		*/
		glBegin(GL_TRIANGLE_FAN);
		if (color == 1)
			glColor3f(1.0, 0.0, 0.0);

		else if (color == 2)
			glColor3f(0.0, 1.0, 0.0);

		else if (color == 3)
			glColor3f(0.0, 0.0, 1.0);

		else if (color == 4)
			glColor3f(1.0, 0.1, 1.0);

		else if (color == 5)
			glColor3f(1.0, 0.5, 0.1);

		else
		{
			glColor3f(1.0, 0.5, 0.0);
			color = 1;
		}

		glVertex3f(-0.2, 0.4 + sinB, 0.0);
		glVertex3f(0.2, 0.4 + sinB, 0);
		glVertex3f(0.2, -0.4 + sinB, 0);

		glVertex3f(-0.2, -0.4 + sinB, 0.0);
		glEnd();

		// ======
		glBegin(GL_TRIANGLE_FAN);
		if (color == 1)
			glColor3f(1.0, 0.0, 0.0);

		else if (color == 2)
			glColor3f(0.0, 1., 0.0);

		else if (color == 3)
			glColor3f(0.0, 0.0, 1.0);

		else if (color == 4)
			glColor3f(1.0, 0.1, 1.0);

		else if (color == 5)
			glColor3f(1.0, 0.5, 0.1);

		else
		{
			glColor3f(1.0, 0.5, 0.0);
			color = 1;
		}
		glVertex3f(0.6, -0.8 + sinC, 0);
		glVertex3f(0.6, -0.4 + sinC, 0);
		glVertex3f(0.2, -0.4 + sinB, 0);

		glVertex3f(-0.2, -0.4 + sinB, 0);

		glVertex3f(-0.6, -0.4 + sinA, 0);

		glVertex3f(-0.6, -0.8 + sinA, 0);
		glEnd();


	}

	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// ======
		glBegin(GL_TRIANGLE_FAN);
		if (color == 1)
			glColor3f(1.0, 0.0, 0.0);

		else if (color == 2)
			glColor3f(0.0, 1., 0.0);

		else if (color == 3)
			glColor3f(0.0, 0.0, 1.0);

		else if (color == 4)
			glColor3f(1.0, 0.1, 1.0);

		else if (color == 5)
			glColor3f(1.0, 0.5, 0.1);

		else
		{
			glColor3f(1.0, 0.5, 0.0);
			color = 1;
		}
		glVertex3f(-0.6, 0.8 + sinA, 0);
		glVertex3f(-0.6, 0.4 + sinA, 0);
		glVertex3f(-0.2, 0.4 + sinB, 0);

		glVertex3f(0.2, 0.4 + sinB, 0);

		glVertex3f(0.6, 0.4 + sinC, 0);

		glVertex3f(0.6, 0.8 + sinC, 0);
		glEnd();

		/*
		||
		||
		||
		*/
		glBegin(GL_TRIANGLE_FAN);
		if (color == 1)
			glColor3f(1.0, 0.0, 0.0);

		else if (color == 2)
			glColor3f(0.0, 1., 0.0);

		else if (color == 3)
			glColor3f(0.0, 0.0, 1.0);

		else if (color == 4)
			glColor3f(1.0, 0.1, 1.0);

		else if (color == 5)
			glColor3f(1.0, 0.5, 0.1);

		else
		{
			glColor3f(1.0, 0.5, 0.0);
			color = 1;
		}
		glVertex3f(-0.2, 0.4 + sinB, 0.0);
		glVertex3f(0.2, 0.4 + sinB, 0);
		glVertex3f(0.2, -0.4 + sinB, 0);

		glVertex3f(-0.2, -0.4 + sinB, 0.0);
		glEnd();


		// ======
		glBegin(GL_TRIANGLE_FAN);
		if (color == 1)
			glColor3f(1.0, 0.0, 0.0);

		else if (color == 2)
			glColor3f(0.0, 1., 0.0);

		else if (color == 3)
			glColor3f(0.0, 0.0, 1.0);

		else if (color == 4)
			glColor3f(1.0, 0.1, 1.0);

		else if (color == 5)
			glColor3f(1.0, 0.5, 0.1);

		else
		{
			glColor3f(1.0, 0.5, 0.0);
			color = 1;
		}
		glVertex3f(0.6, -0.8 + sinC, 0);
		glVertex3f(0.6, -0.4 + sinC, 0);
		glVertex3f(0.2, -0.4 + sinB, 0);

		glVertex3f(-0.2, -0.4 + sinB, 0);

		glVertex3f(-0.6, -0.4 + sinA, 0);

		glVertex3f(-0.6, -0.8 + sinA, 0);
		glEnd();
	}
	glPopMatrix();
	if (whoosh)
		glPopMatrix();

	//Used to see what graphical text info needs to be printed
	checkForText();

	//Swaps the buffers of the current window if double buffered.
	glutSwapBuffers();
	glFlush();
}

/**
* Function: checkForText()
* Description: Used to see what graphical text info needs to be printed. This can be very useful information
*              for the user to check what all animations are currently going on with the model.
* Parameters: (void)
*/
void checkForText()
{
	if (in_app_display)
	{
		if (dancing)
		{
			drawText(-2 * asp_rat, 1.9 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.9 *asp_rat, "Dancing-Mode : ON");
		}
		else
		{
			drawText(-2 * asp_rat, 1.9 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.9 * asp_rat, "Dancing-Mode : OFF");
		}


		if (disco_mode)
		{
			drawText(-2 * asp_rat, 1.8 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.8 * asp_rat, "Disco-Mode : ON");
		}
		else
		{
			drawText(-2 * asp_rat, 1.8 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.8 * asp_rat, "Disco-Mode : OFF");
		}


		if (whoosh)
		{
			drawText(-2 * asp_rat, 1.7 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.7 * asp_rat, "Fly-Mode : ON");
		}
		else
		{
			drawText(-2 * asp_rat, 1.7 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.7 * asp_rat, "Fly-Mode : OFF");
		}


		if (meshview)
		{
			drawText(-2 * asp_rat, 1.6 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.6 * asp_rat, "Meshview : ON");

		}

		else
		{
			drawText(-2 * asp_rat, 1.6 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.6 * asp_rat, "Meshview : OFF");
		}



		if (rotate_mode)
		{
			drawText(-2 * asp_rat, 1.5 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.5 * asp_rat, "Rotation-Mode : ON");
		}
		else
		{
			drawText(-2 * asp_rat, 1.5 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.5 * asp_rat, "Rotation-Mode : OFF");
		}

		if (fps_mode)
		{
			drawText(-2 * asp_rat, 1.4 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.4 * asp_rat, "FPS : ON (Check Cosole)");
		}
		else
		{
			drawText(-2 * asp_rat, 1.4 * asp_rat, "                                       ");
			drawText(-2 * asp_rat, 1.4 * asp_rat, "FPS : OFF");
		}
	}
}

/**
* Function: updateDisco(int)
* Description: This function works when the disco mode is switched ON. It changes the color of the
*			   background every 750ms. Has 4 colors it loops on and on in. Helps provide a disco feel.
*              The colors used however are not so disco-ee :p
*
* Parameters: int value :: used to fulfill the glutTimerFunc requirement
*/
void updateDisco(int value){
	toggle++;
	if (disco_mode == true)
	{
		if (toggle == 1)
			glClearColor(0.9, 0.08, 1, 1);
		else if (toggle == 2)
			glClearColor(1, 1, 0.4, 1);
		else{
			glClearColor(0.0, 1, 0.5, 1);
			toggle = 0;
		}
		glutPostRedisplay();
		glutTimerFunc(750, updateDisco, 0);
	}

	else
		glClearColor(1, 1, 1, 1);

}


/**
* Function: rotation(int)
* Description: This function helps in increasing or decreasing the speed of the rotation.
*			   Note that this only works if the rotation mode is switched ON.
* Parameters: int value :: used to fulfill the glutTimerFunc requirement
*/
void rotation(int value){
	if (rotate_mode)
	{
		angle = angle + speedOfRotation;

		if (angle > 360)
			angle -= 360;
		else if (angle < 0)
			angle += 360;
		glutPostRedisplay();
		glutTimerFunc(50, rotation, 0);
	}
}


/**
* Function: keyboard(usinged char, int, int)
*
* Description: Used for the interactivity aspect of the user. Helps identity the 'command' keys on the keyboard
*			   to toggle the required animation/function for the model 'I'.
*
* Parameters: unsingned char c :: Used to store the ASCII value of the key pressed
*			  itn x,y :: used to fulfill requirement
*/
void keyboard(unsigned char c, int x, int y)
{

	if (c == 27)			//Escape Key used to exit the app
	{
		exit(0);
	}

	else if (c == ' ')
	{
		dancing = !dancing;
		timeElapsed = 0;
		if (dancing)
		{
			cout << endl << "Dancing ON!" << endl;
		}
		else
		{
			cout << endl << "Dancing OFF!" << endl;
		}

		timer(0);

	}

	else if (c == 'd' || c == 'D')
	{
		disco_mode = !disco_mode;
		toggle = 0;
		if (disco_mode)
		{
			cout << endl << "Disco - Mode ON!" << endl;
		}
		else
		{
			cout << endl << "Disco - Mode OFF!" << endl;
		}

		updateDisco(0);
	}

	else if (c == 'w' || c == 'W')
	{
		whoosh = !whoosh;
		timeElapsed2 = 0;
		if (whoosh)
		{
			cout << endl << "Fly Mode ON!" << endl;
		}
		else
		{
			cout << endl << "Fly Mode OFF!" << endl;
		}

		timer2(0);
	}

	else if (c == 'n' || c == 'N')
	{
		color++;
		cout << "Color 'I' Changed!" << endl;

	}

	else if (c == 'f' || c == 'F')
	{
		fps_mode = !fps_mode;
		if (fps_mode)
			cout << endl << "FPS View ON!" << endl;
		else
			cout << endl << "FPS View OFF!" << endl;

	}

	else if (c == 'm' || c == 'M')
	{
		meshview = !meshview;
		if (meshview)
		{
			cout << endl << "Mesh-View ON!" << endl;
		}

		else
		{
			cout << endl << "Mesh-View OFF!" << endl;
		}
	}

	else if (c == 'r' || c == 'R')
	{
		rotate_mode = !rotate_mode;
		speedOfRotation = 5;
		if (rotate_mode)
		{
			cout << endl << "Rotate ON!" << endl;
		}
		else
		{
			cout << endl << "Rotate OFF!" << endl;
		}

		rotation(0);
	}

	else if (c == '1')
	{
		if (rotate_mode)
		{
			cout << "Speed Increased!" << endl;
			speedOfRotation += 5;
		}
	}

	else if (c == '2')
	{
		if (rotate_mode)
		{
			cout << "Speed Decreased!" << endl;
			speedOfRotation -= 5;
		}

	}

	else if (c == 'z' || c == 'Z')
	{
		cout << "Zooming In!" << endl;

		zoomer += 0.01;
	}

	else if (c == 'x' || c == 'X')
	{
		cout << "Zooming Out!" << endl;
		if (zoomer <= 0)
			zoomer = 0.0;
		else
			zoomer -= 0.01;
	}

	else if (c == 'o' || c == 'O')
	{
		in_app_display = !in_app_display;
		if (in_app_display)
			cout << "In App Text Display : ON!" << endl;
		else
			cout << "In App Text Display : OFF!" << endl;
	}

	else if (c == 'c' || c == 'C')
	{
		system("cls");
		instructions();
	}

}

/**
* Function: updatedisplay(int)
* Description: Function is used to render a new frame every 32ms. FPS is also calcuted in the funciton.
* Parameters: int value :: used to fulfill the glutTimerFunc requirement
*/
void updatedisplay(int value)
{
	//To update the display repeatedly
	glutPostRedisplay();

	frameCount++;
	//  Get the number of milliseconds since glutInit called 
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if (timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
	}

	glutTimerFunc(32, updatedisplay, 0);

}

/**
* Function: instructions(int)
* Description: Function used to display the FPS every second on the console window.
*			   The FPS function has to be ON to work/display the FPS.
* Parameters: int value :: used to fulfill the glutTimerFunc requirement
*/
void displayFPS(int value)
{
	if (fps_mode)
		cout << "FPS : " << fps << endl;

	glutTimerFunc(1000, displayFPS, 0);
}

/**
* Function: instructions()
* Description: Function used to print simple instructions for the App on the console window
* Parameters: (void)
*/
void instructions()
{
	cout << "                             *****INSTRUCTIONS*****                      " << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << " m : Mesh-View ON/OFF" << endl;
	cout << " f : FPS Display ON/OFF" << endl;
	cout << " -space- : Dance ON/OFF" << endl;
	cout << " w : Fly 'I' ON/OFF" << endl;
	cout << " d : Disco Mode ON/OFF" << endl;
	cout << " r : Rotation Mode ON/OFF" << endl;
	cout << " 1/2: Increase/Decrease speed of Rotation" << endl;
	cout << " z/x: Zoom In / Zoom Out" << endl;
	cout << " n : Change Color of the 'I'" << endl;
	cout << " o : Display In-App Function States" << endl;
	cout << " c : Clear Console Screen" << endl;
	cout << " Esc: Quit" << endl;
	cout << "--------------------------------------------------------------------------------" << endl << endl;
}
