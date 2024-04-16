#pragma once

#include <stack>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "texture_manager.h"
#include "sound_manager.h"
#include "animation_handler.h"
#include "rotation_handler.h"
#include "font_manager.h"
#include "text_manager.h"
#include "animation_handler.h"
#include "text_manager.h"
#include "typewriter.h"
#include "sprite_manager.h"

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
	FontManager fontManager;
	AnimationHandler animationHandler;
	RotationHandler rotationHandler;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

private:
	void loadTextures();
	void loadSounds();
	void loadFonts();
};