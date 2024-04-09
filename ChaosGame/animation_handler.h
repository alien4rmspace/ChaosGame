#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace sf;

struct Animation {
public:
	Sprite& sprite;
	IntRect rectSource;
	int moveRect;
	int lastRect;
	int resetRect;
	float animationSpeed;
};

class AnimationHandler {
public:
	AnimationHandler() {
		this->time = 0.0f;
	}
	~AnimationHandler() {
	}

	void addAnimation(const String& name, Sprite& sprite, IntRect rectSource, int moveRect, int lastRect, int resetRect, float animationSpeed);
	void update(const String& string, const float dt);

private:
	float time;
	map <String, Animation> animations;
};