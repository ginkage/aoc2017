#include "../lib.hpp"

int main() {
    uint64_t a = 783, b = 325;
    int result = 0;
    for (int i = 0; i < 40000000; i++) {
        a = (a * 16807llu) % 2147483647llu;
        b = (b * 48271llu) % 2147483647llu;
        if ((a & 0xFFFF) == (b & 0xFFFF))
            result++;
    }
    cout << result << endl;
    return 0;
}

