//
// Created by ahmad on 17/12/2018.
//
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
    int i = argc - 1, number = 1;

    for (; i > 0; i--) {
        printf("%d: %s\n", number, argv[i]);
        number ++;
    }
    exit(0);
}
