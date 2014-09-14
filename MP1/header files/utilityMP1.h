/* CONSTANT VALUES */
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const char* WINDOW_TITLE = "Wiggle Wiggle Wiggle";

/* GLOBAL VARIABLES (USED TO STORE TOGGLE VALUES) */
int color = 1;								//To switch between color of 'I'
int toggle = 0;								//To switch between disco color lighting
float angle = 0.0;						//Used for the rotation of the model
float zoomer = 1.0;						//Used to Zoom in and Out for the Model (Tells us the value of the z Axis the model is currently translated at)
float speedOfRotation;					//Stores the current spped of rotation for the model
float whoosh_factor = 10;			//A factor reponsible for the flying animation
float asp_rat;						// variable used to store the aspect ratio of the window

//Variables used for FPS and FPS calculation
float fps;
int frameCount = 0;
int currentTime = 0;
int previousTime = 0;


static bool meshview = false;			//Mesh-View Originally OFF || Variable used for Mesh-View Toggle
static bool disco_mode = false;			//Disco-Mode Originally OFF || Variable used for Disco-Mode Toggle
static bool fps_mode = false;			//FPS Originally OFF || Variable used for FPS Toggle
static bool dancing = false;			//Dance Originally OFF || Variable used to Make the 'I' dance
static bool rotate_mode = false;				//Rotate Originally OFF || Vairiable used to make the model rotate
static bool whoosh = false;						//Whoosh Originally OFF || Variable used to make the model fly
static bool in_app_display = false;				//In App Display Originally OFF || Used to display/draw the current animation info on the screen

/* FUNCTION LIST */

void instructions(void);			//Display "commands" on the console
void updatedisplay(int value);
void drawModel(void);
void updateDisco(int value);
void checkForText(void);
void keyboard(unsigned char c, int x, int y);
void updateRotation(int value);							//Updates the Rotation of the model (right & left direction)
void displayClearMessage(int value);
void displayFPS(int value);						//Used to print FPS on the Console
void timer(int value);
void timer2(int value);
void resize(int width, int height);



/**
* Function: drawText()
*
* Description: Used to display graphical text on the GLUT window. This helps the user know which function is activated
*			   and also is aethetically pleasing.
*
* Parameters: float x :: used for the x-coordinate position of the text starting point
*			  float y :: used for the y-coordinate position of the text starting point
*			  char *text :: Used to get the string/text to print on the screen
*
*/
void drawText(float x, float y, char *text)
{
	int length = strlen(text);		//Grabs the length of the text

	glColor3f(0, 0, 0);

	//Position to draw the text
	glRasterPos2f(x, y);

	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < length; i++)
	{
		//2nd parameter is sent as integers as the function needs the ASCII codes
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);
}