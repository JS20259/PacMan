#include "ItemSpawner.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
using namespace std;
using namespace Items;

vector<Item> ItemSpawner::readFile(string filename)
{
    vector<Item> items;
    ifstream file(filename);
    if (!file.is_open())
        return items;

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;

        size_t start = line.find_first_not_of(" \t");
        if (start == string::npos) continue; 

        istringstream iss(line);
        Item item;

        if (iss >> item.name >> item.cost >> item.symbol)
        {

            items.push_back(item);
        }
    }
    file.close();

    cout << "Загружено предметов: " << items.size() << endl;
    for (const auto& item : items)
    {
        cout << item.name << " - " << item.cost << " - символ: " << item.symbol << endl;
    }
    return items;
}

void ItemSpawner::generateItems(vector<Item> items, vector<vector<int>>& maze, int itemsAmount)
{
    srand(time(0));

    for (int i = 0; i < itemsAmount; i++)
    {
        while (true)
        {
            int x = rand() % maze[0].size();
            int y = rand() % maze.size();

            if (maze[y][x] == 0)
            {
                int itemIndex = i % items.size();
                maze[y][x] = items[itemIndex].symbol;
                break;
            }
        }
    }

    cout << "Сгенерировано " << itemsAmount << " предметов" << endl;
}