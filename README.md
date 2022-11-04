# Ember Engine
 The Ember engine is a work in progress cross platform 3D rendering engine using the OpenGL sepcification. 

 ## Build
 ### Windows
 To build run ```bin\premake\windows\premake5 vs2022```
 
 ### MacOS
 To build run ```bin/premake/macos/premake5 gmake```
 
 ### Linux 
 Currently untested on Linux so, good luck 🤷🏻‍♂️🤷🏻‍♂️🤷🏻‍♂️

 ## Memory Reporting
 To ensure no memory leaks are present, I use memory reporting which tracks dynamic heap memory allocation.
 On Windows this is done for you, on MacOS ( for some reason ) this method does not work. However, to test for
 memory leaks run ```leaks --atExit -- ./Sandbox``` in the directory with the executable to detect memory leak 
 information.
