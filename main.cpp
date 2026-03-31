#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Directions: 0=Up, 1=Right, 2=Down, 3=Left
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    vector<vector<int>> grid(10, vector<int>(10));
    int startX = -1, startY = -1;

    // Read input
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 4) {
                startX = i;
                startY = j;
                grid[i][j] = 1; // Convert starting position to empty space
            }
        }
    }

    int x = startX, y = startY;
    int dir = 0; // Start going up
    int score = 0;

    // Track visited states (position + direction) to detect loops
    set<tuple<int, int, int>> visited;
    visited.insert({x, y, dir});

    // Track eaten pellets
    vector<vector<bool>> pelletEaten(10, vector<bool>(10, false));

    while (true) {
        // Try to move based on right-hand rule: right > straight > left > U-turn
        bool moved = false;

        // Priority order based on current direction
        int priorities[4];
        priorities[0] = (dir + 1) % 4; // Right
        priorities[1] = dir;           // Straight
        priorities[2] = (dir + 3) % 4; // Left
        priorities[3] = (dir + 2) % 4; // U-turn

        for (int i = 0; i < 4; i++) {
            int newDir = priorities[i];
            int nx = x + dx[newDir];
            int ny = y + dy[newDir];

            // Check if the new position is valid (within bounds and not a wall)
            if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && grid[nx][ny] != 0) {
                // Move to new position
                x = nx;
                y = ny;
                dir = newDir;
                moved = true;

                // Check if we hit a ghost
                if (grid[x][y] == 3) {
                    score -= 500;
                    cout << score << endl;
                    return 0;
                }

                // Check if we eat a pellet
                if (grid[x][y] == 2 && !pelletEaten[x][y]) {
                    score += 2;
                    pelletEaten[x][y] = true;
                }

                // Check for loop
                if (visited.count({x, y, dir})) {
                    cout << "Silly Pacman" << endl;
                    return 0;
                }
                visited.insert({x, y, dir});

                break;
            }
        }

        // If we couldn't move at all, we're stuck (shouldn't happen with valid input)
        if (!moved) {
            cout << score << endl;
            return 0;
        }
    }

    return 0;
}
