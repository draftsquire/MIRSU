//
// Created by drafty on 28.09.2024.
//

#ifndef MIRSU_STEP_H
#define MIRSU_STEP_H

/**
 * @brief Класс, реализующий функционал блока Step из Simulink
 */
class Step {
public:
    /**
     *
     * @param init_time Начальное значение
     * @param step_time Время "срабатывания" единичного воздействия
     * @param step_value Множитель единичного воздействия
     */
    Step(float init_value, float step_time, float step_value) {
        _init_value = init_value;
        _step_time = step_time;
        _step_value = step_value;
    };

    /**
     * @brief Получить значение блока для заданного времени
     *
     * @param t - Время, с
     * @return Значение выхода блока для времени t
     */
    float get_time_output(float t) {
        if (t == 0) return 0;
        if (t >= _step_time) {
            return _step_value;
        } else {
            return _init_value;
        }
    }
private:
    float _init_value = 0.f;
    float _step_time = 0.f;
    float _step_value = 1.f;

};

#endif //MIRSU_STEP_H
