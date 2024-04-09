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

	float time = 0;
};

class AnimationHandler {
public:
	AnimationHandler() {
	}
	~AnimationHandler() {
	}

	void addAnimation(const String& name, Sprite& sprite, IntRect rectSource, unsigned short int moveRect, unsigned short int lastRect, unsigned short int resetRect, const float animationSpeed);
	void update(const String& string, const float dt);

private:
	map <String, Animation> animations;
};