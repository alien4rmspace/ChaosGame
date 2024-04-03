// Include important C++ libraries here
#include "StartScreen.h"
#include "MovingSprite.h"
#include "AnimatedSprite.h"


#include <sstream>
#include <vector>
#include <random>

void playBackgroundSound(Sound& backgroundSound, int delaySeconds) {
  this_thread::sleep_for(chrono::seconds(delaySeconds));
  backgroundSound.play();
}

Vector2f findTriangleCenter(Vector2f a, Vector2f b, Vector2f c) {
  float centerX = (a.x + b.x + c.x) / 3.0f;
  float centerY = (a.y + b.y + c.y) / 3.0f;

  return Vector2f(centerX, centerY);
}

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
  bool displayUserPrompt = true;
  bool howardTimerStart = false;
  bool showHoward = false;
  bool howardEntranceSongPlayed = false;
  bool xFilePlayed = false;
  bool illuminatiTriangleTimerStart = false;
  bool showIlluminatiTriangle = false;
  bool showFireworks = false;
  bool showGuests = false;

  // Create a video mode object
  VideoMode vm(1920, 1080);
  // Create and open a window for the game
  RenderWindow window(vm, "Chaos Game", Style::Default);

  vector<Vector2f> vertices;
  vector<Vector2f> points;
  Vector2f lastVertices;

  StartScreen startScreen(window);

  // Create sprites
  // 16,000 is max pixel X size
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

  Texture shootingAsteroidTexture;
  shootingAsteroidTexture.loadFromFile("Images/asteroidbelt.png");
  Sprite shootingAsteroid;
  shootingAsteroid.setTexture(shootingAsteroidTexture);

  Texture howardTheAlienTexture;
  howardTheAlienTexture.loadFromFile("Images/howard_the_alien_sprite_sheet.png");
  IntRect rectSourceHoward(0, 0, 210, 586);
  Sprite howardTheAlien(howardTheAlienTexture, rectSourceHoward);
  howardTheAlien.setScale(0.25, 0.25);
  howardTheAlien.setOrigin(105, 293);
  AnimatedSprite animatedHoward(window, howardTheAlien, 31710, 210, 21000, 1.6);

  Texture illuminatiEyeTexture;
  illuminatiEyeTexture.loadFromFile("Images/illuminati_eye.png");
  Sprite illuminatiEye{ illuminatiEyeTexture };
  illuminatiEye.setPosition((1920 / 2), (1080 / 2));
  illuminatiEye.setOrigin(288, 300);
  illuminatiEye.setScale(0.01, 0.01);

  Texture fireworkTexture;
  fireworkTexture.loadFromFile("Images/fireworks_sprite_sheet.png");
  IntRect rectSourceFireworks(0, 0, 200, 400);
  Sprite fireworks(fireworkTexture, rectSourceFireworks);
  fireworks.setScale(2, 2);
  fireworks.setOrigin(100, 200);
  Sprite fireworks_1 = fireworks;
  fireworks_1.setPosition(100, 100);
  AnimatedSprite animatedFireworks_1(window, fireworks_1, 3800, 200, 200, 0.8);
  Sprite fireworks_2 = fireworks;
  fireworks_2.setPosition(1600, 200);
  AnimatedSprite animatedFireworks_2(window, fireworks_2, 3800, 200, 200, 1.0);
  Sprite fireworks_3 = fireworks;
  fireworks_3.setPosition(600, 400);
  AnimatedSprite animatedFireworks_3(window, fireworks_3, 3800, 200, 200, 1.3);

  Texture squidwardDancingTexture;
  squidwardDancingTexture.loadFromFile("Images/squidward_dancing_sprite_sheet.png");
  IntRect rectSourceSquidward(0, 0, 200, 498);
  Sprite squidwardDancing{ squidwardDancingTexture, rectSourceSquidward };
  AnimatedSprite animatedSquidward(window, squidwardDancing, 10200, 200, 0);
  squidwardDancing.setPosition(200, 500);
  squidwardDancing.setScale(1.5, 1.5);

  Texture kidDancingTexture;
  kidDancingTexture.loadFromFile("Images/dancing_kid_sprite_sheet.png");
  IntRect rectSourceKidDancing(0, 0, 250, 270);
  Sprite kidDancing{ kidDancingTexture, rectSourceKidDancing };
  AnimatedSprite animatedKidDancing(window, kidDancing, 30500, 250, 20000, 2);
  kidDancing.setPosition(1400, 600);
  kidDancing.setScale(1.5, 1.5);
  kidDancing.setRotation(10);

  MovingSprite movingSpriteAsteroid_0(window, shootingAsteroidTexture, Vector2f(1600, 0), Vector2f(0, 1080), 1.0, 0.2);
  MovingSprite movingSpriteAsteroid_1(window, shootingAsteroidTexture, Vector2f(1240, 50), Vector2f(0, 1080), 0.63, 0.3);
  MovingSprite movingSpriteAsteroid_2(window, shootingAsteroidTexture, Vector2f(800, 100), Vector2f(0, 1080), 1.1, 0.4);
  MovingSprite movingSpriteAsteroid_3(window, shootingAsteroidTexture, Vector2f(200, 300), Vector2f(0, 1080), 0.9, 0.5);
  MovingSprite movingSpriteAsteroid_4(window, shootingAsteroidTexture, Vector2f(1600, 600), Vector2f(0, 1080), 2.0, 0.6);

  // Create sound objects
  SoundBuffer beginningSoundBuffer;
  if (!beginningSoundBuffer.loadFromFile("Sounds/meteor_woosh.wav")) {
    return -1;
  }
  Sound beginningSound{ beginningSoundBuffer };

  SoundBuffer startGeneratingSoundBuffer;
  if (!startGeneratingSoundBuffer.loadFromFile("Sounds/game_end.wav")) {
    return -1;
  }
  Sound startGeneratingSound{ startGeneratingSoundBuffer };

  SoundBuffer backgroundSoundBuffer;
  if (!backgroundSoundBuffer.loadFromFile("Sounds/space.wav")) {
    return -1;
  }
  Sound backgroundSound{ backgroundSoundBuffer };
  backgroundSound.setLoop(true);

  SoundBuffer buffer;
  if (!buffer.loadFromFile("Sounds/blaster.wav")) {
    return -1;
  }
  Sound sound{ buffer };

  SoundBuffer xFileSoundBuffer;
  if (!xFileSoundBuffer.loadFromFile("Sounds/x_files.wav")) {
    return -1;
  }
  Sound xFile{ xFileSoundBuffer };

  SoundBuffer howardEntranceSoundBuffer;
  if (!howardEntranceSoundBuffer.loadFromFile("Sounds/WHAT_DAH_HELL.wav")) {
    cout << "Something went CRITICALLY wrong" << endl;
    return -1;
  }
  Sound howardEntranceSound{ howardEntranceSoundBuffer };

  // Play intro sound and create a thread to play sounds
  beginningSound.play();

  thread backgroundSoundThread(playBackgroundSound, std::ref(backgroundSound), 9);

  thread typeWriteTitleThread(&StartScreen::TitleTypeWrite, &startScreen);
  thread typeWritePromptThread(&StartScreen::PromptTypeWrite, &startScreen);

  // Create clocks
  Clock clock; // measure delta time
  Clock illuminatiTriangleClock; // measure how long it's been to trigger illuminati triangle scenario
  Clock animationClock; // measure time for animations
  Clock haroldClock;

  // Initializing sequence for mt19937. 
  // Use in place of srand(), better rng generator.
  mt19937 mt(time(nullptr));
  uniform_int_distribution<int> dist(0, verticesAmount - 1); // this sets the range for the rng

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
            displayUserPrompt = false;

            illuminatiTriangleClock.restart(); //restarts clock to time when generation starts.
            illuminatiTriangleTimerStart = true; // starts timer when to play illuminati scenario
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
Update Illuminati Triangle Scenario
****************************************
*/

    if (illuminatiTriangleTimerStart) {
      if (illuminatiTriangleClock.getElapsedTime().asSeconds() > 5) {
        // Play song if not played yet.
        if (!xFilePlayed) {
          xFile.play();
          xFilePlayed = true;

          showIlluminatiTriangle = true; // when sound plays, show triangle.
          //Center our illuminati triangle in the center of the 3 vertices.
          Vector2f triangleCenter = findTriangleCenter(vertices[0], vertices[1], vertices[2]);
          illuminatiEye.setPosition(triangleCenter);
        }
      }
    }

    /*
****************************************
Update Harold Entrance Scenario
****************************************
*/

		if (showHoward) {
			if (!howardEntranceSongPlayed) {
				howardEntranceSound.play();
				howardEntranceSongPlayed = true;

        Vector2f howardPosition = illuminatiEye.getPosition();
        howardTheAlien.setPosition(howardPosition);
			}

      Vector2f maxScaleSize(2.5, 2.5);
      Vector2f currentScaleSize(howardTheAlien.getScale());
      float scaleSizeSpeed = 1.00377;
      float rotateSpeed = 0.589;
      if (currentScaleSize.x < maxScaleSize.x || currentScaleSize.y < maxScaleSize.y) {
        howardTheAlien.scale(scaleSizeSpeed, scaleSizeSpeed);
        howardTheAlien.rotate(rotateSpeed);

      }
      else {
        showFireworks = true;
        showGuests = true;
        showIlluminatiTriangle = false;
      }
    }



    /*
****************************************
Draw
****************************************
*/
    window.clear();

    startScreen.DisplayBackGround();
    startScreen.DisplayGameTitle();


    if (displayUserPrompt) {
      startScreen.DisplayPrompt();
      startScreen.Update(deltaTimeSeconds);
    }

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

    // Moves each asteroid sprite object across the screen and draws them
    movingSpriteAsteroid_0.Update(deltaTimeSeconds);
    movingSpriteAsteroid_1.Update(deltaTimeSeconds);
    movingSpriteAsteroid_2.Update(deltaTimeSeconds);
    movingSpriteAsteroid_3.Update(deltaTimeSeconds);
    movingSpriteAsteroid_4.Update(deltaTimeSeconds);

    if (showIlluminatiTriangle) {
      window.draw(illuminatiEye);

      Vector2f maxScaleSize(1.5, 1.5);
      Vector2f currentScaleSize(illuminatiEye.getScale());
      float scaleSizeSpeed = 1.005;
      float rotateSpeed = 0.716;
      if (currentScaleSize.x < maxScaleSize.x || currentScaleSize.y < maxScaleSize.y) {
        illuminatiEye.scale(scaleSizeSpeed, scaleSizeSpeed);
        illuminatiEye.rotate(rotateSpeed);

      }

      if (illuminatiTriangleClock.getElapsedTime().asSeconds() > 14) {
        xFile.stop();

        showHoward = true;
      }
    }

    if (showHoward) {
      animatedHoward.animate();

      // launch fireworks for Howard.
      if (showFireworks) {
        animatedFireworks_1.animate();
        animatedFireworks_2.animate();
        animatedFireworks_3.animate();
      }
      // Guests out for Howard!
      if (showGuests) {
        animatedSquidward.animate();
        animatedKidDancing.animate();
      }
    }

    window.display();
    this_thread::sleep_for(chrono::milliseconds(1));
  }

  backgroundSoundThread.join();
  typeWriteTitleThread.join();
  typeWritePromptThread.join();
  return 0;
}