#include "animation_handler.h"

void AnimationHandler::addAnimation(const string& name, Sprite& sprite, IntRect rectSource, unsigned short int moveRect, unsigned short int lastRect, unsigned short int resetRect, const float animationSpeed) {
	sprite.setTextureRect(rectSource);
	animations.emplace(name, Animation{ sprite, rectSource, moveRect, lastRect, resetRect, animationSpeed });
}

void AnimationHandler::update(const string& name, const float dt) {
	// Using delta time to sync our animation speed with the user's computer spec.
	// Idk if it actually works, in Unity it's built into the api lol.
	Animation& animation = animations.at(name);
	animation.time += dt;
	int frame = int(animation.time / animation.animationSpeed);

	//cout << "Address of sprite without () " << &animations.at(name).sprite << endl;
	//cout << "Address of sprite with ()" << &(animations.at(name).sprite) << endl;
	//cout << "Address of sprite " << &(animations[name].sprite) << endl;

	// If animation's intRect exceeds our sprite intRect bounds (lastRect), 
	// reset the animation to the frame we want and reset the time as well.
	if (animation.rectSource.left >= animation.lastRect) {
		animation.rectSource.left = animation.resetRect; 
		animation.time = 0; // resets the clock

		animation.hasResetted = true;
	}
	else if (!animation.hasResetted){
		animation.rectSource.left = (frame * animation.moveRect);
	}
	else {
		animation.rectSource.left = animation.resetRect + (frame * animation.moveRect);
	}

	animation.sprite.setTextureRect(animation.rectSource);
}
