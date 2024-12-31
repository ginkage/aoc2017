#include "../lib.hpp"

int main() {
    string perm = "abcdefghijklmnop";
    const regex linerexs("s(.*)");
    const regex linerexx("x(.*)/(.*)");
    const regex linerexp("p(.*)/(.*)");

    string in;
    getline(cin, in);
    for (string s : split_s(in, ",")) {
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
    }
    cout << perm << endl;

    return 0;
}

