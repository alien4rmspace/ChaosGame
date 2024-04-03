#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace sf;
using namespace std;

class AnimatedSprite {
private:
  Clock animationClock;
  IntRect rectSourceSprite;
  Sprite& sprite;
  RenderWindow& window;
  int lastPixelFrame;
  int movePixelFrame;
  int resetPixelFrame;
  float animationSpeed;

public:
  AnimatedSprite(RenderWindow& window, Sprite& sprite, int last, int move, int reset, float animationSpeed = 1)
    : sprite(sprite), window(window), lastPixelFrame(last), movePixelFrame(move), resetPixelFrame(reset), animationSpeed(animationSpeed){
    rectSourceSprite = sprite.getTextureRect();
  }

  void animate() {
    if (animationClock.getElapsedTime().asMilliseconds() > (100.0f / animationSpeed)) {
      if (rectSourceSprite.left >= lastPixelFrame) {
        rectSourceSprite.left = resetPixelFrame;
      }
      else {
        rectSourceSprite.left += movePixelFrame;
      }

      sprite.setTextureRect(rectSourceSprite);
      animationClock.restart();
    }
    window.draw(sprite);
  }
};