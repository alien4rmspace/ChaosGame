#include "game_state_editor.h"

GameStateEditor::GameStateEditor(Game* game) {
	this->game = game;

	Vector2f pos = Vector2f(this->game->window.getSize());
	this->guiView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);
}

void GameStateEditor::draw(const float dt) {
	this->game->window.clear();
	this->game->window.draw(this->game->background);
}

void GameStateEditor::update(const float dt) {

}

void GameStateEditor::handleInput() {
	Event event;

	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
			case Event::Closed: {
				this->game->window.close();
				break;
			}
			default: break;
		}
	}
}