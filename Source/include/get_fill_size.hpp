#ifndef FILLSIZE
#define FILLSIZE

SDL_Rect getFillSize(int image_w, int image_h, int back_w, int back_h) {
	SDL_Rect result;
	
	int result_w = image_w * back_h / image_h;
	int result_h = back_h;
	
	if (result_w < back_w || result_h < back_h) {
		result_w = back_w;
		result_h = image_h * back_w / image_w;
	}
	
	int result_x = (back_w - result_w) / 2;
	int result_y = (back_h - result_h) / 2;
	
	result = {result_x, result_y, result_w, result_h};
	
	return result;
}

#endif
