#include "../include/freecell.h"

int main(int argv, char** args) {
	FreeCell freecell;
	if (freecell.init()) {
		freecell.setupItens();
		
		while (!freecell.finish()) {
			freecell.update();
			if (freecell.win()) {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Resultado", "Você ganhou!", NULL);
				break;
			}
		}
	}

	return 0;
}
