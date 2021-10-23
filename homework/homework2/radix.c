#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int getDigit(int number, int digit) {
    return (int)(number/(pow(10,digit-1)))%10;
}

void countingSort (int* A, int* B, int sizeA, int digit_number);
int numDigit (int* A, int sizeA);
void radixSort (int* A, int* B, int sizeA);

int main()
{
    //C = 1 2 3 5 8 9 11 11 11 12
    int A[12] = {0,5,1,4,6,2,3,4,6,9,3,4};
    int A2[12] = {0,52,11,42,69,22,31,42,68,91,34,42};
    int B[12] = {0};

    radixSort (A2, B, 12);

    for (int i=0; i<12; i++)
        printf ("%d ", B[i]);
}

void countingSort (int* A, int* B, int sizeA, int digit_number) {

    int C[10] = {0};

    /*
    int C[dim] = {0};
    */

    for (int i=0; i<sizeA; i++) {
        C[getDigit(A[i], digit_number)]++;
        // printf("Digit: %d.\n",getDigit(A[i], digit_number));
    }

    for (int i=1; i<10; i++) {
        C[i] += C[i-1];
    }


    for (int i=0; i<10; i++) {
        printf("C[i]=%d.\n", C[i]);
    }


    for (int i=sizeA-1; i>=0; i--) {
    // printf("%d\n",C[getDigit(A[i], digit_number)]-1 );
      B[C[getDigit(A[i], digit_number)]-1] = A[i];
      //  printf("A[%d]=%d -> C[%d]=%d -> B[%d]=%d.\n", i,A[i],getDigit(A[i], digit_number) ,C[getDigit(A[i], digit_number)],C[getDigit(A[i], digit_number)], B[C[getDigit(A[i], digit_number)]]);
      C[getDigit(A[i], digit_number)]--;
    }
}

int numDigit (int* A, int sizeA) {
    int max = A[0];

    for (int i = 1; i < sizeA; i++)
        if (A[i] > max)
            max = A[i];

    int digit=0;

    do {
        max /= 10;
        digit++;
    } while (max!=0);

    return digit;
}

void radixSort (int* A, int* B, int sizeA) {

    int d = numDigit (A, sizeA);
    printf ("NumDigit -> %d.\n", d);

    for (int i = 1; i < d+1; i++) {
      countingSort(A, B, sizeA, i);
    }
}
