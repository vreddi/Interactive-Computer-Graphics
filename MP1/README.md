#Project 1 - Dancing 'I'

First Mp for CS 418. Creates an App with interactive functionality for the user. The animation part of the functionality
effectively makes the model 'I' dance, henceforth 'Dancing - I'.
The model is a 10 Triangle model built with traingle fans effectively reducing the number of calls made to glVertex.

This file provides an explaination (user point of view) on how to use this app. The video link is 
provided on the bottom of the file.

###COMPILATION INSTRUCTIONS

This app/project is build on Microsoft Visual Studio. For the submission the entire project has been included.
The main file is cs418mp1.cpp which needs to be compiled.
It requires some header files which are listed as follows:
<code>
<pre lang="markup">
#include <iostream>
#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include "utilityMP1.h" 
(utilityMP1.h file contains global variables, some functions, constant values and function protocols)

[<b><u>Note:</b></u> utilityMP1.h exists in the same folder as the main cs418mp1.cpp file]
</code>
</pre>

###INTERACTIVITY FUNCTIONALITY

(<b><u>Note:</b></u> All of these interactable features with the model are toggable mapped unique keys for each functionality
       to be separate from the other and run independently.) 
[The Instructions for the following functionalities is shown on the console screen.]

- ####Mesh-View ON/OFF  [PRESS <code>m</code> to toggle]

       This functionality allows the User to interact with the model and toggle views between the wire or the 
       mesh view of the 'I' and the solid color view of the 'I'. The mesh view can be used to ensure that there 
       are no T-Junctions in the model.


- ####FPS Display ON/OFF   [PRESS <code>f</code> to toggle]

       This functionality allows the user to view the FPS (frames per second) every second on the console screen.The target          FPS set for this application is 30fps.


- ###Dance ON/OFF       [PRESS <code>-spacebar-</code> to toggle]

       This functionality provides a 'Wiggle' animation to the model 'I'. This is too complete the animation/dancing                 requirement for the machine problem.This function is toggable and once its turned OFF the position of the model is            reset as before. This is basically acheived with the used of periodic functions such as a Sine Function.


- ###Fly-Mode ON/OFF      [PRESS <code>w</code> to toggle]

       This functionality provides the 'flying' animation to the model 'I'. This is in addition to the basic dance animation.        This animation provides movement to the model rather than just static position animations.


- ###Disco-Mode ON/OFF	 [PRESS <code>d</code> to toggle]

       This mode provides the app with a disco effect where the background changes color every 750ms.
       Just a fun functionality to add more feel to the Dancing 'I' app.


- ###Rotation-Mode ON/OFF	    [PRESS <code>r</code> to toggle]

       This functionality when toggled on helps in rotating the model "I' along the y-axis providing a 3D perspective to the        App. The rotation is set to be anti-clockwise.


- ###Increase/Decrease Speed of Rotation	    [PRESS <code>1</code> to Increase and <code>2</code> to Decrease]

       This functionality only works if the the Rotation-Mode is switched ON. If it is, then this functionality helps in             speeding up the rotation or decrease the speed of rotation. This just provides and additional usage to the roation            functionality.


- ###Zooming In/Out     [PRESS <code>z</code> to zoom in and </code>x</code> to zoom out]

       This functionality helps the user to zoom in on the model and zoom out on the model. These zoom ins and outs work even        if the animation is running. This can be used to examine the mesh-view more closely or to have a different view on the        animations.


- ###Change Color of 'I'	     [Press <code>n</code> to Change Color]

       Helps User select Color of the model 'I'. The user has 5 choices of colro through wich the change of color loops              through. The colors include: red, blue, green, pink, orange.


- ###In-App Display ON/OFF      [PRESS <code>o</code> to toggle]

       This functionality draws the current state of the functionalities on the top right corner of the window. This makes it        very useful for th euser to check the current state being ON or OFF.  


- ###Clear Console Screen	    [PRESS <code>c</code> to Clear]

       This functionality clears the console screen. Therefore it helps the console in getting rid of the clutter of                 information.


- ###Exit App	 [PRESS </code>Esc</code> to Exit]

       Used to quit the App.



####Video Link : https://www.youtube.com/watch?v=YuNN_YQ4ka4
----------

(<b><u>Note:</b></u> Snapshots of the project are in the project folder under the folder name "SnapShots")
