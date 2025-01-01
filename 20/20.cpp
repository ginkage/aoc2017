#include "../lib.hpp"

int main() {
    vector<vec3> pos, vel, acc;

    const regex linerex("p=<(.*)>, v=<(.*)>, a=<(.*)>");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 4) {
            auto p = split_i(linematch[1].str(), ",");
            auto v = split_i(linematch[2].str(), ",");
            auto a = split_i(linematch[3].str(), ",");
            pos.emplace_back(p[0], p[1], p[2]);
            vel.emplace_back(v[0], v[1], v[2]);
            acc.emplace_back(a[0], a[1], a[2]);
        }
    }

    int n = pos.size();
    vector<bool> collide(n, false), newcoll(n, false);
    for (int t = 0; t < 10000; t++) {
        for (int i = 0; i < n; i++) {
            if (collide[i])
                newcoll[i] = true;
            else {
                for (int j = i + 1; j < n; j++)
                    if (collide[j])
                        newcoll[j] = true;
                    else {
                        vec3 d = pos[i] - pos[j];
                        if (abs(d[0]) + abs(d[1]) + abs(d[2]) < 0.5) {
                            newcoll[i] = true;
                            newcoll[j] = true;
                        }
                    }
                vel[i] += acc[i];
                pos[i] += vel[i];
            }
        }
        swap(newcoll, collide);
/*
        double mx = -1;
        int mxi = -1;
        for (int i = 0; i < n; i++) {
            double dist = abs(pos[i][0]) + abs(pos[i][1]) + abs(pos[i][2]);
            if (mx < 0 || mx > dist) {
                mx = dist;
                mxi = i;
            }

            vel[i] += acc[i];
            pos[i] += vel[i];
        }
        cout << mxi << ' ' << mx << endl;
*/
    }

    int result = 0;
    for (int i = 0; i < n; i++)
        if (!collide[i])
            result++;
    cout << result << endl;

    return 0;
}

