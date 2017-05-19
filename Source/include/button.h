#ifndef BUTTON
#define BUTTON

#define BUTTON_WIDTH 250
#define BUTTON_HEIGHT 50

#include <iostream>
#include "textura.h"

using namespace std;

class Button {
	string type;
	Textura tex_normal;
	Textura tex_hover;
	Textura tex_hold;
	bool state_hover;
	bool state_hold;
	
	public:
		Button(string);
		Button(string, SDL_Renderer*);
		void render();
		string getType() const;
		void setPosition(SDL_Point);
		SDL_Point getPosition() const;
		bool isInside(SDL_Point) const;
		void setStateHover(bool);
		bool getStateHover() const;
		void setStateHold(bool);
		bool getStateHold() const;
};

inline Button::Button(string type):type(type), state_hover(false), state_hold(false) {}

inline Button::Button(string type, SDL_Renderer* renderer):type(type) {
	string path_normal = "", path_hover = "", path_hold = "";
	string dir = "../textures/buttons/";
	
	path_normal.append(dir); path_normal.append(this->type); path_normal.append("_normal.png");
	path_hover.append(dir); path_hover.append(this->type); path_hover.append("_hover.png");
	path_hold.append(dir); path_hold.append(this->type); path_hold.append("_hold.png");
	
	this->tex_normal = Textura(path_normal, renderer, 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
	this->tex_hover = Textura(path_hover, renderer, 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
	this->tex_hold = Textura(path_hold, renderer, 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
}

inline string Button::getType() const {
	return this->type;
}

inline void Button::render() {
	if (!this->state_hover && !this->state_hold)
		this->tex_normal.render();
	else if (this->state_hover && !this->state_hold)
		this->tex_hover.render();
	else if (this->state_hold)
		this->tex_hold.render();
}

inline void Button::setPosition(SDL_Point pos) {
	this->tex_normal.setPosition(pos);
	this->tex_hover.setPosition(pos);
	this->tex_hold.setPosition(pos);
}

inline SDL_Point Button::getPosition() const {
	return this->tex_normal.getPosition();
}

inline bool Button::isInside(SDL_Point point) const {
//	SDL_Point size = this->tex_normal.getSize();
//	SDL_Point position = this->tex_normal.getPosition();
//
//	bool inside = 	((point.x > position.x && point.x < position.x + size.x) &&
//					 (point.y > position.y && point.y < position.y + size.y));
//
//	return inside;

return true;
}

inline void Button::setStateHover(bool state) {
	this->state_hover = state;
}
inline bool Button::getStateHover() const {
	return this->state_hover;
}

inline void Button::setStateHold(bool state) {
	this->state_hold = state;
}
inline bool Button::getStateHold() const {
	return this->state_hold;
}

#endif
