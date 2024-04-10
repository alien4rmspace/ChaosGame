#include "DEPRECATED_StartScreen.h"

StartScreen::StartScreen(RenderWindow& window) : window(window) {
  startScreenTexture.loadFromFile("Images/StartScreenBackground.jpg");
  startScreen.setTexture(startScreenTexture);
  startScreen.setPosition(0.f, 0.f);
  startScreen.setScale(3.1, 3.1);

  if (!font.loadFromFile("Fonts/Debug.otf")) {
    cout << "Oh caca, font didn't load" << endl;
  }

  gameTitle.setFont(font);
  gameTitle.setString("");
  gameTitle.setCharacterSize(100);
  gameTitle.setFillColor(Color::Red);
  gameTitle.setPosition(750, 30);

  userPrompt.setFont(font);
  userPrompt.setString("");
  userPrompt.setCharacterSize(20);
  userPrompt.setFillColor(Color::White);
  userPrompt.setPosition(100, 100);

  Vector2u windowSize = window.getSize();
  windowSizex = windowSize.x;
  windowSizey = windowSize.y;
}

void StartScreen::Update(float deltaTime) {
  Vector2f currentPosition = userPrompt.getPosition();
  Vector2f newPosition = currentPosition;

  int centerWindowPosx = windowSizex / 2 - 200;
  int centerWindowPosy = windowSizey / 2 - 100;
  if (newPosition.x <= centerWindowPosx) {
    newPosition.x = currentPosition.x + 200 * deltaTime;
  }
  if (newPosition.y <= centerWindowPosy) {
    newPosition.y = currentPosition.y + 300 * deltaTime;

  }

  userPrompt.setPosition(newPosition);
}

void StartScreen::TitleTypeWrite() {
  int milliSeconds = 100;
  String gameTitleDescription = "Chaos Game";
  String gameTitleString = "";
  for (auto ch : gameTitleDescription) {
    gameTitleString += ch;
    gameTitle.setString(gameTitleString);
    this_thread::sleep_for(std::chrono::milliseconds(milliSeconds));
  }
}

void StartScreen::PromptTypeWrite() {
  int milliSeconds = 40;
  String userPromptDescription = "Welcome wandering stranger to the CHAOS game!\n"
                                 "To play this game you will need to select 3 points\n"
                                 "on the screen to create a triangle using the left\n"
                                 "mouse button.\n"
                                 "Then you will select a 4th point to begin...\n"
                                 "\n\t\t\t\t\t\t\tTHE CHAOS";
  String gamePromptString = "";
  for (auto ch : userPromptDescription) {
    gamePromptString += ch;
    userPrompt.setString(gamePromptString);
    this_thread::sleep_for(std::chrono::milliseconds(milliSeconds));
  }
  // This sets font bold for both user prompt and game title.
  userPrompt.setStyle(Text::Bold);
  gameTitle.setStyle(Text::Bold);

  for (unsigned short i = 0; i < 30; i++) {
    if (i % 2 == 0) {
      userPrompt.setFillColor(Color::Magenta);
      gameTitle.setFillColor(Color::Green);
    }
    else {
      userPrompt.setFillColor(Color::Green);
      gameTitle.setFillColor(Color::Magenta);
    }
    this_thread::sleep_for(std::chrono::milliseconds(milliSeconds));
  }
}

void StartScreen::DisplayBackGround() {
  window.draw(startScreen);
}

void StartScreen::DisplayGameTitle() {
  window.draw(gameTitle);
}

void StartScreen::DisplayPrompt() {
  window.draw(userPrompt);
}
