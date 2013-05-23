LunarLander
===========
This is a 2D game written in C++ with Xlib


Enhancements:
1. pseudo-randomly generated and scrollable map
* the map is scrollable so that spaceship can naviagtve around
* performance optimization: only on-screen map is rendered, all off-screen terrain is NOT rendered to save memory


2. spaceship animation
* animation is achieved by loading 11 frames of bitmaps, and play each of them as time passed by
