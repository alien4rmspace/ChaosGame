#pragma once

#include<vector>

#include "game.h"


// This is an interface.
// Interfaces weren't talked about in class let me know if
// you have any questions about how they work. - DS
class GameState {
public:
	Game* game;
	AnimationHandler animationHandler;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;
};