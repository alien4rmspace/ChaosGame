#include "text_manager.h"

void TextManager::addText(const auto& _text, FontManager& fontManager) {
  Text text;
  string contentHolder = "";

  for (const auto& text : _text["content"]) {
    contentHolder += text;
  }

  text.setString(contentHolder);
  text.setFont(fontManager.getFont(string(_text["font"])));
  text.setPosition(_text["position"].at("x"), _text["position"].at("y"));
  text.setCharacterSize(_text["size"]);

  texts.emplace(_text["name"], text);
}

void TextManager::loadTexts(const string& textsFileName, FontManager& fontManager) {
  ifstream file(textsFileName);
  if (!file.is_open()) {
    cerr << "Error: Failed to open file " << textsFileName << endl;
    return;
  }

  // Read JSON data from file documentation on nlohmann github, it's my first time using this too
  json jsonData;
  try {
    file >> jsonData;
  }
  catch (const json::parse_error& e) {
    cerr << "Error " << textsFileName << ": " << e.what() << endl;
    return;
  }

  for (const auto& text : jsonData["texts"]) {
    addText(text, fontManager);
  }
}

Text& TextManager::getText(const string& name) {
	return texts.at(name);
}