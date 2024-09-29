//
// Created by drafty on 26.09.2024.
//

#include <ControlObject3D.h>
#include <string>

ControlObject3D::ControlObject3D(float A[3][3], float B[3], float C[3]) {
    _integrator[0] = new Integrator(0.0);
    _integrator[1] = new Integrator(0.0);
    _integrator[2] = new Integrator(0.0);
    for (int i = 0; i < 3; i++){
        memcpy(_A[i], A[i], sizeof(float) * 3);
    }
    memcpy(_B, B, sizeof(float) * 3);
    memcpy(_C, C, sizeof(float) * 3);

}

float ControlObject3D::update(float input, float dt) {
    float x1 = _integrator[0]->get_state();
    float x2 = _integrator[1]->get_state();
    float x3 = _integrator[2]->get_state();
    float x1d = _A[0][0] * x1 + _A[0][1] * x2 + _A[0][2] * x3 + _B[0] * input;
    float x2d = _A[1][0] * x1 + _A[1][1] * x2 + _A[1][2] * x3 + _B[1] * input;
    float x3d = _A[2][0] * x1 + _A[2][1] * x2 + _A[2][2] * x3 + _B[2] * input;
    _integrator[0]->update(x1d, dt);
    _integrator[1]->update(x2d, dt);
    _integrator[2]->update(x3d, dt);
    return _C[0] * x1 + _C[1] * x2 + _C[2] * x3;
}