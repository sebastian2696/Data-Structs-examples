#include <stdio.h>

int main() {
    double number1;
    double number2;
    printf("Insert the first number: \n");
    if(scanf("%lf", &number1) != 1) {
        printf("invalid input \n");
        return 1;
    }

    printf("Insert the second number: \n");
    
    if(scanf("%lf", &number2) != 1) {
        printf("invalid input \n");
        return 1;
    }
    
    printf("sum of two inputs is: %lf \n", number1+number2);
    printf("subtraction of two inputs is: %lf \n", number1-number2);
}