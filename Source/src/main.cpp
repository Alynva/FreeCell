#include "../include/freecell.h"
#include "../include/musica.h"

int main(int argv, char** args) {
	Musica back_music;
	back_music.init();
//	back_music.setVolume(5);
	back_music.play();
	
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
