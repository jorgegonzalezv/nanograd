#include <stdio.h>
#include <stdlib.h>
#include "../libs/nn.h"

int try_nn(){
    float a[3] = {1,2,3};
    float b[3] = {2,2,2};
    float_tensor *res;
    float output;
    
    printf("sizeof array: %lu\nsizeof float: %lu\n", sizeof(a), sizeof(float));
    float_tensor tensor_a = {.size=sizeof(a)/sizeof(float), .data=&a};
    float_tensor tensor_b = {.size=sizeof(b)/sizeof(float), .data=&b};

    printf("tensor a: %f,%f,%f\n", tensor_a.data[0],tensor_a.data[1],tensor_a.data[2]);
    printf("tensor b: %f,%f,%f\n", tensor_b.data[0],tensor_b.data[1],tensor_b.data[2]);
    printf("Apply sum...\n");
    res = sum(&tensor_a, &tensor_b);
    if (res == NULL){
        printf("Aborting!\n");
        exit(-1);
    }

    printf("tensor a: %f,%f,%f\n", tensor_a.data[0],tensor_a.data[1],tensor_a.data[2]);
    printf("tensor b: %f,%f,%f\n", tensor_b.data[0],tensor_b.data[1],tensor_b.data[2]);
    printf("Apply dot...\n");
    res = dot(&tensor_a, &tensor_b);
    if (res == NULL){
        printf("Aborting!\n");
        exit(-1);
    }

    printf("tensor a: %f,%f,%f\n", tensor_a.data[0],tensor_a.data[1],tensor_a.data[2]);
    printf("tensor b: %f,%f,%f\n", tensor_b.data[0],tensor_b.data[1],tensor_b.data[2]);


    printf("Apply sigmoid...\n");
    output = sigmoid_activation(&tensor_b);
    printf("activation output: %f\n", output);
    return 0;
}

int main(int argc, char **argv){
    
    try_nn();
}