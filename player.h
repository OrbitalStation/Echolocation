#pragma once
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Player {

public:

    static void init();

    static void move_forward();

    static void move_left();

    static void move_backward();

    static void move_right();

private:

    static void play_step_sound(const sf::Time &delay);

private:

    /* Position in meters */
    static sf::Vector2f pos;

    static float angle;

    static sf::Clock pause_steps_clock, move_blocking_clock;

    static sf::Sound step_sound, wall_bumped_sound;

    static sf::SoundBuffer step_sound_buf, wall_bumped_sound_buf;
};
