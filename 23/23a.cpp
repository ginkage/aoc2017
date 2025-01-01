#include "../lib.hpp"

enum op_t {
    op_set,
    op_sub,
    op_mul,
    op_jnz
};

unordered_map<string, op_t> op_name = {
    { "set", op_set },
    { "sub", op_sub },
    { "mul", op_mul },
    { "jnz", op_jnz }
};

static vector<int64_t> regs(26, 0);
static int64_t reg_jmp;

struct val_t {
    int64_t val;
    bool is_im;

    int64_t& get() { return is_im ? val : regs[val]; }

    val_t(const string &v) {
        if (isdigit(v[0]) || v[0] == '-') {
            val = stol(v);
            is_im = true;
        }
        else {
            val = v[0] - 'a';
            is_im = false;
        }
    }

    val_t() {}
};

struct cmd_t {
    op_t op;
    val_t arg1;
    val_t arg2;
};

unordered_map<op_t, function<void(cmd_t&)>> ops = {
    { op_set, [](cmd_t &c) { c.arg1.get() = c.arg2.get(); } },
    { op_sub, [](cmd_t &c) { c.arg1.get() -= c.arg2.get(); } },
    { op_mul, [](cmd_t &c) { c.arg1.get() *= c.arg2.get(); } },
    { op_jnz, [](cmd_t &c) { if (c.arg1.get()) reg_jmp = c.arg2.get(); } }
};

int main() {
    const regex linerex2("(.*) (.*) (.*)");
    const regex linerex1("(.*) (.*)");
    vector<cmd_t> program;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        cmd_t cmd;
        smatch linematch;
        if (regex_match(s, linematch, linerex2) && linematch.size() == 4) {
            cmd.op = op_name[linematch[1].str()];
            cmd.arg1 = val_t(linematch[2].str());
            cmd.arg2 = val_t(linematch[3].str());
        }
        else if (regex_match(s, linematch, linerex1) && linematch.size() == 3) {
            cmd.op = op_name[linematch[1].str()];
            cmd.arg1 = val_t(linematch[2].str());
        }
        program.push_back(cmd);
    }

    int result = 0;
    int64_t ptr = 0;
    //regs[0] = 1;
    while (ptr >= 0 && ptr < program.size()) {
        reg_jmp = 1;
        cmd_t &cmd = program[ptr];
        ops[cmd.op](cmd);
        if (cmd.op == op_mul)
            result++;
        ptr += reg_jmp;
    }
    cout << result << endl;
    return 0;
}

