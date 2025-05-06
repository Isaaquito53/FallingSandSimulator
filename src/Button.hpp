#pragma once
#include "Utilities.hpp"

/* BUTTON CLASS */
// button to draw falling sand/solid pixel, clear grid...

class Button {
public:
	Button(float x, float y, float w, float h, string text, vector<vector<int>> colors, int maxStates);
	void Action(float mouseX, float mouseY, bool& mouseDown);

	SDL_FRect m_actionArea;				// where you can click the button
	string m_text;						// the text that it will be displayed
	string m_id;						// id to identificate the action
	vector<vector<int>> m_colors;		// button background color
	int m_option;						// option that manages this button
	int m_maxStates;					// the max amount of states that manages this button
};