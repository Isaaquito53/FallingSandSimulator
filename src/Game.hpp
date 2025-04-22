#pragma once
#include "Utilities.hpp"
#include "Button.hpp"
#include "Grid.hpp"

/* GAME CLASS */

class Game {
public:
	void GameInit();					// init the game
	void GameLoop();					// main game loop
	void ManageEvents();				// manage all keyboard/mouse events
	void AddPixel(float px, float py);		// add a pixel in the grid by a position in the screen
	void DrawButton();					// draw a button depending on its ID
	void DrawPixels();					// draw all pixels in the grid
	void RemoveAllPixels();				// remove all pixels in the grid

	bool m_run;							// if true, run the main game loop
	SDL_Renderer* m_rend;				// SDL renderer
	SDL_Window* m_win;					// SDL window
	SDL_Event m_e;						// SDL event
	int m_clearGrid;					// if 1, clear the grid and put this variable back to 0
	int m_solidOrFalling;				// draw solid pixel or falling pixel (0: solid, 1: falling sand)
	vector<int> m_solidColor;			// R,G,B for solid pixels
	vector<int> m_fallingColor;			// R,G,B for falling sand pixels
	SDL_FRect m_pixel;					// rectangle that will be drawn at DrawPixels() method
	Grid m_grid;						// grid where everything is drawn
	bool m_mouseDown;					// if true, draw pixels on the grid
	float m_mouseX;						// keeps track of the mouse X coordinate
	float m_mouseY;						// keeps track of the mouse Y coordinate
	vector<Button> m_buttons;			// menu buttons
};