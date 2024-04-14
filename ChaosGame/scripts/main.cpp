#include "game.h"
#include "game_state_start.h"
#include "game_state_editor.h"

int main() {
	Game game;

	game.pushState(new GameStateStart(&game));
	game.gameLoop();


	return 0;
}