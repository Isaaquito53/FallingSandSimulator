#pragma once
#include "Button.hpp"

/* BUTTON METHODS */

Button::Button(float x, float y, float w, float h, string text, vector<vector<int>> colors, int maxStates) {
	m_actionArea.x = x;		m_actionArea.y = y;
	m_actionArea.w = w;		m_actionArea.h = h;
	m_text = text;			m_id = "ID_" + text;
	m_colors = colors;
	m_option = 0;			m_maxStates = maxStates;
}

// calculate if we clicked inside of a button area
void Button::Action(float mouseX, float mouseY, bool& mouseDown) {
	if (m_actionArea.x <= mouseX && m_actionArea.x + m_actionArea.w >= mouseX) {
		if (m_actionArea.y <= mouseY && m_actionArea.y + m_actionArea.h >= mouseY) {
				m_option++;
				if (m_option == m_maxStates)
					m_option = 0;
				mouseDown = false;
		}
	}
}