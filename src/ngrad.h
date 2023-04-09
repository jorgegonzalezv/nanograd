#ifndef NN
#define NN

typedef struct float_tensor{
    float *data;
    int size;
}float_tensor;

/* Create new tensor in memory */
float_tensor* create_tensor(float *data, int size);

/* Apply pointwise product over vectors*/
float_tensor* pointwise_dot(float_tensor *a, float_tensor *b);

/* Apply sum of vectors*/
float_tensor* pointwise_sum(float_tensor *a, float_tensor *b);

float reduce_sum(float_tensor *a, float *bias);

/* Apply sigmoid activation function to tensor */
float sigmoid_activation(float a);

float cross_entropy_loss(float y_true, float y_pred);

float cross_entropy_loss_derivative(float y_true, float y_pred);

/* Perceptron classifier optimize over sample and ground truth */
float_tensor* optimize(float_tensor *input, float y_true, float_tensor *weights, float * bias, float learning_rate);

/* Perceptron classifier evaluation over sample */
float evaluate(float_tensor *input, float_tensor *weights, float *bias);

#endif