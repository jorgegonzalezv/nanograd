#include <stdio.h> // where shoud i put this?
#include <stdlib.h>
#include <math.h>
#include "nn.h"

float_tensor* create_tensor(float *data, int size){
    float_tensor *tensor = (float_tensor*) malloc(sizeof(float_tensor));
    if (tensor == NULL){
        perror("create_tensor");
        return NULL;
    }
    tensor->data  = (float*) malloc(sizeof(float)*size);
    for(int i=0; i<size; i++){
        tensor->data[i] = data[i];
    }
    tensor->data = data;
    tensor->size = size;

    printf("Created tensor (%f,%f,%f) with size %d\n",tensor->data[0], tensor->data[1],tensor->data[2], tensor->size);
    return tensor;
}

float_tensor* dot(float_tensor *a, float_tensor *b){
    if(a->size != b->size){
        perror("dot");
        return NULL;
    }
    for (int i=0; i < a->size; i++){
        b->data[i] = a->data[i] * b->data[i];
    }
    return b;
}

float_tensor* sum(float_tensor *a, float_tensor *b){
    if(a->size != b->size){
        perror("sum");
        return NULL;
    }
    for (int i=0; i < a->size; i++){
        b->data[i] = a->data[i] + b->data[i];
    }
    return b;
}

float sigmoid_activation(float_tensor *a){
    float result = 0;
    
    for(int i=0; i<a->size;i++){
        result += a->data[i];
    }

    result = 1/(1 + exp(-result));

    return result;
}

float_tensor* optimize(float_tensor *input, int ground_truth, float_tensor *weights, float * bias, float learning_rate){
    // copy weights to auxiliary variable
    float_tensor *weight_state = create_tensor(weights->data, weights->size);

    if (dot(input, weight_state) == NULL){
        perror("optimize: ");
        return NULL;
    }

    if (sum(input, weight_state) == NULL){
        perror("optimize: ");
        return NULL;
    }

    return NULL;
}
