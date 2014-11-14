#Project 3 - 'Teapot Contest'


Third Mp for CS 418. This App loads a teapot objects ("Utah Teapot") and allows the user to view the teapot
as a 3D object from different angles. Texture Mapping and Environment Mapping (using sphere mapping) is also 
implemented. 
![Alt Text](https://github.com/vreddi/Interactive-Computer-Graphics--CS-418-/blob/master/MP3/SnapShots/teapot1.png)

- Triangles are loaded properly from the .obj file
- Rendering uses perspective distortion/projection
- Hidden Surfaces are removed
- The Surface of the teapot realistically illuminates from one or more light sources
- Texture is mapped on the surface
- Surface reflects an environment

This file provides an explaination (user point of view) on how to use this app. The video link is 
provided on the bottom of the file.

###COMPILATION INSTRUCTIONS

[Note: Source Code folder is CS 418_MP2_vreddi2]

This app/project is build on Microsoft Visual Studio. For the submission the entire project has been included.
The main file is Source.cpp which needs to be compiled.
It requires some header files which are listed as follows:
<code>
<pre lang="markup">
iostream
glut.h	(GL/gl.h and GL/glu.h are inside glut.h)
stdio.h
stdlib.h
math.h
cstdlib
GL/glew.h
imageloader.h
string
fstream
mp3utility.h
camera.h (Contains the Camera Class and its functionalities)
Vector3.h (Contains the Vector3 Class with its functionalities)
Point3.h (Contains the Point3 Class with its functionalities)
</code>
</pre>
[<b><u>Note:</b></u> camera.h, Vector3.h & Point3.h exists in the same folder as the main main.cpp file]

[<b></u>Note:</b></u> imageloader.h and imageloader.cpp are files in the project that are not written by me. Those files
are used for the sole purpose of loading images (.BMP files). All Credit goes to www.videotutorialsrock.com for 
providing those image loading files]

###INTERACTIVITY FUNCTIONALITY (CONTROLS)

[<b><u>Note:</b></u> Console Displays all vector positions including the camera position at every flight position change.]

- ####Up Arrow Key  [PRESS <code>UP_ARROW_KEY</code> to pitch]

Allows the user to look up in the scene.


- ####Down Arrow Key   [PRESS <code>DOWN_ARROW_KEY</code> to pitch]

Allows the User to look down in the scene


- ####Left Arrow Key       [PRESS <code>LEFT_ARROW_KEY</code> to roll]

Allows the user to roll the view camera to produce different angles of viewing.


- ####Right Arrow Key     [PRESS <code>RIGHT_ARROW_KEY</code> to roll]

Allows the user to roll the view camera to produce different angles of viewing.

- ####Q-Key	 [PRESS <code>Q</code> to Yaw]

Allows the user to look at their left


- ####W-Key	    [PRESS <code>W</code> to Yaw]

Allows the User to look at their right.


- ####L-Key       [Press <code>L</code> to toggle]

This acts as a light switch. THis is a toggle button which would enable the user to switch the lighting ON 
or OFF. Initially when the App launches the lighting is ON by default.

- ####T-Key	      [Press <code>T</code> to toggle]

Allows the user to switch between normal object, texture mapped object and environment mapped object.

the loop goes like this:
normal OBJ -> Texture OBJ -> Environment OBJ -> Texture OBJ -> normal OBJ


####Video Link : https://www.youtube.com/watch?v=OG5qles9uAc
----------

(<b><u>Note:</b></u> Snapshots of the project are in the project folder under the folder name "Snapshots")
