#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

namespace Items
{
	class Item
	{
	public:
		string name;
		int cost;
		int symbol;
	};

	class ItemSpawner
	{
	public:
		vector<Item> readFile(string filename);
		void generateItems(vector<Item>, vector<vector<int>>& maze, int itemsAmount);
	};
}




