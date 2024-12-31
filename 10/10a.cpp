#include "../lib.hpp"

int main() {
    string s;
    getline(cin, s);
    vector<int> in = split_i(s, ",");
    vector<int> v(256);
    for (int i = 0; i < 256; i++)
        v[i] = i;

    int cur = 0, skip = 0;
    for (int len : in) {
        for (int l = 0; l < len / 2; l++)
            swap(v[(cur + l) % v.size()], v[(cur + len + v.size() - l - 1) % v.size()]);
        cur = (cur + len + skip) % v.size();
        skip++;
    }

    cout << v[0] * v[1] << endl;

    return 0;
}

