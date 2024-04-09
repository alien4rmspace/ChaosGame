#include "animation_handler.h"

#include "animation_handler.h"

void AnimationHandler::addAnimation(const String& name, Sprite& sprite, IntRect rectSource, unsigned short int moveRect, unsigned short int lastRect, unsigned short int resetRect, const float animationSpeed) {
	sprite.setTextureRect(rectSource);
	animations.emplace(name, Animation{ sprite, rectSource, moveRect, lastRect, resetRect, animationSpeed });
}

void AnimationHandler::update(const String& string, const float dt) {
	Animation& animation = animations.at(string);
	animation.time += dt;
	int frame = int(animation.time / animation.animationSpeed);

	if (animation.rectSource.left >= animation.lastRect) {
		animation.rectSource.left = animation.resetRect;
		animation.time = 0; // resets the clock
	}
	else {
		animation.rectSource.left = animation.resetRect + (frame * animation.moveRect);
	}
	animation.sprite.setTextureRect(animation.rectSource);
}
