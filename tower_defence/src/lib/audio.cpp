#include "../headers/audio.h"
#include "string.h"
#include <map>

Music::Music(std::string name) {
    std::string path = "audio/";
    path += name;
    sf::Music* melody = new sf::Music;
    melody->openFromFile(path);
    melody->setVolume(30);
    melody->play();
    melody->setLoop(true);
    this->channel = melody;
}

Music::~Music() {
    delete channel;
    channel = nullptr;
}

Sound::Sound(std::string name) {
    std::string path = "audio/";
    path += name;

    this->buffer = new sf::SoundBuffer();
    this->buffer->loadFromFile(path);
    this->sound = new sf::Sound(*this->buffer);
    printf("new sound_buffer %p;\t sound %p\n", this->buffer, this->sound);
}

Sound::~Sound() {
    if (this->sound != nullptr) {
        delete this->sound;
        this->sound = nullptr;
    }
    if (this->buffer != nullptr) {
        delete this->buffer;
        this->buffer = nullptr;
    }
    printf("deleted sound_buffer %p;\t sound %p\n", this->buffer, this->sound);
}

void Sound::play() {
    this->sound->play();
}

/*Sound::Sound() {
    std::string path = "audio/";
    this->catalog = new sf::SoundBuffer* [GAME_OVER + 1];
    
    std::string name = path + "die.ogg";
    this->catalog[Sound::DIE] = new sf::SoundBuffer();
    printf("new %p\n", this->catalog[Sound::DIE]);
    this->catalog[Sound::DIE]->loadFromFile(name);

    name = path + "game_over.ogg";
    this->catalog[Sound::GAME_OVER] = new sf::SoundBuffer();
    printf("new %p\n", this->catalog[Sound::GAME_OVER]);
    this->catalog[Sound::GAME_OVER]->loadFromFile(name);
    
    name = path + "click.ogg";
    this->catalog[Sound::CLICK] = new sf::SoundBuffer();
    printf("new %p\n", this->catalog[Sound::CLICK]);
    this->catalog[Sound::CLICK]->loadFromFile(name);

    name = path + "shoot1.ogg";
    this->catalog[Sound::SHOOT_1] = new sf::SoundBuffer();
    printf("new %p\n", this->catalog[Sound::SHOOT_1]);
    this->catalog[Sound::SHOOT_1]->loadFromFile(name);

    name = path + "shoot2.ogg";
    this->catalog[Sound::SHOOT_2] = new sf::SoundBuffer();
    printf("new %p\n", this->catalog[Sound::SHOOT_2]);
    this->catalog[Sound::SHOOT_2]->loadFromFile(name);
}*/

/*void Sound::play(Sound::action type) {
    this->sound = new sf::Sound(*this->catalog[type]);
    printf("new %p\n", this->sound);
    sound->play();
}*/

/*Sound::~Sound() {
    printf("delete %p\n", this->sound);
    delete this->sound;
    this->sound = nullptr;

    for (int i = 0; i <= Sound::action::GAME_OVER; ++i) {
        printf("delete %p\n", this->catalog[i]);
        if (this->catalog[i] != nullptr) delete this->catalog[i];
    }

    if (this->catalog != nullptr) this->catalog = nullptr;
}*/