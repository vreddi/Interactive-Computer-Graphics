README FILE FOR CS 418 'Teapot Contest'
------------------------------------

Fourth Mp and Final MP for CS 418. This App loads "coarse mesh" a basic 32 vertices model of 'I'. Catmull-Clark subdivision is
used on the mesh/model to get the next smoother mesh. The model moves along a Bezier Curve. Colors, Lighting, Textures, Subdivisions
and some other misc. functionalities are implemented. The following has been acheived as per the requirements

* Subdivision (atleast 2) -> 3 are shown in the demo but actually you can go on forever if you have enough memory and processing power
* Cubic space curve camera path (Bezier Curve)
* Appearance (texture/lighting/color)
* The code compiles and runs
* Documentation is presented

This file provides an explaination (user point of view) on how to use this app. The video link is 
provided on the bottom of the file.

COMPILATION INSTRUCTIONS
-------------------------
[Note: Source Code folder is CS 418 MP4]

This app/project is build on Microsoft Visual Studio. For the submission the entire project has been included.
The main file is Source.cpp which needs to be compiled.
It requires some header files which are listed as follows:

#include <iostream>
#include <glut.h>	(#include <GL/gl.h> and #include <GL/glu.h> are inside glut.h)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include "imageloader.h"
#include "mp4utility.h"
#include "Vector3.h" (Contains the Vector3 Class with its functionalities)
#include "Point3.h" (Contains the Point3 Class with its functionalities)

[Note:Vector3.h & Point3.h exists in the same folder as the main main.cpp file]

[NOTE: imageloader.h and imageloader.cpp are files in the project that are not written by me. Those files
are used for the sole purpose of loading images (.BMP files). All Credit goes to www.videotutorialsrock.com for 
providing those image loading files]

INTERACTIVITY FUNCTIONALITY (CONTROLS)
--------------------------------------
[Note: Console Displays all the control changes.]

*  S-Key  [PRESS 'S' to go to next Subdivision]

Press 'S' to move to the next Catmull Clark Subdivision


* C-Key   [PRESS 'C' to Change Color]

Press 'C' to change color of the model/mesh. The colors include white, red, green and blue.


* M-Key      [PRESS 'M' to toggle Mesh-View]

Pressing 'M' will allow the user to toggle between mesh view and solid model view.


* T-Key    [PRESS 'T' to toggle Texture]

Pressing 'T' will allow the user to switch the textures ON and OFF (used as a switch) for the surface of the
model.

* L-Key	 [PRESS 'L' to toggle Lights]

Used to toggle lights ON and OFF.


* 1-Key    [PRESS '1' to Speed Up]

Allows the user to speed down the movement of the model along the Bezier curve.


* 2-Key       [Press '2' to Speed Down]

Allows the user to speed up the movement of the model along the Bezier curve.



Video Link : https://www.youtube.com/watch?v=l-GnZPeZP4s
----------

(Note: Snapshots of the project are in the project folder under the folder name "Snapshots")
