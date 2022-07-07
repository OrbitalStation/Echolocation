#pragma once
#include <SFML/Audio.hpp>

const size_t DRIP_ECHO_NUMBER = 8;

class Drip {

public:

    Drip();

    void sound();

private:

    sf::Vector2f position;

    //Echo echo_drip[DRIP_ECHO_NUMBER];

    sf::Sound drip_sound;
    sf::SoundBuffer drip_sound_buf;

    sf::Clock clock;

};
