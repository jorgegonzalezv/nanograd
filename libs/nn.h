#ifndef NN
#define NN

typedef struct float_tensor{
    float *data;
    int size;
}float_tensor;

/* Create new tensor in memory */
float_tensor* create_tensor(float *data, int size);

/* Apply pointwise product over vectors*/
float_tensor* dot(float_tensor *a, float_tensor *b);

/* Apply sum of vectors*/
float_tensor* sum(float_tensor *a, float_tensor *b);

/* Apply sigmoid activation function to tensor */
float sigmoid_activation(float_tensor *a);

/* Perceptron classifier optimize over sample and ground truth */
float_tensor* optimize(float_tensor *input, int ground_truth, float_tensor *weights, float * bias, float learning_rate);
#endif