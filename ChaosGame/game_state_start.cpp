#include "game_state_start.h"

#include "game_state_editor.h"
#include "animation_handler.h"

#include<thread>
#include <chrono>

GameStateStart::GameStateStart(Game* game) : mt(time(nullptr)), dist(0, maxVertices - 1) {
	this->game = game;

	// Assign our sprites
	this->star.setTexture(this->game->textureManager.getRef("star"));
	this->star.setOrigin(128, 128);
	this->star.setScale(0.5, 0.5);

	this->asteroid.setTexture(this->game->textureManager.getRef("asteroid"));
	this->asteroid.setOrigin(206, 206);
	this->asteroid.setScale(0.04, 0.04);

	this->illuminatiTriangle.setTexture(this->game->textureManager.getRef("illuminatiTriangle"));

	IntRect rectSourceHoward(0, 0, 106, 586);
	this->howardTheAlien.setTexture(this->game->textureManager.getRef("howardTheAlien"));
	

	animationHandler.addAnimation("howardTheAlien", this->howardTheAlien, rectSourceHoward, 106, 16006, 8480, 1.6);

	// Assign our sounds
	this->star_sound.setBuffer((this->game->soundManager.getBuffer("star")));
	this->android_sound.setBuffer((this->game->soundManager.getBuffer("android_notification")));
}

void GameStateStart::draw(const float dt) {
	this->game->window.clear();
	this->game->window.draw(this->game->background);

	// Draw our triangle vertices
	for (const auto& vertex : this->vertices) {
		star.setPosition(vertex);
		this->game->window.draw(star);
	}

	// Draw our points
	for (const auto& point : this->points) {
		asteroid.setPosition(point);
		this->game->window.draw(asteroid);
	}

	if (showIlluminatiTriangle) {
		this->game->window.draw(illuminatiTriangle);
	}

	// Draw our animations
	this->game->window.draw(howardTheAlien);
}

void GameStateStart::update(const float dt) {	
	if (this->points.size() > 0) {
		generatePoint(pointsToGenerate);
	}

	if (startTimer) {
		timer += dt;
	}
	// Check if illuminati triangle is not showing, and if timer exceeds set time until show.
	int secondsUntilShow = 4;
	if (((showIlluminatiTriangle) == false) && (timer > secondsUntilShow)) {
		showIlluminatiTriangle = true;
	}

	// Update howardTheAlien animation
	animationHandler.update("howardTheAlien", dt);
}

void GameStateStart::handleInput() {
	Event event;

	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
			case Event::Closed: {
				this->game->window.close();
				break;
			}
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape) {
					this->game->window.close();
					break;
				}
				if (event.key.code == Keyboard::Space) {
					cout << "loaded" << endl;
					this->loadgame();
					break;
				}
			case Event::MouseButtonPressed: {
				if (event.mouseButton.button == Mouse::Left) {
					cout << "Left mouse button was pressed" << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;

					// If our vector has less than 3 vertices, continue selecting vertices.
					if (this->vertices.size() < this->maxVertices) {
						star_sound.play();

						selectVertice(event.mouseButton.x, event.mouseButton.y);
					}
					else if (this->points.size() == 0) {
						android_sound.play();
						startTimer = true;

						this->points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					break;
				}
				break;
			}
			default: break;
		}
	}
}

void GameStateStart::selectVertice(unsigned short int x, unsigned short int y) {
	this->vertices.push_back(Vector2f(x, y));
}

Vector2f GameStateStart::selectRandomVertice() {
	Vector2f randomVertice = this->vertices[dist(mt)];
	return randomVertice;
}

// Finds a random vertice to pick from that is different from previously,
// then finds the half way point between that vertice and our last point to push back.
void GameStateStart::generatePoint(unsigned short int amount) {
	for (unsigned short i = 0; i < amount; i++)
	{
		vertex = selectRandomVertice();

		Vector2f lastPoint = points.back();

		float x = (this->vertex.x + lastPoint.x) / 2.f;
		float y = (this->vertex.y + lastPoint.y) / 2.f;

		this->points.push_back(Vector2(x, y));
	}
}


void GameStateStart::loadgame() {
	this->game->pushState(new GameStateEditor(this->game));
}

