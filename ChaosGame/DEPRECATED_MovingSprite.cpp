#include "MovingSprite.h"

MovingSprite::MovingSprite(RenderWindow& window, Texture& texture, Vector2f position, Vector2f endPosition, float moveSpeed, float scale) : window(window), texture(texture), position(position), endPosition(endPosition), moveSpeed(moveSpeed), scale(scale){
	Sprite* sprite = new Sprite;
	sprite->setTexture(texture);
	sprite->setPosition(position);
	sprite->setScale((1 * scale), (1 * scale));
	this->sprite = sprite;
}
void MovingSprite::Update(float deltaTime) {
	if (!(this->position.x < 0)){
	int xDifference = this->position.x - this->endPosition.x;
	int yDifference = this->position.y - this->endPosition.y;

	float linearAcceleration = 2;
	if (xDifference < 0) {
		if (this->position.x < 0) {
			this->position.x += linearAcceleration * (this->moveSpeed * 200) * deltaTime;
		}
	}
	else {
		if (this->position.x > 0) {
			this->position.x -= linearAcceleration * (this->moveSpeed * 200) * deltaTime;
		}
	}

	if (yDifference > 0) {
		if (this->position.y > 0) {
			this->position.y -= (this->moveSpeed * 200) * deltaTime;
		}
	}
	else {
		if (this->position.y < this->endPosition.y) {
			this->position.y += (this->moveSpeed * 200) * deltaTime;
		}
	}


	this->sprite->setPosition(this->position);
	window.draw(*sprite);
	}
}
