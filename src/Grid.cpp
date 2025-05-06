#pragma once
#include "Grid.hpp"

/* GRID METHODS */

// set all the grid to 0 (air/no pixel)
void Grid::InitGrid() {
	for (int i = 0; i < m_nRows; i++) {
		vector<int> line;
		for (int j = 0; j < m_nCols; j++) {
			line.push_back(EMPTY_PIXEL);
		}
		m_matrix.push_back(line);
	}
}

void Grid::ClearGrid() {
	for (int i = 0; i < m_nRows; i++) {
		for (int j = 0; j < m_nCols; j++) {
			m_matrix[i][j] = EMPTY_PIXEL;
		}
	}
}

// set the pixel in position r,c as a solid or falling sand pixel
void Grid::AddPixel(int r, int c, int pixelType) {
	if (r < m_nRows && c < m_nCols && r >= 0 && c >= 0 && (m_matrix[r][c] == EMPTY_PIXEL || pixelType == EMPTY_PIXEL))
		m_matrix[r][c] = pixelType;
}

// a row/column in the matrix represents a column/row in SDL window
// manage the falling sand 
void Grid::FallingSand() {
	for (int r = m_nRows - 1; r >= 0; r--) {
		for (int c = m_nCols - 1; c >= 0; c--) {
			if (c + 1 < m_nCols && m_matrix[r][c + 1] == EMPTY_PIXEL) {
				if (m_matrix[r][c] == FALLING_SAND_PIXEL) {
					m_matrix[r][c] = EMPTY_PIXEL;
					m_matrix[r][c+1] = FALLING_SAND_PIXEL;
				}
			}
			if (c - 1 >= 0 && m_matrix[r][c-1] != EMPTY_PIXEL) {
				if (r + 1 < m_nRows && m_matrix[r + 1][c] == EMPTY_PIXEL) {
					if (m_matrix[r][c] == FALLING_SAND_PIXEL) {
						m_matrix[r][c] = EMPTY_PIXEL;
						m_matrix[r+1][c] = FALLING_SAND_PIXEL;
					}
				}
				else if (r - 1 >= 0 && m_matrix[r - 1][c] == EMPTY_PIXEL) {
					if (m_matrix[r][c] == FALLING_SAND_PIXEL) {
						m_matrix[r][c] = EMPTY_PIXEL;
						m_matrix[r - 1][c] = FALLING_SAND_PIXEL;
					}
				}
			}
		}
	}
}
// manage the water
void Grid::Water() {
	int randomFlow = 0;
	for (int r = m_nRows - 1; r >= 0; r--) {
		for (int c = m_nCols - 1; c >= 0; c--) {
			if (c + 1 < m_nCols && m_matrix[r][c + 1] == EMPTY_PIXEL) {
				if (m_matrix[r][c] == WATER_PIXEL) {
					m_matrix[r][c] = EMPTY_PIXEL;
					m_matrix[r][c + 1] = WATER_PIXEL;
				}
			}
			if (c - 1 >= 0 && m_matrix[r][c - 1] == WATER_PIXEL) {
				if (r + 1 < m_nRows && m_matrix[r + 1][c] == EMPTY_PIXEL) {
					if (m_matrix[r][c] == WATER_PIXEL) {
						m_matrix[r][c] = EMPTY_PIXEL;
						m_matrix[r + 1][c] = WATER_PIXEL;
					}
				}
				else if (r - 1 >= 0 && m_matrix[r - 1][c] == EMPTY_PIXEL) {
					if (m_matrix[r][c] == WATER_PIXEL) {
						m_matrix[r][c] = EMPTY_PIXEL;
						m_matrix[r - 1][c] = WATER_PIXEL;
					}
				}
			}
			if (c + 1 < m_nCols && m_matrix[r][c + 1] != EMPTY_PIXEL) {
				randomFlow = rand() % 2;
				if (randomFlow && r + 1 < m_nRows && m_matrix[r + 1][c] == EMPTY_PIXEL) {
					if (m_matrix[r][c] == WATER_PIXEL) {
						m_matrix[r][c] = EMPTY_PIXEL;
						m_matrix[r + 1][c] = WATER_PIXEL;
					}
				}
				else if (r - 1 >= 0 && m_matrix[r - 1][c] == EMPTY_PIXEL) {
					if (m_matrix[r][c] == WATER_PIXEL) {
						m_matrix[r][c] = EMPTY_PIXEL;
						m_matrix[r - 1][c] = WATER_PIXEL;
					}
				}
			}
		}
	}
}