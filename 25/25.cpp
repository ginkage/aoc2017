#include "../lib.hpp"

struct instr_t {
    bool val;
    int dir;
    char new_state;
};

struct state_t {
    instr_t instr[2];
};

int main() {
    int steps = 0;
    string s;
    smatch linematch;

    getline(cin, s); // Begin in state A.
    getline(cin, s);
    const regex linerex("Perform a diagnostic checksum after (.*) steps.");
    if (regex_match(s, linematch, linerex) && linematch.size() == 2)
        steps = stoi(linematch[1].str());

    unordered_map<int32_t, bool> tape;
    unordered_map<char, state_t> state;

    while (true) {
        getline(cin, s); // Empty line
        if (!cin) break;

        getline(cin, s);
        const regex linerex("In state (.*):");
        if (regex_match(s, linematch, linerex) && linematch.size() == 2) {
            char st = linematch[1].str()[0];
            for (int bit = 0; bit < 2; bit++) {
                getline(cin, s); // If the current value is {bit}:
                getline(cin, s);
                const regex linerex("    - Write the value (.*).");
                if (regex_match(s, linematch, linerex) && linematch.size() == 2) {
                    bool val = stoi(linematch[1].str());
                    getline(cin, s);
                    const regex linerex("    - Move one slot to the (.*).");
                    if (regex_match(s, linematch, linerex) && linematch.size() == 2) {
                        int dir = linematch[1].str() == "left" ? -1 : 1;
                        getline(cin, s);
                        const regex linerex("    - Continue with state (.*).");
                        if (regex_match(s, linematch, linerex) && linematch.size() == 2) {
                            char newst = linematch[1].str()[0];
                            state[st].instr[bit] = instr_t { val, dir, newst };
                        }
                    }
                }
            }
        }
    }

    char curst = 'A';
    int32_t pos = 0;
    for (int t = 0; t < steps; t++) {
        instr_t instr = state[curst].instr[tape[pos]];
        tape[pos] = instr.val;
        pos += instr.dir;
        curst = instr.new_state;
    }

    int result = 0;
    for (auto s : tape)
        result += s.second;
    cout << result << endl;

    return 0;
}

