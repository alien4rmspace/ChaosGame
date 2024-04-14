#include "game_state_start.h"

#include "game_state_editor.h"

#include<thread>
#include <chrono>

GameStateStart::GameStateStart(Game* game) : mt(time(nullptr)), dist(0, kMaxVertices - 1) {
	this->game = game;

	// Set our vertex buffer primitive type
	pointsBuffer.setPrimitiveType(Quads);

	// Create our texts
	this->textManager.loadTexts("texts/game_start_texts.json", this->game->fontManager.getFontManager());

	// Assign our sprites
	this->star.setTexture(this->game->textureManager.getRef("star"));
	this->star.setOrigin(128, 128);
	this->star.setScale(0.5, 0.5);

	this->asteroid.setTexture(this->game->textureManager.getRef("asteroid"));
	this->asteroid.setOrigin(206, 206);
	this->asteroid.setScale(0.04, 0.04);

	this->illuminatiTriangle.setTexture(this->game->textureManager.getRef("illuminatiTriangle"));
	this->illuminatiTriangle.setOrigin(288, 290);
	this->illuminatiTriangle.setScale(0.1, 0.1);

	IntRect rectSourceHoward(0, 0, 106, 586);
	this->howardTheAlien.setTexture(this->game->textureManager.getRef("howardTheAlien"));
	howardTheAlien.setPosition(500, 200);
	howardTheAlien.setOrigin(53, 283);
	howardTheAlien.setScale(0.1, 0.1);

	// Adds animation to our howardTheAlien png sheet.
	// If you have any questions how the animations work you can ask me - DS	
	float howardTheAlienAnimationSpeed = 0.06;
	this->game->animationHandler.addAnimation("howardTheAlien", this->howardTheAlien, rectSourceHoward, 106, 16006, 8480, howardTheAlienAnimationSpeed);

	// Assign our rotations to each individual sprite we want to be rotated.
	int illuminatiTriangleRotationDuration = 2; // In seconds
	float illuminatiTriangleRotationSpeed = 8;
	this->game->rotationHandler.addRotation("illuminatiTriangle", this->illuminatiTriangle, illuminatiTriangleRotationDuration, illuminatiTriangleRotationSpeed);
	
	int howardTheAlienRotationDuration = 2;
	float howardTheAlienRotationSpeed = 25;
	this->game->rotationHandler.addRotation("howardTheAlien", this->howardTheAlien, howardTheAlienRotationDuration, howardTheAlienRotationSpeed);

	// Assign our sounds
	this->star_sound.setBuffer((this->game->soundManager.getBuffer("star")));
	this->android_sound.setBuffer((this->game->soundManager.getBuffer("android_notification")));
	this->x_files_sound.setBuffer((this->game->soundManager.getBuffer("x_files")));
	this->WHAT_DAH_HELL_sound.setBuffer((this->game->soundManager.getBuffer("WHAT_DAH_HELL")));
}

void GameStateStart::draw(const float dt) {
	// Draw background
	this->game->window.clear();
	this->game->window.draw(this->game->background);

	// Draw our texts
	this->game->window.draw(textManager.getText("title"));
	this->game->window.draw(textManager.getText("user_instructions"));

	// Draw our triangle vertices
	for (const auto& vertex : this->vertices) {
		star.setPosition(vertex);
		this->game->window.draw(star);
	}

	// Draw our points
	//for (const auto& point : this->points) {
	//	asteroid.setPosition(point);
	//	this->game->window.draw(asteroid);
	//}

	// Draw our sprites
	this->game->window.draw(pointsBuffer, asteroid.getTexture()); // draws vertexBuffer

	if (showIlluminatiTriangle) {
		this->game->window.draw(illuminatiTriangle);
	}

	if (showHowardTheAlien) {
		this->game->window.draw(howardTheAlien);
	}
}

