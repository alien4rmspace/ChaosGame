#pragma once
#include "game_state.h"

// Inherits from our abstract class which serves as an interface.
// Override is not needed here since we're not overriding any functions
// as our abstract class uses pure virtual functions. 
// If any questions about abstract classes or virtual/pure virtual functions
// feel free to ask me, I can go more into deph - DS
class GameStateEditor : public GameState {
public:
	GameStateEditor(Game* game);

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

private:
	View gameView;
	View guiView;
};
