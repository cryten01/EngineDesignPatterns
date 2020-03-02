# EngineDesignPatterns

A repository for testing out different design patterns in an openGL environment.


## Requirements

Development and tests were done under following environment:

* Windows 10 Pro v.1903
* Visual Studio CE 2019
* Intel Iris Graphics 6100

## Setup

Just open `generateProject.bat` to generate a project for Visual Studio 2019.

## Usage

Open `src/Params.h` for controlling the following scene parameters:

* ECS_MODE = Runs the demo in either Classic or ECS mode.
* NR_OF_ENTITIES = Determines the number of created entities.
* FIRST_FPS_CAPTURE_TIME = Determines the first time point for capturing FPS
* SECOND_FPS_CAPTURE_TIME = Determines the second time point for capturing FPS.


## Tests

Test results are stored by capturing frame times in either:
* `assets/profiling/classic.fps` when ECS_MODE is turned on
* `assets/profiling/ecs.fps` when ECS_MODE is turned off


## Built with

* [Premake 5.0](https://premake.github.io/) - Build management tool
* [GLAD](https://glad.dav1d.de/) - For loading functions inside the graphics driver
* [GLFW](https://www.glfw.org/download.html) - For window and input management
* [GLM](https://glm.g-truc.net/0.9.9/index.html) - An openGL math library


## Findings

* Avoid expensive runtime operations in system update loops!
    * Map lookups
    * Transformations (especially glm::rotate())