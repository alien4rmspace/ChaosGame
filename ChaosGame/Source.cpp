// Include important C++ libraries here
#include "StartScreen.h"
#include "MovingSprite.h"


#include <sstream>
#include <vector>

#include <random>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
  /*
****************************************
Settings
****************************************
*/

  int verticesAmount = 3;

  
  // Create a video mode object
  VideoMode vm(1920, 1080);
  // Create and open a window for the game
  RenderWindow window(vm, "Chaos Game", Style::Default);

  vector<Vector2f> vertices;
  vector<Vector2f> points;
  Vector2f lastVertices;

  StartScreen startScreen(window);

  // Create sprites
  Texture asteroidTexture;
  asteroidTexture.loadFromFile("Images/asteroid.png");
  Sprite asteroid;
  asteroid.setTexture(asteroidTexture);
  asteroid.setScale(0.02, 0.02);

  Texture starsTexture;
  starsTexture.loadFromFile("Images/star.png");
  Sprite stars;
  stars.setTexture(starsTexture);
  stars.setScale(0.2, 0.2);

  Texture asteroidBeltTexture;
  asteroidBeltTexture.loadFromFile("Images/asteroidbelt.png");
  Sprite asteroidBelt;
  asteroidBelt.setTexture(asteroidBeltTexture);
  asteroidBelt.setScale(0.4, 0.4);

  MovingSprite movingSpriteAsteroid_0(window, asteroidBeltTexture, Vector2f(1600, 0), Vector2f(0, 1080), 1.0, 0.2);
  MovingSprite movingSpriteAsteroid_1(window, asteroidBeltTexture, Vector2f(1240, 50), Vector2f(0, 1080), 1.3, 0.3);
  MovingSprite movingSpriteAsteroid_2(window, asteroidBeltTexture, Vector2f(800, 100), Vector2f(0, 1080), 1.1, 0.4);
  MovingSprite movingSpriteAsteroid_3(window, asteroidBeltTexture, Vector2f(200, 300), Vector2f(0, 1080), 0.9, 0.5);
  MovingSprite movingSpriteAsteroid_4(window, asteroidBeltTexture, Vector2f(1600, 600), Vector2f(0, 1080), 2.0, 0.6);

  // Create sound objects
  SoundBuffer beginningSoundBuffer;
  if (!beginningSoundBuffer.loadFromFile("Sounds/gameBegin.wav")) {
    return -1;
  }
  Sound beginningSound;
  beginningSound.setBuffer(beginningSoundBuffer);

  SoundBuffer startGeneratingSoundBuffer;
  if (!startGeneratingSoundBuffer.loadFromFile("Sounds/gameEnd.wav")) {
    return -1;
  }
  Sound startGeneratingSound;
  startGeneratingSound.setBuffer(startGeneratingSoundBuffer);

  SoundBuffer backgroundSoundBuffer;
  if (!backgroundSoundBuffer.loadFromFile("Sounds/space.wav")) {
    return -1;
  }
  Sound backgroundSound;
  backgroundSound.setBuffer(backgroundSoundBuffer);
  backgroundSound.setLoop(true);

  SoundBuffer buffer;
  if (!buffer.loadFromFile("Sounds/blaster.wav")) {
    return -1;
  }
  Sound sound;
  sound.setBuffer(buffer);

  // Play intro sound and create a thread to play sounds
  beginningSound.play();

  auto playBackgroundSound = [&]() {
    this_thread::sleep_for(std::chrono::seconds(6));
    backgroundSound.play();
  };
  thread backgroundSoundThread(playBackgroundSound); // thread is needed to work with sleep

  thread typeWriteTitleThread(&StartScreen::TitleTypeWrite, &startScreen);
  thread typeWritePromptThread(&StartScreen::PromptTypeWrite, &startScreen);

  // Initializing sequence for mt19937. 
  // Use in place of srand(), better rng generator.
  mt19937 mt(time(nullptr));
  uniform_int_distribution<int> dist(0, verticesAmount - 1); // this sets the range for the rng

  // Create a clock for delta time.
  // We use delta time instead of the framerate of the program 
  // because results can vary relying on the framerate.
  Clock clock;

  while (window.isOpen())
  {
    /*
****************************************
Handle the players input
****************************************
*/
    Event event;
    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed)
      {
        // Quit the game when the window is closed
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed)
      {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
          std::cout << "the left button was pressed" << std::endl;
          std::cout << "mouse x: " << event.mouseButton.x << std::endl;
          std::cout << "mouse y: " << event.mouseButton.y << std::endl;

          if (vertices.size() < verticesAmount)
          {
            sound.play();
            vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
          }
          else if (points.size() == 0)
          {
            ///fourth click
            ///push back to points vector
            points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
            startGeneratingSound.play();
          }
        }
      }
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }
    /*
****************************************
Update
****************************************
*/
    Time deltaTime = clock.restart(); // restart() resets the clock and returns time elapsed
    float deltaTimeSeconds = deltaTime.asSeconds();

    if (points.size() > 0)
    {
      ///generate more point(s)
      ///select random vertex
      ///calculate midpoint between random vertex and the last point in the vector
      ///push back the newly generated coord.
      Vector2f randomVertex = vertices[dist(mt)]; // dist(mt) uses the range we set above.
      
      if (verticesAmount == 4) {
        while (randomVertex == lastVertices) {
          randomVertex = vertices[dist(mt)];
        }
        lastVertices = randomVertex;
      }

      Vector2f lastPoint = points[points.size() - 1];
      
      float x = (randomVertex.x + lastPoint.x) / 2.f;
      float y = (randomVertex.y + lastPoint.y) / 2.f;

      Vector2f newPoint(x, y);
      points.push_back(newPoint);
    }

    /*
****************************************
Draw
****************************************
*/
    window.clear();

    startScreen.DisplayBackGround();

    movingSpriteAsteroid_0.Update(deltaTimeSeconds);
    movingSpriteAsteroid_1.Update(deltaTimeSeconds);
    movingSpriteAsteroid_2.Update(deltaTimeSeconds);
    movingSpriteAsteroid_3.Update(deltaTimeSeconds);
    movingSpriteAsteroid_4.Update(deltaTimeSeconds);

    startScreen.DisplayGameTitle();
    startScreen.DisplayPrompt();
    startScreen.Update(deltaTimeSeconds);
    
    for (int i = 0; i < vertices.size(); i++)
    {
      int centeringAdjustment = 25;
      stars.setPosition(Vector2f(vertices[i].x - centeringAdjustment, vertices[i].y - centeringAdjustment));
      window.draw(stars);
    }

    for (int i = 0; i < points.size(); i++) {
      asteroid.setPosition(points[i]);
      window.draw(asteroid);
    }


    window.display();
  }

  backgroundSoundThread.join();
  typeWriteTitleThread.join();
  typeWritePromptThread.join();
  return 0;
}