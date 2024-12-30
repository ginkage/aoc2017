#include "../lib.hpp"

int main() {
    int input = 347991;
    unordered_map<vec, int, VHash> grid;
    vec pos(0, 0), dir(0, 1);
    grid[pos] = 1;
    for (int i = 2; i <= input; i++) {
        pos += dir;

        for (int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= 1; dj++)
                if (di != 0 || dj != 0) {
                    auto it = grid.find(pos + vec(di, dj));
                    if (it != grid.end())
                        grid[pos] += it->second;
                }

        if (grid[pos] > input) {
            cout << grid[pos] << endl;
            break;
        }

        vec left(-dir[1], dir[0]);
        if (grid.find(pos + left) == grid.end())
            dir = left;
    }
    return 0;
}
