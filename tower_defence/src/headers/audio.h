#pragma once
#include <SFML/Audio.hpp>
//#include <map>

class Music : public sf::Music {
public:
    Music(std::string name);
    ~Music();
private:
    sf::Music* channel;
};

class Sound : public sf::Sound {
public:
    Sound(std::string name);
    ~Sound();
    

    void play(bool once = false);
private:
    bool sound_has_played;
    sf::SoundBuffer* buffer;
    sf::Sound* sound;
};