#include <iostream>
#include <vector>
#include "ItemSpawner.h"
using namespace Items;
using namespace std;
namespace Character
{
    class Character
    {
    public:
        string name;
        int X;
        int Y;
    };
    class Player : public Character
    {
    public:
        vector<Item> inventory;
        bool movePlayer(int dx, int dy, Player& player, vector<vector<int>>& field);
        bool checkForWin(vector<vector<int>> maze);
    };
}

