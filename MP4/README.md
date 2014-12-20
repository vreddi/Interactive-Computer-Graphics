#Project 4 - 'Surface Subdivision'


Fourth Mp and Final MP for CS 418. This App loads "coarse mesh" a basic 32 vertices model of 'I'. Catmull-Clark subdivision is used on the mesh/model to get the next smoother mesh. The model moves along a Bezier Curve. Colors, Lighting, Textures, Subdivisions and some other misc. functionalities are implemented. The following has been achieved as per the requirements

![Alt Text](https://github.com/vreddi/Interactive-Computer-Graphics--CS-418-/blob/master/MP4/Snapshots/Subdivision%20Level%203.png)

- Subdivision (atleast 2) -> 3 are shown in the demo but actually you can go on forever if you have enough memory and processing power
- Cubic space curve camera path (Bezier Curve)
- Appearance (texture/lighting/color)
- The code compiles and runs
- Documentation is presented

This file provides an explanation (user point of view) on how to use this app. The video link is 
provided on the bottom of the file.

###COMPILATION INSTRUCTIONS

[Note: Source Code folder is src]

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
GL/glew.h
imageloader.h
string
fstream
mp4utility.h
Vector3.h (Contains the Vector3 Class with its functionalities)
Point3.h (Contains the Point3 Class with its functionalities)
</code>
</pre>
[<b><u>Note:</b></u> Vector3.h & Point3.h exists in the same folder as the main Source.cpp file]

[<b></u>Note:</b></u> imageloader.h and imageloader.cpp are files in the project that are not written by me. Those files
are used for the sole purpose of loading images (.BMP files). All Credit goes to www.videotutorialsrock.com for 
providing those image loading files]

###INTERACTIVITY FUNCTIONALITY (CONTROLS)


- ####S-Key  [PRESS <code>S</code> to go to next Subdivision]

    Press 'S' to move to the next Catmull Clark Subdivision


- ####C-Key  [PRESS <code>C</code> to change color]

   Press 'C' to change color of the model/mesh. The colors include white, red, green and blue.


- ####T-Key       [PRESS <code>LEFT_ARROW_KEY</code> to toggle Texture]

    Pressing 'T' will allow the user to switch the textures ON and OFF (used as a switch) for the surface of the
model.


- ####M-Key     [PRESS <code>M</code> to toggle Mesh-View]

    Pressing 'M' will allow the user to toggle between mesh view and solid model view.


- ####Q-Key	 [PRESS <code>Q</code> to Yaw]

    Allows the user to look at their left


- ####L-Key       [Press <code>L</code> to toggle Lighting]

    This acts as a light switch. THis is a toggle button which would enable the user to switch the lighting ON 
    or OFF. Initially when the App launches the lighting is OFF by default.


- ####1-Key	      [Press <code>1</code> to Speed Down]

    Allows the user to speed down the movement of the model along the Bezier curve.
    

- ####2-Key	      [Press <code>2</code> to Speed Up]

    Allows the user to speed up the movement of the model along the Bezier curve.


####Video Link : https://www.youtube.com/watch?v=l-GnZPeZP4s
----------

(<b><u>Note:</b></u> Snapshots of the project are in the project folder under the folder name "Snapshots")
