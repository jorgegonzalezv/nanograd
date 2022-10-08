#include <stdio.h>
#include <stdlib.h>
#include "../libs/nn.h"

int try_nn(){
    float_tensor *res;
    float output;
    
    float_tensor *tensor_a = create_tensor((float[3]){1,2,3}, 3);
    float_tensor *tensor_b  = create_tensor((float[3]){2,2,2}, 3);

    res = pointwise_sum(tensor_a, tensor_b);
    if (res == NULL){
        printf("Aborting!\n");
        exit(-1);
    }
    printf("tensor b: %f,%f,%f\n", tensor_b->data[0],tensor_b->data[1],tensor_b->data[2]);


    res = pointwise_dot(tensor_a, tensor_b);
    if (res == NULL){
        printf("Aborting!\n");
        exit(-1);
    }
    printf("tensor b: %f,%f,%f\n", tensor_b->data[0],tensor_b->data[1],tensor_b->data[2]);

    printf("Apply sigmoid...\n");
    output = sigmoid_activation(reduce_sum(tensor_b, NULL));
    printf("activation output: %f\n", output);
    return 0;
}

int try_and(){
    
    float_tensor *tensor_1 = create_tensor((float[2]){0,0}, 2);
    float_tensor *tensor_2 = create_tensor((float[2]){1,0}, 2);
    float_tensor *tensor_3 = create_tensor((float[2]){0,1}, 2);
    float_tensor *tensor_4 = create_tensor((float[2]){1,1}, 2);

    float_tensor * inputs[4] = {tensor_1, tensor_2, tensor_3, tensor_4};
    float labels[4] = {0, 0, 0, 1};

    int epochs = 1000;
    int idx = 0;
    float_tensor * weights = create_tensor((float[2]){1.,1.}, 2);
    float bias = 0.5;
    float learning_rate = 0.1;

    for (int i=0; i<epochs; i++){
        idx = i % 4;
        printf("Epoch: %d, weights: %f, %f, bias: %f\n",i,  weights->data[0], weights->data[1], bias);
        optimize(inputs[idx], labels[idx], weights, &bias, learning_rate);
    }

    printf("***** Evaluation: \n");
    float res = 0;
    for (int i=0; i<4; i++){
        res = evaluate(inputs[i], weights, &bias);
        printf("INPUT: (%f, %f). LABEL: %f PROB: %f\n", inputs[i]->data[0], inputs[i]->data[1], labels[i], res);    
    }

    return 0;

}

int main(int argc, char **argv){
    
    try_and();
    return 0;
}