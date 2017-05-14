#include "../include/freecell.h"

int main(int argv, char** args) {
	FreeCell freecell;
	if (freecell.init()) {
		freecell.setupItens();
		
		while (!freecell.finish()) {
			freecell.update();
		}
	}

	return 0;
}
