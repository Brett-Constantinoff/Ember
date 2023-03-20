# Ember Engine
 The Ember engine is a work in progress 3D rendering engine targeted for the Windows operating system using the OpenGL specification. 

 # Platforms
 This project was built with the thought of cross compatability in mind, meaning it would succesfully build and run 
 on windows, macos and linux. However, the MacOS version was unstable and did not perform as inteded. This means that I 
 will switch to windows development for the time being.

 This shift will allow me to focus more on adding the features I want to add without worrying about cross 
 platform specifications. This isnt to say that this project will stay on windows forever and in the future Im
 making it a goal to fully incorporate cross platform capabilities.

 ## Build
 First clone the repository using:
 ```git clone --recursive git@github.com:Brett-Constantinoff/Ember.git```
 
 To build run ```bin\premake\windows\premake5 vs2022```

 This will generate a visual studio solution file in the root 
 directory which you can then use the build the poject
 
 ## How To Use
 To move the camera use the WASD keys, to look around hold down the right mouse button and move the mouse. Zoom by using the middle scroll wheel while holding the right mouse button.

## Abstraction
Almost every object in Ember needs to be initialized with some creation information (much like the Vulkan specification), this allows for the creation
of objects to be much more verbose which increases the freedom the user has to customize their experience however they like. In practice this looks like the following:
```cpp
CreateInfoStruct createInfo{};

// setup the information stored inside the create info

newEmberObject = std::make_shared<EmberObject>(createInfo);
```

## TO-DO
* ~~Load Obj files~~
* Create fully working GUI
* Dynamic shadow mapping
* ~~Textured objects~~
* Enhanced lighting
* ~~Skyboxes~~
* PBR
* Add cross platform support

## Progress
* ~~Load Obj Files~~
![Capture](https://user-images.githubusercontent.com/77081808/225159901-6c393698-6e36-41f7-b072-52e6a802ab82.PNG)

* ~~Textured Objects~~
![Capture](https://user-images.githubusercontent.com/77081808/226477935-ce80d92f-b360-4189-925d-8289e77910c1.PNG)

* ~~Skyboxes~~
![Capture](https://user-images.githubusercontent.com/77081808/226146545-6890dfc5-ec24-4ba8-a454-ed4a9b92c193.PNG)



## Third Party Libraries
* GLFW - handles window creation
* Glad - contains all OpenGL function declarations
* GLM - a great math library for graphics programming
* STB - a lightweight header only image loading library
* IMGUI - a gui library that integrates very well with OpenGL projects
* TinyOBJ - a lightweight header only library for loading and rendering .obj files
