#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace sf;
using namespace std;

class MovingSprite {
public:
	MovingSprite(RenderWindow& window, Texture& texture, Vector2f position, Vector2f endPosition, float moveSpeed = 1, float scale = 1.0f);
	void Update(float deltatime);

private:
	float moveSpeed;
	float scale;
	RenderWindow& window;
	Texture& texture;
	Sprite* sprite;
	Vector2f position;
	Vector2f endPosition;
};