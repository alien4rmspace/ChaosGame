#pragma once

#include <SFML/Graphics.hpp>
#include<unordered_map>
#include<iostream>

using namespace std;
using namespace sf;

struct Rotation {
public:
	Sprite& sprite;
	float rotationDuration;
	int rotationSpeed;
	float time = 0;
	bool doneRotating = false;

	Rotation() = default;
	Rotation(Sprite& sprite, int rotationDuration, int rotationSpeed)
		: sprite(sprite), rotationDuration(rotationDuration), rotationSpeed(rotationSpeed) {}
};

class RotationHandler {
public:
	RotationHandler() {};
	~RotationHandler() {};

	void addRotation(const string& name, Sprite& sprite, float rotationDuration, int rotationSpeed);
	void stopRotation(const string& name);
	void update(const string& name, float dt);
private:
	unordered_map<string, Rotation> rotations;
};