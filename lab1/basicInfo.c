#include <stdio.h>

int main() {
    char buffer[256];
    printf("Insert your full address: ");
    if (fgets(buffer, 256, stdin) != NULL) {
        printf("Your address is: %s \n", buffer);
    } else {
        printf("Error input \n");
    }
}