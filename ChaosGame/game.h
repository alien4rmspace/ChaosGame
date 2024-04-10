#pragma once

#include <stack>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "texture_manager.h"
#include "sound_manager.h"
#include "animation_handler.h"

using namespace std;
using namespace sf;

class GameState;

class Game {
public:
	Game();
	~Game();

	stack<GameState*> states;

	RenderWindow window;
	TextureManager textureManager;
	Sprite background;
	SoundManager soundManager;
	AnimationHandler animationHandler;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

private:
	void loadTextures();
	void loadSounds();
};