#include "../lib.hpp"

int main() {
    vector<int> jmp;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        jmp.push_back(stoi(s));
    }

    int t = 0;
    for (int i = 0; (i >= 0 && i < jmp.size()); t++) {
        int off = jmp[i];
        jmp[i] += (off >= 3) ? -1 : 1;
        i += off;
    }
    cout << t << endl;

    return 0;
}

