#include "../lib.hpp"

int main() {
    string s;
    getline(cin, s);
    vector<int> in; //= split_i(s, ",");
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

    string result;
    for (uint8_t d : dense) {
        result += hexdigit[d >> 4];
        result += hexdigit[d & 15];
    }
    cout << result << endl;

    return 0;
}

