#include "../lib.hpp"

int main() {
    const regex linerex("(.*) <-> (.*)");
    unordered_map<int, unordered_set<int>> edge;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            int node = stoi(linematch[1].str());
            for (int e : split_i(linematch[2].str(), ", ") )
                edge[node].insert(e);
        }
    }

    unordered_map<int, int> parent, size;
    for (auto it : edge) {
        int i = it.first;
        parent[i] = i;
        size[i] = 1;
    }

    for (auto it : edge) {
        int x = it.first;
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }

        for (int e : it.second) {
            int y = e;
            while (y != parent[y]) {
                parent[y] = parent[parent[y]];
                y = parent[y];
            }

            if (x != y) {
                parent[y] = x;
                size[x] += size[y];
            }
        }
    }

    int y = 0;
    while (y != parent[y]) {
        parent[y] = parent[parent[y]];
        y = parent[y];
    }
    cout << size[y] << endl;

    int result = 0;
    for (auto it : parent)
        if (it.first == it.second)
            result++;
    cout << result << endl;

    return 0;
}

