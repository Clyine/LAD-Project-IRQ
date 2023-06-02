#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
//#define __STDC_FORMAT_MACROS

#define MAPeriod 5

uint64_t arr[5];
uint64_t average(uint64_t *array);
uint64_t* append(uint64_t *array, uint64_t num);

int what(int n);

int main() {
    uint64_t a = 100000000000000;
    uint64_t b = 500000;


    uint64_t* arr_ptr = &arr[0];

    for (int i = 0; i < 6; i++) {
        what(i+100000000000000);
    }

    printf("%d\n", a-b);
    printf("%u\n", a-b);
    printf("Hi: %" PRIu64 "\n", average(&arr[0]));
    printf("%f\n", a-b);


}

uint64_t average(uint64_t *array) {
    uint64_t sum;
    for (int i = 0; i < 5; i++) {
        sum += *(array+i);
    }
    return sum;
}

uint64_t* append(uint64_t *array, uint64_t num) {
    for (int i = 0; i < 5-1; i++) {
        *(array+i) = *(array+i+1);
    }
    *(array+5-1) = num;
    return array;
}

int what(int n){
    append(&arr[0], n);
}