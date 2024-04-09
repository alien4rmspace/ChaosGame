#pragma once

#include<random>
#include<ctime>

#include "game_state.h"

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

private:
	const int kMaxVertices = 3;
	const int kPointsToGenerate = 2;
	float timer = 0;

	// This is our rng generator, gives better rng than what we learned in class.
	// If any questions feel free to ask me - DS
	mt19937 mt;
	uniform_int_distribution<int> dist;

	bool startTimer = false;
	bool showIlluminatiTriangle = false;
	bool showHowardTheAlien = false;
	bool playedXFiles = false;
	bool playedWHATDAHHELL = false;

	Vector2f vertex;
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	Sprite star;
	Sprite asteroid;
	Sprite illuminatiTriangle;
	Sprite howardTheAlien;

	Sound star_sound;
	Sound android_sound;
	Sound x_files_sound;
	Sound WHAT_DAH_HELL_sound;
};