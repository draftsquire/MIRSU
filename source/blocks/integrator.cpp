//
// Created by drafty on 26.09.2024.
//

#include <blocks/integrator.h>
/**
 *
 * @param init - начальное значение интегриуемой переменной
 */
Integrator::Integrator(float init) {
    _state = init;
}

/**
 * @brief Итерация обновления состояния интегратора
 *
 * @param input - Вход
 * @param dt - Временной шаг
 * @return Выход
 */
float Integrator::update(float input, float dt) {
    _state = _state + (_prev_in + input) * dt / 2;
    _prev_in = input;
    return _state;
}