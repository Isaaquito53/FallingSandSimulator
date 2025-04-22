#pragma once
#include "Grid.hpp"

/* GRID METHODS */

// set all the grid to 0 (air/no pixel)
void Grid::InitGrid() {
	for (int i = 0; i < m_nRows; i++) {
		vector<int> line;
		for (int j = 0; j < m_nCols; j++) {
			line.push_back(2);
		}
		m_matrix.push_back(line);
	}
}

void Grid::ClearGrid() {
	for (int i = 0; i < m_nRows; i++) {
		for (int j = 0; j < m_nCols; j++) {
			m_matrix[i][j] = 2;
		}
	}
}

// set the pixel in position r,c as a solid or falling sand pixel
void Grid::AddPixel(int r, int c, int pixelType) {
	if (r < m_nRows && c < m_nCols && r >= 0 && c >= 0 && m_matrix[r][c] == 2)
		m_matrix[r][c] = pixelType;
}

// manage the falling sand (a row/column in the matrix represents a column/row in SDL window)
void Grid::FallingSand() {
	for (int r = m_nRows - 1; r >= 0; r--) {
		for (int c = m_nCols - 1; c >= 0; c--) {
			if (c + 1 < m_nCols && m_matrix[r][c + 1] == 2) {
				if (m_matrix[r][c] == 1) {
					m_matrix[r][c] = 2;
					m_matrix[r][c+1] = 1;
				}
			}
			if (c - 1 >= 0 && m_matrix[r][c-1] != 2) {
				if (r + 1 < m_nRows && m_matrix[r + 1][c] == 2) {
					if (m_matrix[r][c] == 1) {
						m_matrix[r][c] = 2;
						m_matrix[r+1][c] = 1;
					}
				}
				else if (r - 1 >= 0 && m_matrix[r - 1][c] == 2) {
					if (m_matrix[r][c] == 1) {
						m_matrix[r][c] = 2;
						m_matrix[r - 1][c] = 1;
					}
				}
			}
		}
	}
}