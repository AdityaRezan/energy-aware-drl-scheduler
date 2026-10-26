#ifndef INFERENCE_H
#define INFERENCE_H

#define INPUT_DIM 3
#define HIDDEN_DIM 64
#define ACTION_DIM 4

float tanh_activation(float x);
int infer_drl_action(float queue, float temp, float core);

#endif
