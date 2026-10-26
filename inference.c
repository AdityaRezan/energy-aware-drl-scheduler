#include <math.h>
#include "inference.h"
#include "weights.h"

float tanh_activation(float x)
{
    return tanhf(x);
}

int infer_drl_action(float queue, float temp, float core)
{
    float input[INPUT_DIM] = {queue, temp, core};
    float h1[HIDDEN_DIM];
    float h2[HIDDEN_DIM];
    float output[ACTION_DIM];
    int best_action = 0;
    float max_logit = -1e9f;

    for (int i = 0; i < HIDDEN_DIM; i++) {
        float sum = B1[i];
        for (int j = 0; j < INPUT_DIM; j++) {
            sum += W1[i][j] * input[j];
        }
        h1[i] = tanh_activation(sum);
    }

    for (int i = 0; i < HIDDEN_DIM; i++) {
        float sum = B2[i];
        for (int j = 0; j < HIDDEN_DIM; j++) {
            sum += W2[i][j] * h1[j];
        }
        h2[i] = tanh_activation(sum);
    }

    for (int i = 0; i < ACTION_DIM; i++) {
        float sum = B_OUT[i];
        for (int j = 0; j < HIDDEN_DIM; j++) {
            sum += W_OUT[i][j] * h2[j];
        }
        output[i] = sum;
        if (output[i] > max_logit) {
            max_logit = output[i];
            best_action = i;
        }
    }

    return best_action;
}
