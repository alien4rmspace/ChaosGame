#include <SFML/System.hpp>
#include<SFML/Audio.hpp>

#include "game.h"
#include "game_state.h"

Game::Game() {
	this->loadTextures();
	this->loadSounds();
	this->loadFonts();

	this->window.create(VideoMode(1920, 1080), "Chaos Game by Damian & Kenneth", Style::Default);
	this->window.setFramerateLimit(60);

	this->background.setTexture(this->textureManager.getRef("background"));
	this->background.setScale(3.3, 3.1);
}

Game::~Game() {
	while (!this->states.empty()) {
		popState();
	}
}

void Game::pushState(GameState* state) {
	this->states.push(state);

	return;
}

void Game::popState() {
	delete this->states.top();
	this->states.pop();

	return;
}

GameState* Game::peekState() {
	if (this->states.empty()) return nullptr;

	return this->states.top();
}

void Game::gameLoop() {
	Clock clock;

	while (this->window.isOpen()) {
		Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr) continue;
		this->window.clear();
		this->window.draw(background);

		peekState()->handleInput();
		peekState()->update(dt);
		peekState()->draw(dt);
		this->window.display();
	}
}

void Game::loadTextures() {
	textureManager.loadTexture("background", "images/background.jpg");
	textureManager.loadTexture("star", "images/star.png");
	textureManager.loadTexture("asteroid", "images/asteroid.png");
	textureManager.loadTexture("illuminatiTriangle", "images/illuminati_triangle.png");
	textureManager.loadTexture("howardTheAlien", "images/howard_the_alien_sprite_sheet.png");

	cout << "Loaded Textures into Texture Manager." << endl;
}

void Game::loadSounds() {
	soundManager.loadBuffer("game_start_sound", "sounds/game_start_sound.wav");
	soundManager.loadBuffer("background_sound", "sounds/background_sound.wav");
	soundManager.loadBuffer("star", "sounds/star_gazing.wav");
	soundManager.loadBuffer("android_notification", "sounds/android_notification.wav");
	soundManager.loadBuffer("asteroid_woosh", "sounds/asteroid_woosh.wav");
	soundManager.loadBuffer("x_files", "sounds/x_files.wav");
	soundManager.loadBuffer("WHAT_DAH_HELL", "sounds/WHAT_DAH_HELL.wav");

	cout << "Loaded Sounds into Sounds Manager." << endl;
}

void Game::loadFonts() {
	fontManager.loadFont("debug", "fonts/Debug.otf");
	fontManager.loadFont("power_smash", "fonts/Power Smash.ttf");

	cout << "Loaded Fonts into Fonts Manager." << endl;
}