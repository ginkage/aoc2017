#include "../lib.hpp"

int main() {
    int ml = 0, md = 1;
    unordered_map<int, int> scan;
    const regex linerex("(.*): (.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 3) {
            int layer = stoi(linematch[1].str());
            int depth = stoi(linematch[2].str());
            scan[layer] = depth;
            ml = max(ml, layer);
            md = lcm(md, 2 * depth - 2);
        }
    }

    long result = 0;
    for (int delay = 0; delay < md; delay++) {
        bool caught = false;
        for (int t = 0; t <= ml; t++) {
            auto it = scan.find(t);
            if (it != scan.end()) {
                int depth = it->second;
                int pos = (t + delay) % (2 * depth - 2);
                if (pos >= depth)
                    pos -= (pos % depth) + 1;
                if (pos == 0) {
                    caught = true;
                    if (delay == 0)
                        result += depth * t;
                }
            }
        }
        if (!caught) {
            cout << delay << endl;
            break;
        }
    }
    cout << result << endl;

    return 0;
}

