#include <iostream>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TypeWriter {
public:
  TypeWriter(unsigned short int typeSpeed = 100)
    : typeSpeed(typeSpeed) {
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
    return;
  }

  ~TypeWriter() {
  }

private:
  unsigned short int typeSpeed;
};
