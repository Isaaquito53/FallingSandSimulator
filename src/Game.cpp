#pragma once
#include "Game.hpp"

/* GAME METHODS */

void Game::GameInit() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("FallingSandSim", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &m_win, &m_rend);
	m_run = true;
	// set R,G,B of solid pixels
	m_solidColor = { 200, 200, 200 };
	// set R,G,B of falling sand pixels
	m_fallingColor = { 200, 160, 20 };

	// clear the grid and set solid pixels as the initial drawing tool
	m_grid.InitGrid();

	m_mouseDown = false;

	// create buttons
	Button pixelButton(0, 0, 230, 20, "Draw pixels", { { 155, 155, 155 }, { 200, 160, 20 } , {0, 100, 200} }, 3);
	m_buttons.push_back(pixelButton);
	Button erase(0, 25, 230, 20, "Erase pixels", { { 155, 155, 155 }, { 100, 100, 100 } }, 2);
	m_buttons.push_back(erase);
	Button clearGrid(0, 50, 230, 20, "Clear Grid", { { 155, 155, 155 }, { 100, 100, 100 } }, 2);
	m_buttons.push_back(clearGrid);
	Button playPause(0, 75, 230, 20, "Play/Pause", { { 100, 100, 100 }, { 155, 155, 155 } }, 2);
	m_buttons.push_back(playPause);
	Button shader(0, 100, 230, 20, "ShaderON/OFF", { { 155, 155, 155 }, { 100, 100, 100 } }, 2);
	m_buttons.push_back(shader);

	// define pixel colors
	m_solidColor = { pixelButton.m_colors[SOLID_PIXEL][0] + pixelButton.m_colors[SOLID_PIXEL][0] / 4,
					pixelButton.m_colors[SOLID_PIXEL][1] + pixelButton.m_colors[SOLID_PIXEL][1] / 4,
					pixelButton.m_colors[SOLID_PIXEL][2] + pixelButton.m_colors[SOLID_PIXEL][2] / 4 };

	m_fallingColor = { pixelButton.m_colors[FALLING_SAND_PIXEL][0] + pixelButton.m_colors[FALLING_SAND_PIXEL][0] / 4,
					pixelButton.m_colors[FALLING_SAND_PIXEL][1] + pixelButton.m_colors[FALLING_SAND_PIXEL][1] / 4,
					pixelButton.m_colors[FALLING_SAND_PIXEL][2] + pixelButton.m_colors[FALLING_SAND_PIXEL][2] / 4 };

	m_waterColor = { pixelButton.m_colors[WATER_PIXEL][0] + pixelButton.m_colors[WATER_PIXEL][0] / 4,
					pixelButton.m_colors[WATER_PIXEL][1] + pixelButton.m_colors[WATER_PIXEL][1] / 4,
					pixelButton.m_colors[WATER_PIXEL][2] + pixelButton.m_colors[WATER_PIXEL][2] / 4 };
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
			m_mouseDown = true;
			// buttons management
			for (Button& b : m_buttons) {
				b.Action(m_mouseX, m_mouseY, m_mouseDown);
			}
		}
		else if (m_e.type == SDL_EVENT_MOUSE_BUTTON_UP)
			m_mouseDown = false;
	}
}

void Game::AddPixel(float px, float py) {
	// convert screen pixels to grid pixels and add pixel to the grid
	if (m_buttons[ERASE].m_option)
		m_grid.AddPixel(px / GAME_SCALE, py / GAME_SCALE, EMPTY_PIXEL);
	else
		m_grid.AddPixel(px / GAME_SCALE, py / GAME_SCALE, m_buttons[DRAW].m_option);
}

void Game::DrawPixels() {
	// draw all the pixels of the grid (only solid/falling sand pixels)
	if (!m_buttons[SHADER].m_option) {
		SDL_SetRenderScale(m_rend, 1, 1);
		for (int r = 0; r < m_grid.m_nRows; r++) {
			for (int c = 0; c < m_grid.m_nCols; c++) {
				if (m_grid.m_matrix[r][c] != EMPTY_PIXEL) {
					if (m_grid.m_matrix[r][c] == SOLID_PIXEL)
						SDL_SetRenderDrawColor(m_rend, m_solidColor[0], m_solidColor[1], m_solidColor[2], SDL_ALPHA_OPAQUE);
					else if (m_grid.m_matrix[r][c] == FALLING_SAND_PIXEL)
						SDL_SetRenderDrawColor(m_rend, m_fallingColor[0], m_fallingColor[1], m_fallingColor[2], SDL_ALPHA_OPAQUE);
					else if (m_grid.m_matrix[r][c] == WATER_PIXEL)
						SDL_SetRenderDrawColor(m_rend, m_waterColor[0], m_waterColor[1], m_waterColor[2], SDL_ALPHA_OPAQUE);
					// convert grid pixels to screen pixels
					m_pixel.x = r * GAME_SCALE;		m_pixel.y = c * GAME_SCALE;
					m_pixel.w = GAME_SCALE;			m_pixel.h = GAME_SCALE;
					SDL_RenderFillRect(m_rend, &m_pixel);
				}
			}
		}
	}
	else {
		SDL_SetRenderScale(m_rend, 4.5, 4.5);
		for (int r = 0; r < m_grid.m_nRows; r++) {
			for (int c = 0; c < m_grid.m_nCols; c++) {
				if (m_grid.m_matrix[r][c] != EMPTY_PIXEL) {
					if (m_grid.m_matrix[r][c] == SOLID_PIXEL)
						SDL_SetRenderDrawColor(m_rend, m_solidColor[0], m_solidColor[1], m_solidColor[2], SDL_ALPHA_OPAQUE);
					else if (m_grid.m_matrix[r][c] == FALLING_SAND_PIXEL)
						SDL_SetRenderDrawColor(m_rend, m_fallingColor[0], m_fallingColor[1], m_fallingColor[2], SDL_ALPHA_OPAQUE);
					else if (m_grid.m_matrix[r][c] == WATER_PIXEL)
						SDL_SetRenderDrawColor(m_rend, m_waterColor[0], m_waterColor[1], m_waterColor[2], SDL_ALPHA_OPAQUE);
					// convert grid pixels to screen pixels
					SDL_RenderPoint(m_rend, r * 4.5, c * 4.5);
				}
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
		SDL_SetRenderDrawColor(m_rend, b.m_colors[b.m_option][0], b.m_colors[b.m_option][1], b.m_colors[b.m_option][2], SDL_ALPHA_OPAQUE);
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
		if (m_buttons[CLEAR].m_option) {
			RemoveAllPixels();
			m_buttons[CLEAR].m_option = 0;
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
		if (d >= GAME_SPEED && m_buttons[PAUSE].m_option) {
			m_grid.FallingSand();
			m_grid.Water();
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