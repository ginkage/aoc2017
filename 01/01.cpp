#include "../lib.hpp"

int main() {
    int result = 0;
    string s;
    getline(cin, s);
    for (int i = 0; i < s.size(); i++)
        if (s[i] == s[(i + s.size() / 2) % s.size()])
            result += s[i] - '0';
    cout << result << endl;
    return 0;
}

