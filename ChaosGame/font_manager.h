#pragma once

#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <unordered_map>

using namespace std;
using namespace sf;

class FontManager
{
public:
	FontManager() {
		cout << "Font Manager loaded successfully" << endl;
	}
	~FontManager() {

	}

	void loadFont(const string& name, const string& fontFileName);
  Font& getFont(const string& name);
  FontManager& getFontManager();
	const unordered_map<string, Font>& getFonts();

	// Used to debug.
	void listFonts();

private:
	unordered_map<string, Font> fonts;
};

