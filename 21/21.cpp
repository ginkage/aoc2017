#include "../lib.hpp"

static inline vector<string> flip_x(const vector<string> &p) {
    int n = p.size();
    vector<string> np(n, string(n, '.'));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            np[i][j] = p[i][n-1 - j];
    return np;
}

static inline vector<string> flip_y(const vector<string> &p) {
    int n = p.size();
    vector<string> np(n, string(n, '.'));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            np[i][j] = p[n-1 - i][j];
    return np;
}

static inline vector<string> flip_d(const vector<string> &p) {
    int n = p.size();
    vector<string> np(n, string(n, '.'));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            np[i][j] = p[j][i];
    return np;
}

static inline uint32_t vtoi(const vector<string> &p) {
    int n = p.size();
    uint32_t out = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (p[i][j] =='#')
                out |= (1 << (n * i + j));
    return out;
}

unordered_set<uint32_t> flip_all(const vector<string> &p) {
    unordered_set<uint32_t> result;
    for (int i = 0; i < 8; i++) {
        vector<string> dp = p;
        if (i & 4) dp = flip_d(dp);
        if (i & 2) dp = flip_y(dp);
        if (i & 1) dp = flip_x(dp);
        result.insert(vtoi(dp));
    }
    return result;
}

unordered_map<uint32_t, uint32_t> match2;
unordered_map<uint32_t, uint32_t> match3;

int main() {
    const regex linerex("(.*) => (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            auto pattern = split_s(linematch[1].str(), "/");
            auto enhance = vtoi(split_s(linematch[2].str(), "/"));
            for (uint32_t p : flip_all(pattern))
                if (pattern.size() == 2)
                    match2[p] = enhance;
                else
                    match3[p] = enhance;
        }
    }

    unordered_set<vec, VHash> grid;
    vector<string> start = {
        ".#.",
        "..#",
        "###"
    };
    int size = start.size();
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (start[i][j] == '#')
                grid.emplace(i, j);

    for (int t = 0; t < 18; t++) {
        unordered_set<vec, VHash> newgrid;
        int es = (size % 2 == 0) ? 2 : 3, count = size / es;
        int nes = (size % 2 == 0) ? 3 : 4, ns = count * nes;

        for (int i = 0; i < count; i++)
            for (int j = 0; j < count; j++) {
                uint32_t elem = 0;
                for (int r = 0; r < es; r++)
                    for (int c = 0; c < es; c++) {
                        int gr = i * es + r;
                        int gc = j * es + c;
                        if (grid.find(vec { gr, gc }) != grid.end())
                            elem |= (1 << (r * es + c));
                    }

                elem = (es == 2 ? match2[elem] : match3[elem]);
                for (int r = 0; r < nes; r++)
                    for (int c = 0; c < nes; c++)
                        if (elem & (1 << (r * nes + c)))
                            newgrid.emplace(i * nes + r, j * nes + c);
            }

        swap(grid, newgrid);
        size = ns;
    }

    cout << grid.size() << endl;

    return 0;
}

