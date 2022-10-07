#include <stdio.h>
#include <stdlib.h>
#include "../libs/nn.h"

int try_nn(){
    float_tensor *res;
    float output;
    
    float_tensor *tensor_a = create_tensor((float[3]){1,2,3}, 3);
    float_tensor *tensor_b  = create_tensor((float[3]){2,2,2}, 3);

    res = sum(tensor_a, tensor_b);
    if (res == NULL){
        printf("Aborting!\n");
        exit(-1);
    }
    printf("tensor b: %f,%f,%f\n", tensor_b->data[0],tensor_b->data[1],tensor_b->data[2]);


    res = dot(tensor_a, tensor_b);
    if (res == NULL){
        printf("Aborting!\n");
        exit(-1);
    }
    printf("tensor b: %f,%f,%f\n", tensor_b->data[0],tensor_b->data[1],tensor_b->data[2]);

    printf("Apply sigmoid...\n");
    output = sigmoid_activation(tensor_b);
    printf("activation output: %f\n", output);
    return 0;
}

int main(int argc, char **argv){
    
    try_nn();
}