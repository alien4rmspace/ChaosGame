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

private:
	int maxVertices = 3;
	int pointsToGenerate = 2;
	float timer;
	mt19937 mt;
	uniform_int_distribution<int> dist;

	bool startTimer = false;
	bool showIlluminatiTriangle = false;


	Vector2f vertex;
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	Sprite star;
	Sprite asteroid;
	Sprite illuminatiTriangle;
	Sprite howardTheAlien;

	AnimationHandler howardTheAlienAH;

	Sound star_sound;
	Sound android_sound;

	void loadgame();
};