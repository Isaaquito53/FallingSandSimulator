# FALLING SAND SIMULATOR (C++ SDL lib)
#### This project is a little falling sand simulator made in C++ using SDL library.
<br/>

Here is a gif of how it looks like in the **version V0-1** :

<img src="/images/FallingSand.gif" width="300">
<br/>

Here is a gif of how it looks like in the **version V0-3** :

<img src="/images/FallingSand_v0-3.gif" width="300">
<br/>

Here is a gif of how it looks like in the **version V0-4** :

<img src="/images/FallingSand_v0-4.gif" width="300">

---
# In this version you can:
- Draw **solid/falling sand/water pixels** on the grid.
- Change between different types of pixel drawing (by clicking the **"Draw pixels"** button).
- Erase pixels (by clicking the **"Erase Grid"** button).
- Clear the grid (by clicking the **"Clear Grid"** button).
- **"Play/Pause"** the simulation.
- Turn on/off the **shader**.

---
# How to run:

You must have SDL3 installed.
<br/>
Make sure that you have all the .hpp, .cpp, and SDL3.dll files.
<br/>
It is recommended to manage all the files with Visual Studio.

---
# Controls:
- Use the **mouse** and hold the **left click to draw** .
- Same controls to **click the bottons** .

---
# What have I learned?:
- I've learned how to make and manage a grid regardless of the screen size.
- I've learned how to do simple physics.
- I've learned how to make a button system.

---
# Changelog:
## V0-3:
- I've added constant variables for the buttons and pixel types.
- I've added a new type of pixel (water pixel).
- I've added the same simulation to water pixel than falling sand pixel.
- I've added dependency between the "Draw pixels" Button and the pixel colors.
- I've added a colors vector to the Button class.
- I've change the options "solid/falling", "clear" and "play/pause" to be part of the Button class.

## V0-4:
- I've finished the water simulation.
- I've added a new button with a new feature named shader that converts the pixels (squares) into points.
- I've added a new button to erase pixels.

---
# TO DO:
- Add new type of pixel (heavy pixel).
- Add a little button to activate/deactivate the other buttons.