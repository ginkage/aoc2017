#include "../lib.hpp"

vector<string> grid;
int m, n;

int main() {
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        grid.push_back(s);
    }

    m = grid.size();
    n = grid[0].size();

    int di = 1, dj = 0, pi = 0, pj = -1;
    for (int j = 0; j < n && pj < 0; j++)
        if (grid[0][j] == '|')
            pj = j;

    int steps = 0;
    stringstream result;
    while (true) {
        steps++;
        pi += di;
        pj += dj;
        if (grid[pi][pj] == '+') {
            swap(di, dj);
            if (pi + di < 0 || pj + dj < 0 || pi + di >= m || pj + dj >= n ||
                    (grid[pi + di][pj + dj] != '-' && grid[pi + di][pj + dj] != '|')) {
                di = -di;
                dj = -dj;
            }
        }
        else if (grid[pi][pj] == ' ')
            break;
        else if (grid[pi][pj] != '|' && grid[pi][pj] != '-')
            result << grid[pi][pj];
    }
    cout << result.str() << ' ' << steps << endl;

    return 0;
}

