#include "../lib.hpp"

int main() {
    int input = 347991;
    unordered_map<vec, int, VHash> grid;
    vec pos(-1, 0), dir(1, 0);
    for (int i = 1; i <= input; i++) {
        pos += dir;
        grid[pos] = i;
        vec left(-dir[1], dir[0]);
        if (grid.find(pos + left) == grid.end())
            dir = left;
    }
    cout << abs(pos[0]) + abs(pos[1]) << endl;
    return 0;
}
