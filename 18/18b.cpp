#include "../lib.hpp"

enum op_t {
    op_snd,
    op_set,
    op_add,
    op_mul,
    op_mod,
    op_rcv,
    op_jgz
};

unordered_map<string, op_t> op_name = {
    { "snd", op_snd },
    { "set", op_set },
    { "add", op_add },
    { "mul", op_mul },
    { "mod", op_mod },
    { "rcv", op_rcv },
    { "jgz", op_jgz }
};

static int64_t *regs;
static vector<int64_t> regs0(26, 0), regs1(26, 0);
static int64_t reg_jmp;
static queue<int64_t> msg0, msg1, *psq, *prq;

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
    { op_snd, [](cmd_t &c) { psq->push(c.arg1.get()); } },
    { op_set, [](cmd_t &c) { c.arg1.get() = c.arg2.get(); } },
    { op_add, [](cmd_t &c) { c.arg1.get() += c.arg2.get(); } },
    { op_mul, [](cmd_t &c) { c.arg1.get() *= c.arg2.get(); } },
    { op_mod, [](cmd_t &c) { c.arg1.get() %= c.arg2.get(); if (c.arg1.get() < 0) c.arg1.get() += c.arg2.get(); } },
    { op_rcv, [](cmd_t &c) { c.arg1.get() = prq->front(); prq->pop(); } },
    { op_jgz, [](cmd_t &c) { if (c.arg1.get() > 0) reg_jmp = c.arg2.get(); } }
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

    int64_t ptr0 = 0, ptr1 = 0;
    int result0 = 0, result1 = 0;
    regs1['p' - 'a'] = 1;
    do {
        regs = regs0.data();
        psq = &msg0;
        prq = &msg1;
        while (ptr0 >= 0 && ptr0 < program.size()) {
            reg_jmp = 1;
            cmd_t &cmd = program[ptr0];
            if (cmd.op == op_rcv && prq->empty())
                break;
            ops[cmd.op](cmd);
            if (cmd.op == op_snd)
                result0++;
            ptr0 += reg_jmp;
        }

        regs = regs1.data();
        psq = &msg1;
        prq = &msg0;
        while (ptr1 >= 0 && ptr1 < program.size()) {
            reg_jmp = 1;
            cmd_t &cmd = program[ptr1];
            if (cmd.op == op_rcv && prq->empty())
                break;
            ops[cmd.op](cmd);
            if (cmd.op == op_snd)
                result1++;
            ptr1 += reg_jmp;
        }
    } while (!msg0.empty() || !msg1.empty());
    cout << result0 << ' ' << result1 << endl;

    return 0;
}

