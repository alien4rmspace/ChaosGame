#pragma once

#include<random>
#include<ctime>

#include "game_state.h"

// Inherits from our abstract class which serves as an interface.
// Override is not needed here since we're not overriding any functions
// as our abstract class uses pure virtual functions. 
// If any questions about abstract classes or virtual/pure virtual functions
// feel free to ask me, I can go more into deph - DS
class GameStateStart : public GameState {
public:
	GameStateStart(Game* game);

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	void selectVertice(unsigned short int x, unsigned short int y);
	Vector2f selectRandomVertice();
	void generatePoint(unsigned short int amount);
	Vector2f calculateTriangleCenter();
	Vector2f textPosition;

private:
	const int kMaxVertices = 3;
	const int kPointsToGenerate = 4;
	float timer = 0;
	float titleDropAmount = 1;
	float titleDropCounter = 0;
	float titleBounceTo = 0;

	bool startTimer = false;
	bool showTitle = true;
	bool showUserInstructions = true;
	bool showIlluminatiTriangle = false;
	bool showHowardTheAlien = false;
	bool playedXFiles = false;
	bool playedWHATDAHHELL = false;
	bool bounce = false;

	// This is our rng generator, gives better rng than what we learned in class.
// If any questions feel free to ask me - DS
	mt19937 mt;
	uniform_int_distribution<int> dist;

	Vector2f vertex;
	vector<Vector2f> vertices;
	vector<Vector2f> points;
	vector<Vertex> pointsVertex;

	VertexBuffer pointsBuffer;

	Sprite star;
	Sprite asteroid;
	Sprite illuminatiTriangle;
	Sprite howardTheAlien;

	Sound game_start_sound;
	Sound background_sound;
	Sound star_sound;
	Sound android_sound;
	Sound x_files_sound;
	Sound WHAT_DAH_HELL_sound;

	TextManager textManager;
	SpriteManager spriteManager;

	TypeWriter typeWriter;
};