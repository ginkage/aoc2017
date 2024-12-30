#include "../lib.hpp"

long result_b = 0;

void skip_garbage(string &s, int &i) {
    // Invariant: s[i] == '<' at entry.
    if (s[i] != '<') {
        cout << "Panic!" << endl;
        return;
    }

    for (i++; i < s.size() && s[i] != '>'; i++)
        if (s[i] == '!')
            i++;
        else
            result_b++;
}

long score(string &s, int &i, int depth) {
    // Invariant: s[i] == '{' at entry.
    long res = depth;
    if (s[i] != '{') {
        cout << "Panic!" << endl;
        return -1;
    }

    for (i++; i < s.size() && s[i] != '}'; i++) {
        if (s[i] == '{')
            res += score(s, i, depth + 1);
        else if (s[i] == '<')
            skip_garbage(s, i);
    }

    return res;
}

int main() {
    string s;
    getline(cin, s);
    int i = 0;
    cout << score(s, i, 1) << ' ' << result_b << endl;
    return 0;
}

