#define private public
#include "player.h"
#undef private

#include "level.h"
#include "sound.h"
#include <cmath>

#define MOVE(STEP_SOUND, ...) () {\
    if (move_blocking_clock.getElapsedTime() < STEP_SOUND ## _DELAY) return;\
    move_blocking_clock.restart(); \
    play_step_sound(STEP_SOUND ## _DELAY); \
    pos = (*LevelContainer::current)->try_move_and_keep_in_bounds({__VA_ARGS__}, play_wall_bumped_sound); \
    sf::Listener::setPosition(pos.x, pos.y, 0);\
}

const float TAU = M_PI * 2;

const float ROTATION_IN_DEGREES = 22.5;

const float ROTATION_IN_RADIANS = ROTATION_IN_DEGREES / 360.0 * TAU;

const sf::Time ROTATION_DELAY = sf::seconds(0.5);

const float FORWARD_DELAY_IN_SECS = 0.5;

const sf::Time FORWARD_DELAY = sf::seconds(FORWARD_DELAY_IN_SECS);
const sf::Time LEFT_DELAY = sf::seconds(FORWARD_DELAY_IN_SECS * 1.2);
const sf::Time BACKWARD_DELAY = sf::seconds(FORWARD_DELAY_IN_SECS * 1.4);
const sf::Time RIGHT_DELAY = sf::seconds(FORWARD_DELAY_IN_SECS * 1.2);

sf::Vector2f Player::pos;
float Player::angle, Player::sine, Player::cosine;
sf::Clock Player::pause_steps_clock, Player::move_blocking_clock, Player::rotation_clock;
sf::Sound Player::step_sound, Player::wall_bumped_sound;
sf::SoundBuffer Player::step_sound_buf, Player::wall_bumped_sound_buf;

static void play_wall_bumped_sound() {
    Player::wall_bumped_sound.play();
}

void Player::init() {
    LOAD_SOUND(step, "steps");
    LOAD_SOUND(wall_bumped, "wall bump");

    step_sound.setRelativeToListener(true);
    wall_bumped_sound.setRelativeToListener(true);

    update_angle(0);
}

void Player::move_forward MOVE(FORWARD, pos.x + sine, pos.y - cosine)

void Player::move_left MOVE(LEFT, pos.x - 0.8 * cosine, pos.y - 0.8 * sine)

void Player::move_right MOVE(RIGHT, pos.x + 0.8 * cosine, pos.y + sine * 0.8)

void Player::move_backward MOVE(BACKWARD, pos.x - 0.5 * sine, pos.y + 0.5 * cosine)

void Player::update_angle(float radian) {
    angle = radian;
    sine = std::sin(radian);
    cosine = std::cos(radian);
}

void Player::play_step_sound(const sf::Time &delay) {
    if (pause_steps_clock.getElapsedTime() >= delay) {
        pause_steps_clock.restart();
        step_sound.play();
        printf("POS = %f, %f\n", pos.x, pos.y);
    }
}

void Player::rotate_left() {
    if (rotation_clock.getElapsedTime() < ROTATION_DELAY) return;
    rotation_clock.restart();

    angle -= ROTATION_IN_RADIANS;

    if (angle <= 0) angle += TAU;

    update_angle(angle);
    
}

void Player::rotate_right() {
    if (rotation_clock.getElapsedTime() < ROTATION_DELAY) return;
    rotation_clock.restart();

    angle += ROTATION_IN_RADIANS;

    if (angle >= TAU) angle -= TAU;

    update_angle(angle);
}
