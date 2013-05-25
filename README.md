LunarLander
===========
This is a 2D game written in C++ with Xlib

To Compile and Run: 
- 'make run' will trigger the compile and run and game
- The source code uses Xlib. If you are running this on Mac, you need to install xQuartz from http://xquartz.macosforge.org/landing/
- linker option in Makefile might need to be chagned based on the location of your Xlib

Basic Controls:
- SPACE to start the game or pause the game (depending what mode the application is in)
- q to quit the game and exit the application
- arrow keys to activate thrusters

Enhancements:
1. pseudo-randomly generated and scrollable map
* the map is scrollable so that spaceship can naviagtve around
* performance optimization: only on-screen map is rendered, all off-screen terrain is NOT rendered to save memory


2. spaceship animation
* animation is achieved by loading 11 frames of bitmaps, and play each of them as time passed by
