#ifndef FILLSIZE
#define FILLSIZE

SDL_Rect getFillSize(int image_w, int image_h, int back_w, int back_h) {
	SDL_Rect result;
	
	int image_ratio = image_w / image_h;
	int back_ratio = image_w / image_h;
	
	int result_w = back_ratio < image_ratio ? image_w * back_h / image_h : back_w;
	int result_h = back_ratio < image_ratio ? back_h : image_h * back_w / image_w;
	
	int result_x = (back_w - result_w) / 2;
	int result_y = (back_h - result_h) / 2;
	
	result = {result_x, result_y, result_w, result_h};
	
	return result;
}

#endif
