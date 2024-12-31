#include "../lib.hpp"

vector<uint8_t> knothash(string s) {
    vector<int> in;
    for (char c : s)
        in.push_back(c);
    in.insert(in.end(), { 17, 31, 73, 47, 23 });

    vector<uint8_t> v(256);
    for (int i = 0; i < 256; i++)
        v[i] = i;

    int cur = 0, skip = 0;
    for (int i = 0; i < 64; i++) {
        for (int len : in) {
            for (int l = 0; l < len / 2; l++)
                swap(v[(cur + l) % v.size()], v[(cur + len + v.size() - l - 1) % v.size()]);
            cur = (cur + len + skip) % v.size();
            skip++;
        }
    }

    vector<uint8_t> dense(16, 0);
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            dense[i] ^= v[16 * i + j];

    return dense;
}

unordered_set<vec, VHash> grid;
unordered_set<vec, VHash> visit;

static int di[] = { -1, 0, 1, 0 };
static int dj[] = { 0, -1, 0, 1 };

int result = 0;

void fill(int i, int j, bool init) {
    if (grid.find(vec { i, j }) == visit.end() || visit.find(vec { i, j }) != visit.end())
        return;
    visit.emplace(i, j);

    if (init) result++;

    for (int k = 0; k < 4; k++)
        fill(i + di[k], j + dj[k], false);
}

int main() {
    string s = "wenycdww";
    for (int i = 0; i < 128; i++) {
        stringstream ss;
        ss << s << "-" << i;
        vector<uint8_t> dense = knothash(ss.str());
        int col = 0;
        for (uint8_t byte : dense)
            for (int j = 7; j >= 0; j--) {
                if (byte & (1 << j))
                    grid.emplace(i, col);
                col++;
            }
    }

    for (int i = 0; i < 128; i++)
        for (int j = 0; j < 128; j++)
            fill(i, j, true);
    cout << result << endl;

    return 0;
}

