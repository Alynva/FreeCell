#include "../include/freecell.h"

int main(int argv, char** args) {
	FreeCell freecell;
	if (freecell.init()) {
		freecell.menu();
		
		freecell.setupItens();
		
		while (!freecell.finish()) {
			freecell.update();
			if (freecell.win()) {
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Resultado", "Voce ganhou!", NULL);
				break;
			}
		}
	}

	return 0;
}
