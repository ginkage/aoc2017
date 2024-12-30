#include "../lib.hpp"

unordered_map<int, int> reg_val;

unordered_map<string, function<bool(int, int)>> cmp_fn = {
    { "<", [](int a, int b) { return a < b; } },
    { "<=", [](int a, int b) { return a <= b; } },
    { ">", [](int a, int b) { return a > b; } },
    { ">=", [](int a, int b) { return a >= b; } },
    { "==", [](int a, int b) { return a == b; } },
    { "!=", [](int a, int b) { return a != b; } }
};

int main() {
    int result_b = -1;
    const regex linerex("(.*) (.*) (.*) if (.*) (.*) (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 7) {
            int reg = remap(linematch[1].str());
            string op = linematch[2].str();
            int arg = stoi(linematch[3].str());
            if (op == "dec")
                arg = -arg;
            int ireg = remap(linematch[4].str());
            string cmp = linematch[5].str();
            int carg = stoi(linematch[6].str());
            if (cmp_fn[cmp](reg_val[ireg], carg))
                result_b = max(result_b, reg_val[reg] += arg);
        }
    }

    int result_a = -1;
    for (auto it : reg_val)
        result_a = max(result_a, it.second);
    cout << result_a << ' ' << result_b << endl;

    return 0;
}

