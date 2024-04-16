#include "rotation_handler.h"

void RotationHandler::addRotation(const string& name, Sprite& sprite, float rotationDuration, int rotationSpeed) {
	this->rotations.emplace(name, Rotation(sprite, rotationDuration, rotationSpeed));
}

void RotationHandler::stopRotation(const string& name) {
	Rotation& rotation = rotations.at(name);
	rotation.doneRotating = true;
}

void RotationHandler::update(const string& name, float dt) {
	Rotation& rotation = rotations.at(name);

	if (!rotation.doneRotating)
	{
		rotation.time += dt;

		// Check if time is less than rotationDuration we set
		if (rotation.time < rotation.rotationDuration) {
			rotation.sprite.rotate(1 * rotation.rotationSpeed);
		}
		else {
			rotation.doneRotating = true;
		}
	}
	else {
		rotation.sprite.setRotation(0); // Resets sprite to original orientation.
	}
}