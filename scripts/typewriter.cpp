#include "typewriter.h"

void TypeWriter::startTyping(Text& text) {
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