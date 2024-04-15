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

  void startTyping(Text& text) {
    string stringBuffer = "";
    string typeThis = text.getString();
    text.setString("");
    for (const char ch : typeThis) {
      stringBuffer += ch;
      text.setString(stringBuffer);

      this_thread::sleep_for(chrono::milliseconds(typeSpeed));
    }


    for (int i = 0; i <= 10; ++i) {
      Color color(this->dist(mt), this->dist(mt), this->dist(mt));
      text.setFillColor(color);

      this_thread::sleep_for(chrono::milliseconds(100));
    }
    Color color(90, 245, 66);
    text.setFillColor(color);
    return;
  }

  ~TypeWriter() {
  }

private:
  unsigned short int typeSpeed;
  mt19937 mt;
  uniform_int_distribution<int> dist;
};
