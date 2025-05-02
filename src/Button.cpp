#pragma once
#include "Button.hpp"

/* BUTTON METHODS */

Button::Button(float x, float y, float w, float h, string text, vector<int> color) {
	m_actionArea.x = x;		m_actionArea.y = y;
	m_actionArea.w = w;		m_actionArea.h = h;
	m_text = text;			m_id = "ID_" + text;
	m_color = color;
}

void Button::Action(float mouseX, float mouseY, int &option, bool& mouseDown) {
	if (m_actionArea.x <= mouseX && m_actionArea.x + m_actionArea.w >= mouseX) {
		if (m_actionArea.y <= mouseY && m_actionArea.y + m_actionArea.h >= mouseY) {
				option = !option;
				mouseDown = false;
				if (option)
					m_color = { 100, 100, 100 };
				else
					m_color = { 155, 155, 155 };
		}
	}
}