#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;
#include "maze.cpp"
using namespace OurGame;
#include "character.h"
using namespace Character;
#include "ItemSpawner.h"
using namespace Items;
#include "menu.h"

void PrintField(const vector<vector<int>>& field)
{
    //if (field.empty())
    //{
    //    cout << "Поле пустое" << endl;
    //    return;
    //}
    int rows = field.size();
    int cols = field[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//void PrintCoords(const Player& player, const vector<vector<int>>& maze)
//{
//    system("cls");
//    PrintField(maze);
//    cout << "Координата X: " << player.X << "; Координата Y: " << player.Y
//        << "; Клетка поля: " << maze[player.Y][player.X] << endl;
//}

int main() {
    setlocale(LC_ALL, "Russian");

    RenderWindow window(VideoMode(1920, 1080), L"Pacman v2", Style::Fullscreen);

    Texture textyreFlat;
    Texture textyreWall;
    Texture textyreVoid;
    Texture textyrePlayer;
    Texture textyreWatch;
    Texture textyreCoin;
    Texture textyreAxe;

    Sprite wallSprite;
    Sprite voidSprite;
    Sprite playerSprite;
    Sprite watchSprite;
    Sprite coinSprite;
    Sprite axeSprite;

    textyreFlat.loadFromFile("Image/flat.png");
    textyreWall.loadFromFile("Image/wall2.png");
    textyreVoid.loadFromFile("Image/void.png");
    textyrePlayer.loadFromFile("Image/pacman2.png");
    textyreWatch.loadFromFile("Image/watch2.png");
    textyreCoin.loadFromFile("Image/coin2.png");
    textyreAxe.loadFromFile("Image/axe2.png");


    RectangleShape gameBackground(Vector2f(1920, 1080));
    gameBackground.setTexture(&textyreFlat);

    wallSprite.setTexture(textyreWall);
    voidSprite.setTexture(textyreVoid);
    playerSprite.setTexture(textyrePlayer);
    watchSprite.setTexture(textyreWatch);
    coinSprite.setTexture(textyreCoin);
    axeSprite.setTexture(textyreAxe);

    const int CELL_SIZE = 40;

    Menu menu(window);

    bool inMenu = true;
    bool inGame = false;

    MazeGenerator* mazeGen = nullptr;
    vector<vector<int>> maze;
    Player player;
    ItemSpawner spawner;
    vector<Item> items;

    Clock clock;
    float timeSinceLastUpdate = 0;
    float updateInterval = 0.1f;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (/*event.type == Event::KeyPressed && inGame ||*/ player.checkForWin(maze) && (player.X == 46 && player.Y == 23)) {
                //if (event.key.code == Keyboard::Escape) {
                inMenu = true;
                inGame = false;
                menu.setActive(true);

                delete mazeGen;
                mazeGen = nullptr;
                maze.clear();
                items.clear();
                //}
            }
        }

        if (inMenu) {
            menu.update();

            int action = menu.checkClicks();
            if (action == 1) {
                inMenu = false;
                inGame = true;
                menu.setActive(false);

                mazeGen = new OurGame::MazeGenerator(46, 25);
                maze = mazeGen->generate();

                player = Player();
                player.X = 1;
                player.Y = 1;

                if (maze.size() > player.Y && maze[0].size() > player.X) {
                    maze[player.Y][player.X] = 3;
                }

                items = spawner.readFile("Items.txt");
                if (!items.empty()) {
                    spawner.generateItems(items, maze, 5);
                }

                PrintField(maze);
            }
            else if (action == 2) {
            }
            else if (action == 3) {
                window.close();
            }
        }
        else if (inGame && mazeGen) {
            float deltaTime = clock.restart().asSeconds();
            timeSinceLastUpdate += deltaTime;

            if (timeSinceLastUpdate >= updateInterval) {
                bool moved = false;

                if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
                    moved = player.movePlayer(0, -1, player, maze);
                }
                else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
                    moved = player.movePlayer(0, 1, player, maze);
                }
                else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
                    moved = player.movePlayer(-1, 0, player, maze);
                }
                else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
                    moved = player.movePlayer(1, 0, player, maze);
                }

                if (moved) {
                    timeSinceLastUpdate = 0;
                    /*PrintCoords(player, maze);*/
                }
            }
        }

        window.clear();

        if (inMenu) {
            menu.draw();
        }
        else if (inGame && mazeGen && !maze.empty()) {
            window.draw(gameBackground);

            for (int y = 0; y < mazeGen->getHeight(); y++) {
                for (int x = 0; x < mazeGen->getWidth(); x++) {
                    float posX = x * CELL_SIZE + CELL_SIZE / 2;
                    float posY = y * CELL_SIZE + CELL_SIZE;

                    if (maze[y][x] == 0) {
                        voidSprite.setPosition(posX, posY);
                        window.draw(voidSprite);
                    }
                    else if (maze[y][x] == 1) {
                        wallSprite.setPosition(posX, posY);
                        window.draw(wallSprite);
                    }
                    else if (maze[y][x] == 3) {
                        playerSprite.setPosition(posX, posY);
                        window.draw(playerSprite);
                    }
                    else if (maze[y][x] == 5) {
                        watchSprite.setPosition(posX, posY);
                        window.draw(watchSprite);
                    }
                    else if (maze[y][x] == 6) {
                        coinSprite.setPosition(posX, posY);
                        window.draw(coinSprite);
                    }
                    else if (maze[y][x] == 7) {
                        axeSprite.setPosition(posX, posY);
                        window.draw(axeSprite);
                    }
                    else {
                        voidSprite.setPosition(posX, posY);
                        window.draw(voidSprite);
                    }
                }
            }
        }

        window.display();
    }
    delete mazeGen;

    return 0;
}