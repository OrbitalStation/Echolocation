#define private public
#include "player.h"
#undef private

#include "level.h"
#include <cstdio>

#define LOAD_SOUND(SOUND, FILE) \
    if (!SOUND ## _sound_buf.loadFromFile(FILE ".wav")) { \
        fprintf(stderr, "Failed to load " FILE " sound; exiting..."); \
        std::exit(-1); \
    } \
    SOUND ## _sound.setBuffer(SOUND ## _sound_buf)

#define MOVE(STEP_SOUND, ...) () {\
    if (move_blocking_clock.getElapsedTime() < STEP_SOUND ## _DELAY) return;\
    move_blocking_clock.restart(); \
    play_step_sound(STEP_SOUND ## _DELAY); \
    pos = (*LevelContainer::current)->try_move_and_keep_in_bounds({__VA_ARGS__}, play_wall_bumped_sound); \
}

const float FORWARD_DELAY_IN_SECS = 0.5;

const sf::Time FORWARD_DELAY = sf::seconds(FORWARD_DELAY_IN_SECS);
const sf::Time LEFT_DELAY = sf::seconds(FORWARD_DELAY_IN_SECS * 1.2);
const sf::Time BACKWARD_DELAY = sf::seconds(FORWARD_DELAY_IN_SECS * 1.4);
const sf::Time RIGHT_DELAY = sf::seconds(FORWARD_DELAY_IN_SECS * 1.2);

sf::Vector2f Player::pos;
float Player::angle;
sf::Clock Player::pause_steps_clock, Player::move_blocking_clock;
sf::Sound Player::step_sound, Player::wall_bumped_sound;
sf::SoundBuffer Player::step_sound_buf, Player::wall_bumped_sound_buf;

static void play_wall_bumped_sound() {
    Player::wall_bumped_sound.play();
}

void Player::init() {
    LOAD_SOUND(step, "steps");
    LOAD_SOUND(wall_bumped, "wall bump");
}

void Player::move_forward MOVE(FORWARD, pos.x, pos.y - 1)

void Player::move_left MOVE(LEFT, pos.x - 0.8, pos.y)

void Player::move_right MOVE(RIGHT, pos.x + 0.8, pos.y)

void Player::move_backward MOVE(BACKWARD, pos.x, pos.y + 0.5)

void Player::play_step_sound(const sf::Time &delay) {
    if (pause_steps_clock.getElapsedTime() >= delay) {
        pause_steps_clock.restart();
        step_sound.play();
    }
}
