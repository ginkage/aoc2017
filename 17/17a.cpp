#include "../lib.hpp"

int main() {
    int input = 370;

    vector<int> v;
    v.push_back(0);
    int pos = 0;
    for (int i = 1; i <= 2017; i++) {
        pos = (pos + input) % i + 1;
        v.insert(v.begin() + pos, i);
    }
    cout << v[pos + 1] << endl;

    return 0;
}

