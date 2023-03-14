# Ember Engine
 The Ember engine is a work in progress cross platform 3D rendering engine using the OpenGL sepcification. 

 ## Build
 ### Windows
 To build run ```bin\premake\windows\premake5 vs2022```
 
 ### MacOS
 To build run ```bin/premake/macos/premake5 gmake```
 
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
https://1drv.ms/i/s!Ag6HQiJ8N22whsFAuviiIgdmikd19w?e=6Rjsvc


 ## Memory Reporting
 To ensure no memory leaks are present, I use memory reporting which tracks dynamic heap memory allocation.
 On Windows this is done for you, on MacOS this method does not work (since it is a visual studio feature). However, to test for
 memory leaks run ```leaks --atExit -- ./Sandbox``` in the directory with the executable to detect memory leak 
 information.

 If youre compiling on windows and not using Visual Studio the memory reporting will likely result in errors, so i recommend using 
 Visual Studio for best results.
