#include "../lib.hpp"

struct node_t {
    unordered_set<int> children;
    int parent { -1 };
    int weight;
};

unordered_map<int, node_t> nodes;

long sum(node_t &node) {
    long result = node.weight;
    long sub = -1;
    for (int child : node.children) {
        long s = sum(nodes[child]);
        if (sub < 0)
            sub = s;
        else if (sub != s)
            cout << (nodes[child].weight + sub - s) << endl;
        result += s;
    }
    return result;
}

int main() {
    const regex linerex1("(.*) \\((\\d+)\\) -> (.*)");
    const regex linerex2("(.*) \\((\\d+)\\)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex1) && linematch.size() == 4) {
            int node = remap(linematch[1].str());
            int weight = stoi(linematch[2].str());
            nodes[node].weight = weight;
            for (string v : split_s(linematch[3].str(), ", ")) {
                int child = remap(v);
                nodes[node].children.insert(child);
                nodes[child].parent = node;
            }
        }
        else if (regex_match(s, linematch, linerex2) && linematch.size() == 3) {
            int node = remap(linematch[1].str());
            int weight = stoi(linematch[2].str());
            nodes[node].weight = weight;
        }
    }

    vector<string> name(names.size());
    for (auto it : names)
        name[it.second] = it.first;

    for (auto node : nodes)
        if (node.second.parent == -1) {
            cout << name[node.first] << endl;
            for (int child : node.second.children)
                sum(nodes[child]);
        }

    return 0;
}

