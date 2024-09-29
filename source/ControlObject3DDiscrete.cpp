//
// Created by drafty on 29.09.2024.
//
#include <ControlObject3DDiscrete.h>
#include <string.h>
ControlObject3DDiscrete::ControlObject3DDiscrete(float A[3][3], float B[3], float C[3]) {
    for (int i = 0; i < 3; i++){
        memcpy(_A[i], A[i], sizeof(float) * 3);
    }
    memcpy(_B, B, sizeof(float) * 3);
    memcpy(_C, C, sizeof(float) * 3);

}

float ControlObject3DDiscrete::update(float input) {
    float x1 = _A[0][0] * _x1_prev + _A[0][1] * _x2_prev + _A[0][2] * _x3_prev + _B[0] * input;
    float x2 = _A[1][0] * _x1_prev + _A[1][1] * _x2_prev + _A[1][2] * _x3_prev + _B[1] * input;
    float x3 = _A[2][0] * _x1_prev + _A[2][1] * _x2_prev + _A[2][2] * _x3_prev + _B[2] * input;
    _x1_prev = x1;
    _x2_prev = x2;
    _x3_prev = x3;
    return _C[0] * x1 + _C[1] * x2 + _C[2] * x3;
}
