#Project 2 - 'FLight Simulator'

Second Mp for CS 418. This is a simple Flight Simulator App which provides basic interactive flight controls
to the users. The only view avaialble is the cockpit view. The aircraft can perform rolls, piching and yaws. The 
aircraft translates/moves at a constant speed which cannot be changed (In the current design of the App).

![Alt Text](https://github.com/vreddi/Interactive-Computer-Graphics--CS-418-/blob/master/MP2/SnapShots/Image1.png)

This file provides an explaination (user point of view) on how to use this app. The video link is 
provided on the bottom of the file.

###COMPILATION INSTRUCTIONS

[Note: Source Code folder is CS 418_MP2_vreddi2]

This app/project is build on Microsoft Visual Studio. For the submission the entire project has been included.
The main file is Source.cpp which needs to be compiled.
It requires some header files which are listed as follows:

#include <iostream>
#include <glut.h>	(#include <GL/gl.h> and #include <GL/glu.h> are inside glut.h)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include "camera.h" (Contains the Camera Class and its functionalities)
#include "Vector3.h" (Contains the Vector3 Class with its functionalities)
#include "Point3.h" (Contains the Point3 Class with its functionalities)

[Note: camera.h, Vector3.h & Point3.h exists in the same folder as the main Source.cpp file]
<code>
<pre lang="markup">
iostream.h
glut.h    (GL/gl.h and GL/glu.h are inside glut.h)
stdio.h
stdlib.h
math.h
string.h
camera.h (Contains the Camera Class and its functionalities)
Vector3.h (Contains the Vector3 Class with its functionalities)
Point3.h (Contains the Point3 Class with its functionalities)
</code>
</pre>

[Note: All the header files are in the "header files" folder. While compiling they have to be in proper directory 
(Source Folder Directory),otherwise it would not be able to find the header files.]

###INTERACTIVITY FUNCTIONALITY

(<b><u>Note:</b></u> [Console Displays all vector positions including the camera position at every flight position change.]

- ####Up Arrow Key  [PRESS <code>UP_ARROW_KEY</code> to pitch]

       the aircraft pitches down by a certain pre-defined angle.

- ####Down Arrow Key   [PRESS <code>DOWN</code> to toggle]

       The aircraft pitches up by a certain pre-defined angle.

- ###Left Arrow Key       [PRESS <code>LEFT_ARROW_KEY</code> to toggle]
      The aircraft rolls clockwise/ right to left by a pre-defined small angle.

- ###Right Arrow Key      [PRESS <code>RIGHT_ARROW_KEY</code> to toggle]

       The aircraft rolls clockwise/ right to left by a pre-defined small angle.

- ###Q-Key	 [PRESS <code>Q</code> to Yaw]

       The aircraft Yaws towards the right by pre-defined small angle.

- ###W-Key	    [PRESS <code>W</code> to Yaw]

       The aircraft Yaws towards the left by pre-defined small angle.


####Video Link : https://www.youtube.com/watch?v=bLDG3PzZLZA
----------

(<b><u>Note:</b></u> Snapshots of the project are in the project folder under the folder name "Snapshots")
