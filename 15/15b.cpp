#include "../lib.hpp"

int main() {
    uint64_t a = 783, b = 325;
    queue<uint64_t> qa, qb;
    int result = 0, pairs = 0;
    while (pairs < 5000000) {
        a = (a * 16807llu) % 2147483647llu;
        b = (b * 48271llu) % 2147483647llu;
        if (a % 4 == 0)
            qa.push(a);
        if (b % 8 == 0)
            qb.push(b);
        while (!qa.empty() && !qb.empty()) {
            if ((qa.front() & 0xFFFF) == (qb.front() & 0xFFFF))
                result++;
            qa.pop();
            qb.pop();
            pairs++;
        }
    }
    cout << result << endl;
    return 0;
}

