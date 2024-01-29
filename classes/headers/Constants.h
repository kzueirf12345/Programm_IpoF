#pragma once

#include <cmath>

constexpr double EV_TO_G = 1.60217733;        // * 1e-19
constexpr double KG_TO_AEM = 6.022136651675;  // * 1e26
constexpr double G_TO_MY = KG_TO_AEM;         // * 1e16

constexpr long long CNT_CRYSTAL_CELL = 5;
constexpr double EQUAL_DIST = 3.615;              // angstream
constexpr double PGU_THICKNESS = 3 * EQUAL_DIST;  // angstream
constexpr double R_VERLE = 2 * EQUAL_DIST;        // angstream

constexpr double MASS = 63.546;                      // aem
constexpr double D = 5. * EV_TO_G * G_TO_MY * 1e-3;  // aem * andstream^2 / fs^2
constexpr double k = 7.7 * KG_TO_AEM * 1e-4;         // aem * andstream^2 / fs^2
constexpr double ALPHA = std::sqrt(k / (2 * D));
constexpr double TAU = 0.1;  // fs

constexpr unsigned CPU_CNT = 8;

constexpr size_t ITERATIONS_CNT = 2000;