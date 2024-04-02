#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;
using namespace sf;

class StartScreen {
public:
  StartScreen(RenderWindow& window);
  void Update(float deltaTime);
  void TitleTypeWrite();
  void PromptTypeWrite();
  void DisplayBackGround();
  void DisplayGameTitle();
  void DisplayPrompt();
private:
  Vector2f targetPosition;
  RenderWindow& window;
  int windowSizex;
  int windowSizey;
  Texture startScreenTexture;
  Sprite startScreen;
  Font font;
  Text gameTitle;
  Text userPrompt;
};
