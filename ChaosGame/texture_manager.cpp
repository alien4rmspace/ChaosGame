#include "texture_manager.h"

void TextureManager::loadTexture(const string& name, const string& filename) {
	Texture tex;
	tex.loadFromFile(filename);

	this->textures[name] = tex;
}

Texture& TextureManager::getRef(const string& texture) {
	return this->textures.at(texture);
}