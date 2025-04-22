#pragma once
#include "Utilities.hpp"

/* BUTTON CLASS */
// button to draw falling sand/solid pixel, clear grid...

class Button {
public:
	Button(float x, float y, float w, float h, string text);
	void Action(float mouseX, float mouseY, int &option);

	SDL_FRect m_actionArea;		// where you can click the button
	string m_text;				// the text that it will be displayed
	string m_id;				// id to identificate the action
};