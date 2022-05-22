#include <stdio.h>

void f() {
    printf("f\n");
}

void g() {
    printf("g\n");
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        return 1;
    }
    f();
    g();
    for (int i = 0; i < 3; ++i) {
        printf("main %d\n", i);
    }
    return 0;
}