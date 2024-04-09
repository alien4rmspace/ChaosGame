#pragma once

#include<SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include<vector>
#include<map>
#include <iostream>

using namespace std;
using namespace sf;

class SoundManager {
public:
	SoundManager() {

	}
	~SoundManager();

	void loadBuffer(const string& name, const string& buffer);
	const SoundBuffer& getBuffer(const string& soundBuffer) const;

private:
	map<string, SoundBuffer*> soundBuffers;
};