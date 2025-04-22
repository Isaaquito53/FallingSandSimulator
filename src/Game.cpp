#pragma once
#include "Game.hpp"

/* GAME METHODS */

void Game::GameInit() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("FallingSandSim", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &m_win, &m_rend);
	m_run = true;
	// set R,G,B of solid pixels
	m_solidColor.push_back(200);
	m_solidColor.push_back(200);
	m_solidColor.push_back(200);
	// set R,G,B of falling sand pixels
	m_fallingColor.push_back(160);
	m_fallingColor.push_back(120);
	m_fallingColor.push_back(20);

	// clear the grid and set solid pixels as the initial drawing tool
	m_grid.InitGrid();
	m_clearGrid = 0;
	m_solidOrFalling = 0;

	m_mouseDown = false;

	// create buttons
	Button solidFallingButton(0, 0, 230, 20, "Solid/Falling");
	m_buttons.push_back(solidFallingButton);
	Button clearGrid(0, 25, 230, 20, "Clear Grid");
	m_buttons.push_back(clearGrid);
}

void Game::ManageEvents() {
	while (SDL_PollEvent(&m_e)) {
		// if you click the cross button the game loop stops
		if (m_e.type == SDL_EVENT_QUIT) {
			cout << "F";
			m_run = false;
		}
		// manage pixel drawing
		if (m_e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			SDL_GetMouseState(&m_mouseX, &m_mouseY);
			// buttons management
			for (Button b : m_buttons) {
				if (b.m_id == "ID_Solid/Falling")
					b.Action(m_mouseX, m_mouseY, m_solidOrFalling);
				if (b.m_id == "ID_Clear Grid")
					b.Action(m_mouseX, m_mouseY, m_clearGrid);
			}
			m_mouseDown = true;
		}
		else if (m_e.type == SDL_EVENT_MOUSE_BUTTON_UP)
			m_mouseDown = false;
	}
}

void Game::AddPixel(float px, float py) {
	// convert screen pixels to grid pixels and add pixel to the grid
	m_grid.AddPixel(px / GAME_SCALE, py / GAME_SCALE, m_solidOrFalling);
}

void Game::DrawPixels() {
	// draw all the pixels of the grid (only solid/falling sand pixels)
	SDL_SetRenderScale(m_rend, 1, 1);
	for (int r = 0; r < m_grid.m_nRows; r++) {
		for (int c = 0; c < m_grid.m_nCols; c++) {
			if (m_grid.m_matrix[r][c] != 2) {
				// convert grid pixels to screen pixels
				m_pixel.x = r * GAME_SCALE;		m_pixel.y = c * GAME_SCALE;
				m_pixel.w = GAME_SCALE;			m_pixel.h = GAME_SCALE;
				if (m_grid.m_matrix[r][c] == 0)
					SDL_SetRenderDrawColor(m_rend, m_solidColor[0], m_solidColor[1], m_solidColor[2], SDL_ALPHA_OPAQUE);
				else
					SDL_SetRenderDrawColor(m_rend, m_fallingColor[0], m_fallingColor[1], m_fallingColor[2], SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(m_rend, &m_pixel);
 			}
		}
	}
}
 
void Game::RemoveAllPixels() {
	m_grid.ClearGrid();
}

void Game::DrawButton() {
	for (Button b : m_buttons) {
		// draw a rectangle that show where you can click this button
		SDL_SetRenderDrawColor(m_rend, 155, 155, 155, SDL_ALPHA_OPAQUE);
		SDL_SetRenderScale(m_rend, 1, 1);
		SDL_RenderFillRect(m_rend, &b.m_actionArea);
		// display the text of the button
		SDL_SetRenderDrawColor(m_rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_SetRenderScale(m_rend,2, 2);
		SDL_RenderDebugText(m_rend, b.m_actionArea.x/2, b.m_actionArea.y/2, b.m_text.c_str());
	}
}

void Game::GameLoop() {

	int d = 0;		// delta time

	while (m_run) {
		// manage events
		ManageEvents();
		// clear grid
		if (m_clearGrid) {
			RemoveAllPixels();
			m_clearGrid = 0;
		}
		// manage drawing on the grid
		if (m_mouseDown) {
			SDL_GetMouseState(&m_mouseX, &m_mouseY);
			AddPixel(m_mouseX, m_mouseY);
		}
		// clear the window
		SDL_SetRenderDrawColor(m_rend, 0, 0, 0, 255);
		SDL_RenderClear(m_rend);
		// draw all pixels of the grid
		DrawPixels();
		// draw Button
		DrawButton();
		// render all
		SDL_RenderPresent(m_rend);

		// upgrade state of falling sand pixels
		if (d >= GAME_SPEED) {
			m_grid.FallingSand();
			d = 0;
		}

		d++;
	}
}

/* MAIN */

int main() {
	Game game;
	game.GameInit();
	game.GameLoop();
	return 0;
}