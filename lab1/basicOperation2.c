#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Usage: basicOperation2 NUM1 NUM2!\n");
        return 1;
    }
    double number1 = strtod(argv[1], NULL);
    double number2 = strtod(argv[2], NULL);

    printf("sum of two inputs is: %lf \n", number1+number2);
    printf("subtraction of two inputs is: %lf \n", number1-number2);
    return 0;
}
