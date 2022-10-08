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
    tensor->size = size;
    return tensor;
}

float_tensor* scalar_product(float_tensor *tensor, float scalar){
    if(tensor == NULL){
        perror("scalar_product");
        return NULL;
    }
    for (int i=0; i < tensor->size; i++){
        tensor->data[i] = tensor->data[i] * scalar;
    }
    return tensor;
}

float_tensor* pointwise_dot(float_tensor *a, float_tensor *b){
    if(a->size != b->size){
        perror("dot");
        return NULL;
    }
    for (int i=0; i < a->size; i++){
        b->data[i] = a->data[i] * b->data[i];
    }
    return b;
}

float_tensor* pointwise_sum(float_tensor *a, float_tensor *b){
    if(a->size != b->size){
        perror("sum");
        return NULL;
    }
    for (int i=0; i < a->size; i++){
        b->data[i] = a->data[i] + b->data[i];
    }
    return b;
}

float reduce_sum(float_tensor *a, float *bias){
    //TODO error control
    float result = 0;
    
    for(int i=0; i<a->size;i++){
        result += a->data[i];
    }
    if (bias != NULL)
        result += *bias;
    
    return result;
}

float sigmoid_activation(float a){
    float result = 1/(1 + exp(-a));
    return result;
}

float cross_entropy_loss(float y_true, float y_pred){
    return y_true * (log(y_pred)) + (1 - y_true) * (log(1 - y_pred));
}

float cross_entropy_loss_derivative(float y_true, float y_pred){
    //TODO deal with division by zero
    if (y_true == 1 && y_pred == 0){
        return -10;
    }
    if (y_true == 0 && y_pred == 1){
        return 10;
    }
    return y_true * (1/y_pred) - (1 - y_true) * (1/(1 - y_pred));
}

// optimize perceptron
float_tensor* optimize(float_tensor *input, float y_true, float_tensor *weights, float * bias, float learning_rate){
    //TODO: make more efficient use of variables, and implement backprop for other nn arch!
    float_tensor *weight_state = create_tensor(weights->data, weights->size);
    float bias_state;
    float y_sum; 
    float y_pred;
    // apply weights
    if (pointwise_dot(input, weight_state) == NULL){
        perror("optimize: ");
        return NULL;
    }

    // apply sum and sigmoid activation
    y_sum = reduce_sum(weight_state, bias);
    y_pred = sigmoid_activation(y_sum);

    printf("y_pred: %f. y_true: %f. Loss: %f\n",y_pred, y_true, cross_entropy_loss(y_true, y_pred));
    // calculate derivative of loss function (cross entropy for now) with respect to each weight (in perceptron)
    for(int i=0; i<weights->size; i++){
        weight_state->data[i] = cross_entropy_loss_derivative(y_true, y_pred) * y_pred * (1 - y_pred) * input->data[i]; // chain rule, rules!
        //weight_state->data[i] = (-y_pred + y_true) * input->data[i]; // reduced expression for logistic loss with sigmoid... (less numeric errors?)

    }
    //bias_state = -y_pred + y_true;
    bias_state = cross_entropy_loss_derivative(y_true, y_pred) * y_pred * (1 - y_pred);

    //printf(">> Gradiente weights: %f, %f\n",weight_state->data[0], weight_state->data[1]);

    // update weights and free memory
    for(int i=0; i<weights->size; i++){
        weights->data[i] = weights->data[i] + learning_rate * weight_state->data[i];
    }
    *bias += learning_rate * bias_state;

    free(weight_state);

    return weights;
}


//evaluate perceptron
float evaluate(float_tensor *input, float_tensor *weights, float *bias){
    float_tensor *weight_state = create_tensor(weights->data, weights->size);
    float y_pred;

    // apply weights
    if (pointwise_dot(input, weight_state) == NULL){
        perror("optimize: ");
        return -1;
    }
    // apply sum and sigmoid activation
    y_pred = sigmoid_activation(reduce_sum(weight_state, bias));
    return y_pred;
}
