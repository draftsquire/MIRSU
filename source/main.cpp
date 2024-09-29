#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <ControlObject3D.h>
#include <ControlObject3DDiscrete.h>
#include <util/csv.hpp>
#include <blocks/Step.h>
#include <fstream>
#define FIXED_STEP_SIZE (0.001)
int main() {
    /// \brief Непрерывная система
    float A_cont[3][3] = {{-3.f, -1.f, 0.f},
                          {-1.f, -2.f, -1.f},
                          {-0.f, -1.f, -2.f}};
    float B_cont[3] = {10.f,
                       0.f,
                       9.f};
    float C_cont[3] = {0.f, 1.f, 1.f};

    /// \brief Дискретная система, 5 Гц
    float A_disc_5_hz[3][3] = {{0.5606,   -0.1232,    0.0126},
                          {-0.1232,    0.6965,   -0.1358},
                          {0.0126,   -0.1358,    0.6838}};
    float B_disc_5_hz[3] = {1.5215,
                            -0.2847,
                            1.5020};
    float C_disc_5_hz[3] = {0, 1, 1};

    /// \brief Дискретная система, 25 Гц
    float A_disc_25_hz[3][3] = {{0.8876  , -0.0362 ,  0.0007},
                               {-0.0362 ,   0.9246,  -0.0369},
                               {0.0007  , -0.0369 ,  0.9239}};
    float B_disc_25_hz[3] = { 0.3771,
                             -0.0143,
                             0.3462};
    float C_disc_25_hz[3] = {0, 1, 1};

    /// \brief Дискретная система, 100 Гц
    float A_disc_100_hz[3][3] = {{0.9705, -0.0098,    0.0000},
                                {-0.0098,  0.9803,   -0.0098},
                                 {0.0000 ,-0.0098 ,   0.9802}};
    float B_disc_100_hz[3] = {0.0985,
                              -0.0009,
                              0.0891};
    float C_disc_100_hz[3] = {0, 1, 1};

    ControlObject3D ContinuousObject = ControlObject3D(A_cont, B_cont, C_cont);
    ControlObject3DDiscrete DiscreteObject5Hz = ControlObject3DDiscrete(A_disc_5_hz, B_disc_5_hz, C_cont);
    ControlObject3DDiscrete DiscreteObject25Hz = ControlObject3DDiscrete(A_disc_25_hz, B_disc_25_hz, C_cont);
    ControlObject3DDiscrete DiscreteObject100Hz = ControlObject3DDiscrete(A_disc_100_hz, B_disc_100_hz, C_cont);

    /// Создаём массив для хранения отсчётов времени

    /// @brief Время симуляции
    uint32_t simtime_sec = 7;
    /// @brief Шаг симуляции в степени -1
    uint32_t stepsize_inversed = 1000;
    uint32_t timeseries_size = simtime_sec * stepsize_inversed;

    float* timeseries = (float*) calloc(timeseries_size, sizeof(float));
    for (int i = 0; i < timeseries_size; i++) {
        timeseries[i] = FIXED_STEP_SIZE * i;
    }
    float* timeseries_5hz = (float*) calloc(5 * simtime_sec, sizeof(float));
    for (int i = 0; i < 5 * simtime_sec; i++) {
        timeseries_5hz[i] = 0.2 * i;
    }
    float* timeseries_25hz = (float*) calloc(25 * simtime_sec, sizeof(float));
    for (int i = 0; i < 25 * simtime_sec; i++) {
        timeseries_25hz[i] = 0.04 * i;
    }
    float* timeseries_100hz = (float*) calloc(100 * simtime_sec, sizeof(float));
    for (int i = 0; i < 100 * simtime_sec; i++) {
        timeseries_100hz[i] = 0.01 * i;
    }
    /// Создаём массивы для хранения выходов каждой из систем.
    float* cont_out = (float*) calloc(timeseries_size, sizeof(float));
    float* _5hz_out = (float*) calloc(5 * simtime_sec, sizeof(float));
    float* _25hz_out = (float*) calloc(25 * simtime_sec, sizeof(float));
    float* _100hz_out = (float*) calloc(100 * simtime_sec, sizeof(float));

    Step step = Step(0, 0, 1);

    /// Создаём потоки вывода для записи данных в csv файл
    std::ofstream cont_fout;
    std::ofstream _5hz_out_fout;
    std::ofstream _25hz_out_fout;
    std::ofstream _100hz_out_fout;
    cont_fout.open("cont.csv");
    _5hz_out_fout.open("5_hz.csv");
    _25hz_out_fout.open("25_hz.csv");
    _100hz_out_fout.open("100_hz.csv");

    auto cont_writer = csv::make_csv_writer(cont_fout);
    auto _5hz_writer = csv::make_csv_writer(_5hz_out_fout);
    auto _25hz_writer = csv::make_csv_writer(_25hz_out_fout);
    auto _100hz_writer = csv::make_csv_writer(_100hz_out_fout);
    csv::set_decimal_places(3);
    cont_writer << std::make_tuple("t", "y");
    _5hz_writer << std::make_tuple("t", "y");
    _25hz_writer << std::make_tuple("t", "y");
    _100hz_writer << std::make_tuple("t", "y");
    /// Проводим "симуляцию"
    for (int i = 0; i < timeseries_size; i++) {
        cont_out[i] = ContinuousObject.update(step.get_time_output(timeseries[i]), FIXED_STEP_SIZE);
        cont_writer << std::make_tuple(timeseries[i], cont_out[i]);
    }
    for (int i = 0; i < 5 * simtime_sec; i++) {
        _5hz_out[i] = DiscreteObject5Hz.update(step.get_time_output(timeseries_5hz[i]));
        _5hz_writer << std::make_tuple(timeseries_5hz[i], _5hz_out[i]);
    }
    for (int i = 0; i < 25 * simtime_sec; i++) {
        _25hz_out[i] = DiscreteObject25Hz.update(step.get_time_output(timeseries_25hz[i]));
        _25hz_writer << std::make_tuple(timeseries_25hz[i], _25hz_out[i]);
    }
    for (int i = 0; i < 100 * simtime_sec; i++) {
        _100hz_out[i] = DiscreteObject100Hz.update(step.get_time_output(timeseries_100hz[i]));
        _100hz_writer << std::make_tuple(timeseries_100hz[i], _100hz_out[i]);
    }
    cont_fout.close();
    _5hz_out_fout.close();
    _25hz_out_fout.close();
    _100hz_out_fout.close();
    std::cout << "It's done!" << std::endl;


    return 0;
}



