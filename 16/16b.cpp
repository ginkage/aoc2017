#include "../lib.hpp"

int main() {
    string perm = "abcdefghijklmnop";
    const regex linerexs("s(.*)");
    const regex linerexx("x(.*)/(.*)");
    const regex linerexp("p(.*)/(.*)");

    string in;
    getline(cin, in);
    auto vs = split_s(in, ",");

    vector<string> history;
    int period = -1;

    for (int i = 0; i < 10000; i++) {
        for (string s : vs) {
            smatch linematch;
            if (regex_match(s, linematch, linerexs) && linematch.size() == 2) {
                int rot = stoi(linematch[1].str());
                string ns(perm.size(), ' ');
                for (int i = 0; i < perm.size(); i++)
                    ns[(i + rot) % perm.size()] = perm[i];
                swap(perm, ns);
            }
            else if (regex_match(s, linematch, linerexx) && linematch.size() == 3) {
                int id1 = stoi(linematch[1].str());
                int id2 = stoi(linematch[2].str());
                swap(perm[id1], perm[id2]);
            }
            else if (regex_match(s, linematch, linerexp) && linematch.size() == 3) {
                char p1 = linematch[1].str()[0];
                char p2 = linematch[2].str()[0];
                swap(perm[perm.find(p1)], perm[perm.find(p2)]);
            }
            history.push_back(perm);
        }

        if (period < 0) {
            int last = history.size() - 1;
            for (int p = 10; p < history.size() / 2; p++) {
                bool match = true;
                for (int j = 0; j < p && match; j++)
                    if (history[last - j] != history[last - p - j])
                        match = false;
                if (match) {
                    period = p;
                    break;
                }
            }
        }

        if (period > 0) {
            uint64_t t = history.size();                 // Steps done so far
            uint64_t target = 1000000000llu * vs.size(); // How many steps we need to do
            cout << history[t-1 - period + (target - t) % period] << endl;
            break;
        }
    }

    return 0;
}

