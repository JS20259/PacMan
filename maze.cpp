#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
using namespace std;

namespace OurGame {
    class MazeGenerator {
    private:
        int width;
        int height;
        vector<vector<int>> maze;

        const int dx[4] = { 0, 1, 0, -1 };
        const int dy[4] = { -1, 0, 1, 0 };

    public:
        MazeGenerator(int w, int h) : width(w), height(h) {
            srand(time(nullptr));
            if (width % 2 == 0) width++;
            if (height % 2 == 0) height++;

            maze.resize(height, vector<int>(width, 1));
        }

        vector<vector<int>> generate() {
            int startX = 1;
            int startY = 1;

            maze[startY][startX] = 0;

            stack<pair<int, int>> stack;
            stack.push({ startX, startY });

            while (!stack.empty()) {
                int x = stack.top().first;
                int y = stack.top().second;

                vector<int> neighbors = getUnvisitedNeighbors(x, y);

                if (!neighbors.empty()) {
                    int direction = neighbors[rand() % neighbors.size()];
                    int nx = x + dx[direction] * 2;
                    int ny = y + dy[direction] * 2;

                    maze[y + dy[direction]][x + dx[direction]] = 0;
                    maze[ny][nx] = 0;

                    stack.push({ nx, ny });
                }
                else {
                    stack.pop();
                }
            }
            maze[height - 2][width - 1] = 0;
            return maze;
        }

        vector<int> getUnvisitedNeighbors(int x, int y) {
            vector<int> neighbors;

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i] * 2;
                int ny = y + dy[i] * 2;

                if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 && maze[ny][nx] == 1) {
                    neighbors.push_back(i);
                }
            }

            return neighbors;
        }

        int getWidth() const { return width; }
        int getHeight() const { return height; }
    };
}




