#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void convertToBinary(int value) {
    uint32_t bit = value;
    for (int i = 31; i >= 0; i--) {
        if (((bit >> i) & 1) == 1) {
           printf("1");
        } else {
           printf("0");
        }
    }
    printf("\n");
}

void convertBack(char *bitstring) {
    uint32_t value = 0;
    for (int i = 0; bitstring[i] != '\0'; i++) {
        if (bitstring[i] == '1') {
            value = (value << 1) | 1;
        } else if (bitstring[i] == '0'){
            value <<= 1;
        }
    }
    printf("%d\n", value);
}

int main(void) {
    int option;
    printf("What would you like to do?\n");
    printf("1 - Bit to String\n");
    printf("2 - String to Bit\n");
    printf("Enter 1 or 2: ");
    scanf("%d", &option);
    if (option == 1) {
        int input;
        printf("Enter a number: ");
        while (scanf("%d", &input)) {
            convertToBinary(input);
            printf("Enter a number: ");
        }
    } else {
        char input[256];
        printf("Enter a bitstring: ");
        while (scanf("%s", input)) {
            convertBack(input);
            printf("Enter a bitstring: ");
        }
    }
    return 0;
}