#include "../include/FreeCell.h"

int main(int argv, char** args) {
	
	FreeCell freecell;
	if (freecell.init()) {
		freecell.menu();
		
		if (!freecell.finish()) {
			do {
				freecell.setupItens();
				
				while (!freecell.finish()) {
					freecell.update();
					if (freecell.win());
				}
				
				freecell.playAgain();
			} while (!freecell.finish());
		}
	}

	return 0;
}