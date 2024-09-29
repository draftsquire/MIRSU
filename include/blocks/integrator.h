//
// Created by drafty on 26.09.2024.
//

#ifndef MIRSU_INTEGRATOR_H
#define MIRSU_INTEGRATOR_H

/**
 * @brief Класс, реализующий блок - интегратор
 */
class Integrator {
public:
    Integrator();
    Integrator(float init);
    float update(float input, float dt);
    float get_state() {
        return _state;
    }
private:
    float _state = 0;
    float _prev_in = 0;
};

#endif //MIRSU_INTEGRATOR_H
