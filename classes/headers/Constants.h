#pragma once

#include <cmath>

constexpr double EV_TO_G = 1.60217733;        // * 1e-19
constexpr double KG_TO_AEM = 6.022136651675;  // * 1e26
constexpr double G_TO_MY = KG_TO_AEM;         // * 1e16

// constexpr long long CNT_CRYSTAL_CELL = 5;
// constexpr double EQUAL_DIST = 3.615;              // angstream
// constexpr double PGU_THICKNESS = 3 * EQUAL_DIST;  // angstream
// constexpr double R_VERLE = 2 * EQUAL_DIST;        // angstream
 
// constexpr double MASS = 63.546;                      // aem
// constexpr double D = 5. * EV_TO_G * G_TO_MY * 1e-3;  // aem * angstream^2 / fs^2
// constexpr double k = 7.7 * KG_TO_AEM * 1e-4;         // aem * angstream^2 / fs^2
// constexpr double ALPHA = std::sqrt(k / (2 * D));
// constexpr double TAU = 0.5;  // fs // 0.1

// constexpr unsigned CPU_CNT = 8;

// constexpr size_t ITERATIONS_CNT = 500;

/*
5
7.7
3.615
63.546
3.615 3.615 3.615
14
0 0 0
3.615 0 0
0 3.615 0
3.615 3.615 0
0 0 3.615
3.615 0 3.615
0 3.615 3.615
3.615 3.615 3.615
1.8075 1.8075 0
1.8075 0 1.8075
0 1.8075 1.8075
3.615 1.8075 1.8075
1.8075 3.615 1.8075
1.8075 1.8075 3.615
5 5 5
7.24
7.24
0.1
100
8
3
100
0.90375 0.90375 0.90375
4

*/