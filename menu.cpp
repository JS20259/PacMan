#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow& window)
    : window(window), isActive(true) {


    if (!font.loadFromFile("fonts/arial.ttf")) {
        return;
    }

    backgroundTexture.loadFromFile("Image/backGroundMenu.jpg");
    background.setSize(sf::Vector2f(1920, 1080));
    background.setTexture(&backgroundTexture);



    setupText(title, "Pac-man", 1920 / 2, 100, 80);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);

    setupText(playText, L"»√–¿“‹", 1920 / 2, 450, 60);
    setupText(exitText, L"¬€’Œƒ", 1920 / 2, 550, 60);
}

void Menu::setupText(sf::Text& text, const sf::String& str, float x, float y, int size) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setPosition(x, y);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(x, y);
}

void Menu::update() {
    if (!isActive) return;


    sf::Vector2i mousePos = sf::Mouse::getPosition(window);


    playText.setFillColor(playText.getGlobalBounds().contains(mousePos.x, mousePos.y) ?
        sf::Color::Red : sf::Color::White);
    exitText.setFillColor(exitText.getGlobalBounds().contains(mousePos.x, mousePos.y) ?
        sf::Color::Red : sf::Color::White);
}

void Menu::draw() {
    if (!isActive) return;
    window.draw(background);
    window.draw(title);
    window.draw(playText);
    window.draw(statsText);
    window.draw(exitText);
}

int Menu::checkClicks() {
    if (!isActive) return 0;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (playText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return 1;
        }
        else if (exitText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return 3;
        }
    }

    return 0;
}

void Menu::setActive(bool active) {
    isActive = active;
}