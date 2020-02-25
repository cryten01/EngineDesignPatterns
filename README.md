# EngineDesignPatterns

![Gearwheels](https://cdn.imgbin.com/18/6/5/imgbin-logo-symbol-gear-wheel-symbol-vB8kKtVF55bMBPNst8bTXhgJK.jpg)

A repository for testing out different design patterns in an openGL environment.

## Requirements

Development and tests are done under following environment:

* Windows 10 Pro v.1903
* Visual Studio CE 2019
* Intel Iris Graphics 6100

## Setup

Just use open `generateProject.bat` to generate the project for Visual Studio 2019.

Otherwise follow the instructions below:

### GLAD
If not already in the repository download [GLAD](https://glad.dav1d.de/) and select the following options:
* Language: C/C++
* Specification: OpenGL
* gl: Version 4.6
* Profile: Compatibility  

Then click on Generate and download *glad.zip*. Take the *include* and *src* folder from the zip file and store them inside a new folder called *EngineDesignPatterns/external/GLAD*. 

### GLFW
When using Windows 64-bit download the [Windows pre-compiled binaries](https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.bin.WIN64.zip) and paste the following inside *EngineDesignPatterns/external/GLFW* (create if necessary): 
* The *include* folder
* Create a new folder called *lib* and paste the *lib-vc2019* content (IDE dependent)


## Built with

* [Premake 5.0](https://premake.github.io/) - Build management tool
* [GLAD](https://glad.dav1d.de/) - For loading functions inside the graphics driver
* [GLFW](https://www.glfw.org/download.html) - For window and input management
* [GLM](https://glm.g-truc.net/0.9.9/index.html) - An openGL math library
