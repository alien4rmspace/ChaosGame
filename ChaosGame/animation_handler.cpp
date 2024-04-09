#include "animation_handler.h"

#include "animation_handler.h"

void AnimationHandler::addAnimation(const String& name, Sprite& sprite, IntRect rectSource, int moveRect, int lastRect, int resetRect, float animationSpeed) {
	sprite.setTextureRect(rectSource);
	animations.emplace(name, Animation{ sprite, rectSource, moveRect, lastRect, resetRect, animationSpeed });
}

void AnimationHandler::update(const String& string, const float dt) {
	//if (int((time + dt) / duration) > int(time / duration)) {
	//	// Calculate the frame number
	//	int frame = int((time + dt) / duration);

	//	frame %= this->animations[currentAnimation].getLength();
	//}

	Animation& animation = animations.at(string);
	if (animation.rectSource.left >= animation.lastRect) {
		animation.rectSource.left = animation.resetRect;
	}
	else {
		animation.rectSource.left += animation.moveRect;
	}
	animation.sprite.setTextureRect(animation.rectSource);
}
