#include <SFML/Graphics.hpp>
#include "player.h"
#include "level.h"

int main() {

    Player::init();
    LevelContainer::init();

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "The Blind Simulator");

    sf::Event event;

    window.display();

    while (window.isOpen()) {

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) Player::move_forward();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) Player::move_left();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) Player::move_backward();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) Player::move_right();

    }

    LevelContainer::terminate();

}
