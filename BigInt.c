#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 1024

typedef struct {
    int digits[MAX_DIGITS];
    int size;
} BigInt;

void initBigInt(BigInt* num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->size = 0;
}

void strToBigInt(const char* str, BigInt* num) {
    initBigInt(num);
    int len = strlen(str);
    int j = 0;
    for (int i = len - 1; i >= 0; i--) {
        num->digits[j++] = str[i] - '0';
    }
    num->size = len;
}

void printBigInt(const BigInt* num) {
    for (int i = num->size - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

void addBigInt(const BigInt* num1, const BigInt* num2, BigInt* result) {
    initBigInt(result);
    int carry = 0;
    int i;

    for (i = 0; i < num1->size || i < num2->size; i++) {
        int sum = carry;
        if (i < num1->size) {
            sum += num1->digits[i];
        }
        if (i < num2->size) {
            sum += num2->digits[i];
        }

        result->digits[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry > 0) {
        result->digits[i] = carry;
        result->size = i + 1;
    } else {
        result->size = i;
    }
}

void subtractBigInt(const BigInt* num1, const BigInt* num2, BigInt* result) {
    initBigInt(result);
    int borrow = 0;
    int i;

    for (i = 0; i < num1->size; i++) {
        int diff = num1->digits[i] - borrow;

        if (i < num2->size) {
            diff -= num2->digits[i];
        }

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result->digits[i] = diff;
    }

    while (i > 0 && result->digits[i - 1] == 0) {
        i--;
    }

    result->size = i;
}

void multiplyBigInt(const BigInt* num1, const BigInt* num2, BigInt* result) {
    initBigInt(result);

    for (int i = 0; i < num1->size; i++) {
        int carry = 0;
        for (int j = 0; j < num2->size || carry > 0; j++) {
            int product = result->digits[i + j] + num1->digits[i] * (j < num2->size ? num2->digits[j] : 0) + carry;
            result->digits[i + j] = product % 10;
            carry = product / 10;
        }
    }

    int size = MAX_DIGITS;
    while (size > 0 && result->digits[size - 1] == 0) {
        size--;
    }

    result->size = size;
}

int main() {
    BigInt num1, num2, sum, difference, product;
    char inputStr1[1024];
    char inputStr2[1024];

    printf("Enter the first number: ");
    scanf("%s", inputStr1);

    printf("Enter the second number: ");
    scanf("%s", inputStr2);

    strToBigInt(inputStr1, &num1);
    strToBigInt(inputStr2, &num2);

    addBigInt(&num1, &num2, &sum);
    subtractBigInt(&num1, &num2, &difference);
    multiplyBigInt(&num1, &num2, &product);

    printf("Sum: ");
    printBigInt(&sum);

    printf("Difference: ");
    printBigInt(&difference);

    printf("Product: ");
    printBigInt(&product);

    return 0;
}
