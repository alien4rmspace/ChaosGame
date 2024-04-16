#include "font_manager.h"

void FontManager::loadFont(const string& name, const string& fontFileName) {
	Font font;
	if (!font.loadFromFile(fontFileName)) {
		cout << "Font Manager could not load " << fontFileName << endl;
	}
	this->fonts.emplace(name, font);
}
Font& FontManager::getFont(const string& name) {
	return this->fonts.at(name);
}

FontManager& FontManager::getFontManager() {
	return *this;
}

void FontManager::listFonts() {
	for (const auto& map : fonts) {
		cout << map.first << endl;
	}
}