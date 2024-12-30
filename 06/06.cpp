#include "../lib.hpp"

uint64_t get_state(vector<int> &v) {
    uint64_t state = 0;
    for (int i = 0; i < v.size(); i++)
        state |= ((uint64_t)v[i] << (i * 4));
    return state;
}

int main() {
    string s;
    getline(cin, s);
    auto v = split_i(s, "\t");
    unordered_map<uint64_t, int> visit;
    uint64_t state = get_state(v);
    while (visit.find(state) == visit.end()) {
        visit[state] = visit.size();

        int idx, max = -1;
        for (int i = 0; i < v.size(); i++) {
            if (max < v[i]) {
                max = v[i];
                idx = i;
            }
        }

        v[idx] = 0;
        while (max--) {
            idx = (idx + 1) % v.size();
            v[idx]++;
        }

        state = get_state(v);
    }
    cout << visit.size() << ' ' << (visit.size() - visit[state]) << endl;
    return 0;
}

