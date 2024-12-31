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

int main() {
    string s = "wenycdww";
    int result = 0;
    for (int i = 0; i < 128; i++) {
        stringstream ss;
        ss << s << "-" << i;
        vector<uint8_t> dense = knothash(ss.str());
        for (uint8_t byte : dense)
            for (int j = 7; j >= 0; j--)
                if (byte & (1 << j))
                    result++;
    }
    cout << result << endl;
    return 0;
}

