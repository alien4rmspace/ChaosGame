#pragma once

#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <unordered_map>
#include <fstream>

#include "font_manager.h"

#include "json.hpp"

using namespace std;
using namespace sf;
using json = nlohmann::json;

class TextManager {
public:
	TextManager() {
		cout << "Text Manager loaded successfuly." << endl;
	}
	~TextManager() {

	}

	void addText(const auto& _text, FontManager& fontManager);
	void loadTexts(const string& textsFileName, FontManager& font);
	Text& getText(const string& name);

private:
	unordered_map<string, Text> texts;
};