void GameStateStart::update(const float dt) {
	// Our points generator
	if (this->points.size() > 0) {
		generatePoint(kPointsToGenerate);
		pointsBuffer.create(pointsVertex.size());
		pointsBuffer.update(pointsVertex.data());
	}

	if (startTimer) {
		timer += dt;
	}

	// Check if illuminati triangle is not showing, and if timer exceeds set time to show sprite.
	unsigned short int secondsUntilShow = 4;
	if ((!showIlluminatiTriangle) && (timer > secondsUntilShow)) {
		illuminatiTriangle.setPosition(calculateTriangleCenter());
		showIlluminatiTriangle = true;

		if (!playedXFiles) {
			x_files_sound.play();
			playedXFiles = true;
		}
	}

	if (showIlluminatiTriangle) {
		this->game->rotationHandler.update("illuminatiTriangle", dt);

		if (illuminatiTriangle.getScale().x < 1.5) {
			float illuminatiTriangleScaleSpeed = 1.03;
			illuminatiTriangle.scale(Vector2f(illuminatiTriangleScaleSpeed, illuminatiTriangleScaleSpeed));
		}
		else {
			this->game->rotationHandler.stopRotation("illuminatiTriangle");
		}
	}

	// Same thing similar to our illuminati triangle.
	secondsUntilShow = 10;
	if ((!showHowardTheAlien) && (timer > secondsUntilShow)) {
		howardTheAlien.setPosition(calculateTriangleCenter());
		showHowardTheAlien = true;

		if (!playedWHATDAHHELL) {
			WHAT_DAH_HELL_sound.play();
			x_files_sound.stop();
			playedWHATDAHHELL = true;
		}
	}
	
	// While Howard is out and about, we update the IntRect with the animationHandler.
	if (showHowardTheAlien) {
		this->game->animationHandler.update("howardTheAlien", dt);
		this->game->rotationHandler.update("howardTheAlien", dt);

		if (howardTheAlien.getScale().x < 5) {
			float howardTheAlienScaleSpeed = 1.03;
			howardTheAlien.scale(howardTheAlienScaleSpeed, howardTheAlienScaleSpeed);
		}
		else {
			this->game->rotationHandler.stopRotation("howardTheAlien");
			showIlluminatiTriangle = false;
		}
	}
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
				// Spaceholder if we plan to add more screens.
				if (event.key.code == Keyboard::Space) {
					cout << "loaded" << endl;
					break;
				}
			case Event::MouseButtonPressed: {
				if (event.mouseButton.button == Mouse::Left) {
					cout << "Left mouse button was pressed" << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;

					// If our vector has less than 3 vertices, continue selecting vertices.
					if (this->vertices.size() < this->kMaxVertices) {
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

// Randomly picks a vertice inside our vector that the user selected.
// Which then finds the half point of the point and the selected vertice to 
// insert another point into the points vector.
void GameStateStart::generatePoint(unsigned short int amount) {
	for (unsigned short i = 0; i < amount; i++)
	{
		vertex = selectRandomVertice();

		Vector2f lastPoint = points.back();

		float x = (this->vertex.x + lastPoint.x) / 2.f;
		float y = (this->vertex.y + lastPoint.y) / 2.f;

		this->points.push_back(Vector2(x, y));

		// Create a quad with four vertices
		for (unsigned short j = 0; j < 4; j++) {
			Vertex asteroidVertex;
			asteroidVertex.color = Color::White;

			// Adjust position for each vertex of the quad
			float asteroidSpriteScale = 20;
			switch (j) {
				case 0:
					asteroidVertex.position = Vector2(x, y);
					asteroidVertex.texCoords = Vector2f(0, 0);
					break;
				case 1:
					asteroidVertex.position = Vector2(x + asteroidSpriteScale, y);
					asteroidVertex.texCoords = Vector2f(512, 0);
					break;
				case 2:
					asteroidVertex.position = Vector2(x + asteroidSpriteScale, y + asteroidSpriteScale);
					asteroidVertex.texCoords = Vector2f(512, 512);
					break;
				case 3:
					asteroidVertex.position = Vector2(x, y + asteroidSpriteScale);
					asteroidVertex.texCoords = Vector2f(512, 0);
					break;
			}

			pointsVertex.push_back(asteroidVertex);
		}
	}
}

// Calculated the center of our triangle. I'm using this as the position reference
// when spawning in certain sprites.
Vector2f GameStateStart::calculateTriangleCenter() {
	float centerX = (this->vertices[0].x + this->vertices[1].x + this->vertices[2].x) / 3.0f;
	float centerY = (this->vertices[0].y + this->vertices[1].y + this->vertices[2].y) / 3.0f;

	return Vector2f(centerX, centerY);
}
