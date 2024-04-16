#include <iostream>
#include <thread>
#include <chrono>
#include <random>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TypeWriter {
public:
  TypeWriter(unsigned short int typeSpeed = 18)
    : typeSpeed(typeSpeed), mt(time(nullptr)), dist(0, 255) {
  }

  void startTyping(Text& text);

  ~TypeWriter() {
  }

private:
  unsigned short int typeSpeed;
  mt19937 mt;
  uniform_int_distribution<int> dist;
};
