#include <stdio.h>

int reverseNumber(int n) {
    int reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return reversed;
}

int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int isPalindrome(int original, int reversed) {
    return original == reversed;
}

void saveToFile(int number, int reversed, int sum, int palindrome) {
    FILE *f = fopen("results.txt", "a");  // append mode

    if (f == NULL) {
        printf("File error.\n");
        return;
    }

    fprintf(f, "Number: %d\n", number);
    fprintf(f, "Reversed: %d\n", reversed);
    fprintf(f, "Sum: %d\n", sum);
    fprintf(f, "Palindrome: %s\n", palindrome ? "Yes" : "No");
    fprintf(f, "---------------------\n");

    fclose(f);
    printf("Saved to file.\n");
}

void readFile() {
    FILE *f = fopen("results.txt", "r");
    char ch;

    if (f == NULL) {
        printf("No saved results.\n");
        return;
    }

    printf("\n--- Saved Results ---\n");
    while ((ch = fgetc(f)) != EOF) {
        printf("%c", ch);
    }

    fclose(f);
}

void clearInputBuffer(void) {
    while (getchar() != '\n');
}

int getPositiveInteger(void) {
    int n;

    while (1) {
        printf("Enter a positive integer: ");
        if (scanf("%d", &n) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        if (n <= 0) {
            printf("Enter a number greater than 0.\n");
            continue;
        }

        return n;
    }
}

void showMenu(void) {
    printf("\n===== Number Analysis Toolkit =====\n");
    printf("1. Analyze number\n");
    printf("2. Analyze and save to file\n");
    printf("3. Show saved results\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

void analyze(int save) {
    int number = getPositiveInteger();
    int reversed = reverseNumber(number);
    int sum = sumOfDigits(number);
    int palindrome = isPalindrome(number, reversed);

    printf("\n--- Result ---\n");
    printf("Original: %d\n", number);
    printf("Reversed: %d\n", reversed);
    printf("Digit Sum: %d\n", sum);
    printf("Palindrome: %s\n", palindrome ? "Yes" : "No");

    if (save) {
        saveToFile(number, reversed, sum, palindrome);
    }
}

int main(void) {
    int choice;

    while (1) {
        showMenu();

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                analyze(0);
                break;
            case 2:
                analyze(1);
                break;
            case 3:
                readFile();
                break;
            case 0:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}