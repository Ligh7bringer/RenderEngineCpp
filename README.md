# Render Engine

An OpenGL render engine based on the tutorials made by [ThinMatrix](https://www.youtube.com/playlist?list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP). Written in C++ instead of Java as an exercise.

# Features

* OBJ model loading.
* Textures and mip-mapping.
* Normal mapping.
* Shadows.
* Phong shading and lighting optimisations.
* Terrain generation.
* Realistic water with reflections and refraction.
* GUI rendering.
* Skybox, day-night cycle and fog.
* Probably other things that I am forgetting.

# Building

1. Clone this repo.

2.  ```cd``` into the folder of the project.

3. The required libraries are included as submodules. Initialise them: ```git submodule update --init --recursive```.

4. Use **CMake** to generate a solution or Makefiles. The project is buildable on Windows and Linux.

# Screenshots

![sc](https://i.imgur.com/DeQBOdv.png)
