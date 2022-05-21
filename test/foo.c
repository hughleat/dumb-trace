#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        return 1;
    }
    for (int i = 0; i < 3; ++i) {
        printf("%d\n", i);
    }
    return 0;
}