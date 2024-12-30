#include "../lib.hpp"

int main() {
    long result_a = 0, result_b = 0;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;
        auto vs = split_i(s, "\t");
        sort(vs.begin(), vs.end());
        result_a += vs.back() - vs.front();
        for (int i = vs.size() - 1; i > 0; i--)
            for (int j = 0; j < i; j++)
                if (vs[i] % vs[j] == 0)
                    result_b += vs[i] / vs[j];
    }
    cout << result_a << ' ' << result_b << endl;
    return 0;
}

