#include "character.h"
#include <vector>
#include <iostream>
using namespace std;
using namespace Character;

bool Player::movePlayer(int dx, int dy, Player& player, vector<vector<int>>& field)
{
    {
        int newX = player.X + dx;
        int newY = player.Y + dy;

        if (newX == 46 && newY == 23)
        {
            checkForWin(field);
        }

        if (newX >= 0 && newX < field[0].size() && newY >= 0 && newY < field.size())
        {
            if (field[newY][newX] != 1)
            {     
                field[player.Y][player.X] = 0;
                player.X = newX;
                player.Y = newY;
                field[player.Y][player.X] = 3;
                return true;
            }
        }
        return false;
    }
}

bool Player::checkForWin(vector<vector<int>> maze)
{
    int itemsCounter = 0;
    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[0].size(); j++)
        {
            if (maze[i][j] == 5 || maze[i][j] == 6 || maze[i][j] == 7)
            {
                itemsCounter++;
            }
        }
    }
    if (itemsCounter == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}