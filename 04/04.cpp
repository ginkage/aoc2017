#include "../lib.hpp"

int main() {
    int result = 0;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        auto vs = split_s(s, " ");
        bool good = true;
        for (string &s : vs)
            sort(s.begin(), s.end());
        for (int i = 0; i < vs.size() && good; i++)
            for (int j = i + 1; j < vs.size() && good; j++)
                if (vs[i] == vs[j])
                    good = false;
        if (good)
            result++;
    }
    cout << result << endl;
    return 0;
}
