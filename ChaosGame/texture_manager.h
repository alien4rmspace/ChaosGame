#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;
using namespace sf;

class TextureManager {
public:
	TextureManager() {

	}
	
	void loadTexture(const string& name, const string& filename);
	Texture& getRef(const string& texture);

private:
	map<string, Texture> textures;
};