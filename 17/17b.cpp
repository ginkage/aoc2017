#include "../lib.hpp"

int main() {
    int input = 370;
    int pos = 0;
    for (int i = 1; i <= 50000000; i++) {
        pos = (pos + input) % i + 1;
        if (pos == 1)
            cout << i << endl;
    }
    return 0;
}

