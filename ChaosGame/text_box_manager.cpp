#include "text_box_manager.h"

void TextBoxManager::addText(const string& name, const string& string, const Font& font) {
	Text text("hi", font);
	texts.emplace(name, Text(text));
}
const Text& TextBoxManager::getText(const string& name) {
	return texts.at(name);
}