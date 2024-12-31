#include "../lib.hpp"

unordered_map<string, pair<float, float>> dir = {
    { "n", { -1, 0 } },
    { "ne", { -0.5, 1 } },
    { "se", { 0.5, 1 } },
    { "s", { 1, 0 } },
    { "sw", { 0.5, -1 } },
    { "nw", { -0.5, -1 } }
};

int main() {
    string s;
    getline(cin, s);
    pair<float, float> pos(0, 0);
    double result = 0;
    for (auto v : split_s(s, ",")) {
        auto d = dir[v];
        pos.first += d.first;
        pos.second += d.second;
        result = max(result, abs(pos.second) + abs(pos.first - pos.second * 0.5));
    }
    cout << result << endl;
    return 0;
}

