#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void update();
    void draw();
    int checkClicks();
    void setActive(bool active);
    void setWindowSize(float width, float height);

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Text title;
    sf::Text playText;
    sf::Text statsText;
    sf::Text exitText;
    bool isActive;
    float windowWidth;
    float windowHeight;

    void setupText(sf::Text& text, const sf::String& str, float x, float y, int size);
};