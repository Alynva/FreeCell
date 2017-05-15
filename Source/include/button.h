#ifndef BUTTON
#define BUTTON

class Button {
	Textura tex_normal;
	Textura tex_hover;
	Textura tex_hold;
	bool state_hover;
	bool state_hold;
	
	public:
		Button();
		Button(SDL_Renderer*);
		void setPosition(SDL_Point);
		SDL_Point getPosition() const;
		bool isInside(SDL_Point) const;
		void setStateHover(bool);
		void setStateHold(bool);
};

Button::Button();

#endif
