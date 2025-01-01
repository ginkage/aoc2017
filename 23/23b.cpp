#include "../lib.hpp"

int main() {
    int h = 0;
    for (int b = 109300; b <= 126300; b += 17)
        for (int d = 2, f = 1; d < 355 && f; d++)
            if (b % d == 0) {
                f = 0;
                h++;
            }
    cout << h << endl;
    return 0;
}

