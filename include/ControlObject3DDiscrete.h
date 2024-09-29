//
// Created by drafty on 29.09.2024.
//

#ifndef MIRSU_CONTROLOBJECT3DDISCRETE_H
#define MIRSU_CONTROLOBJECT3DDISCRETE_H

/**
 * @brief Класс, реализующий дискретный объект управления
 */
class ControlObject3DDiscrete {
public:
    ControlObject3DDiscrete(float A[3][3], float B[3], float C[3]);
    float update(float input);
private:
    float _A[3][3];
    float _B[3];
    float _C[3];
    float _x1_prev, _x2_prev, _x3_prev;
};

#endif //MIRSU_CONTROLOBJECT3DDISCRETE_H
