#pragma once
#include "Utilities.hpp"

/* GRID CLASS */
// manage all the pixels logic

class Grid {
public:
	void InitGrid();
	void ClearGrid();
	void AddPixel(int r, int c, int pixelType);
	void FallingSand();
	void Water();

	vector<vector<int>> m_matrix;					// screen grid. 0: solid pixel, 1: falling sand pixel, 2: empty
	int m_nRows = WINDOW_WIDTH / GAME_SCALE;		// number of rows
	int m_nCols = WINDOW_HEIGHT / GAME_SCALE;		// number of columns
};