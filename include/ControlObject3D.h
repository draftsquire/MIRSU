//
// Created by drafty on 26.09.2024.
//

#include <blocks/integrator.h>
#ifndef MIRSU_OBJECT_H
#define MIRSU_OBJECT_H

/**
 * @brief Класс, реализующий объект управления
 */
class ControlObject3D {
public:
    ControlObject3D(float A[3][3], float B[3], float C[3]);
    float update(float input, float dt);
private:
    Integrator* _integrator[3];
    float _A[3][3];
    float _B[3];
    float _C[3];
};

#endif //MIRSU_OBJECT_H
