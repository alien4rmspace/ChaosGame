#pragma once

#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <unordered_map>

using namespace std;
using namespace sf;

class TextBoxManager
{
public:
	TextBoxManager() {};
	~TextBoxManager() {};

	void addText(const string& name, const string& text, const Font& font);
	const Text& getText(const string& name);

private:
	unordered_map<string, Text> texts;
};

