# Ember Engine
 The Ember engine is a work in progress cross platform 3D rendering engine using the OpenGL sepcification. 

 ## Build
 First clone the repository using:
 ```git clone --recursive git@github.com:Brett-Constantinoff/Ember.git```
 
 ### Windows
 To build run ```bin\premake\windows\premake5 vs2022```
 
 ### MacOS
 To build run ```./bin/premake/macos/premake5 gmake```
 This will generate a Makefile which you can use to compile the code using the command
 ```Make``` in the root of the repository
 
 ### Linux 
 Currently untested on Linux.

## TO-DO
* ~~Load Obj files~~
* Create fully working GUI
* Dynamic shadow mapping
* textured objects
* Enhanced lighting
* Skyboxes
* PBR

## Progress
* ~~Load Obj Files~~
![Capture](https://user-images.githubusercontent.com/77081808/225159901-6c393698-6e36-41f7-b072-52e6a802ab82.PNG)


## Third Party Libraries
* GLFW - handles window creation
* Glad - contains all OpenGL function declarations
* GLM - a great math library for graphics programming
* STB - a lightweight header only image loading library
* IMGUI - a gui library that integrates very well with OpenGL projects
* TinyOBJ - a lightweight header only library for loading and rendering .obj files

 ## Memory Reporting
 To ensure no memory leaks are present, I use memory reporting which tracks dynamic heap memory allocation.
 On Windows this is done for you, on MacOS this method does not work (since it is a visual studio feature). However, to test for
 memory leaks run ```leaks --atExit -- ./Sandbox``` in the directory with the executable to detect memory leak 
 information.

 If youre compiling on windows and not using Visual Studio the memory reporting will likely result in errors, so i recommend using 
 Visual Studio for best results.
