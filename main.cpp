#include <fstream>

#include "Crystal.h"

int main() {
    std::cin.tie(0);
    std::cout.tie(0);
    clock_t start = clock();

    Cell cell({Coordinate(0, 0, 0), Coordinate(EQUAL_DIST, 0, 0), Coordinate(0, EQUAL_DIST, 0),
               Coordinate(EQUAL_DIST, EQUAL_DIST, 0), Coordinate(0, 0, EQUAL_DIST),
               Coordinate(EQUAL_DIST, 0, EQUAL_DIST), Coordinate(0, EQUAL_DIST, EQUAL_DIST),
               Coordinate(EQUAL_DIST, EQUAL_DIST, EQUAL_DIST),
               Coordinate(EQUAL_DIST / 2, EQUAL_DIST / 2, 0),
               Coordinate(EQUAL_DIST / 2, 0, EQUAL_DIST / 2),
               Coordinate(0, EQUAL_DIST / 2, EQUAL_DIST / 2),
               Coordinate(EQUAL_DIST, EQUAL_DIST / 2, EQUAL_DIST / 2),
               Coordinate(EQUAL_DIST / 2, EQUAL_DIST, EQUAL_DIST / 2),
               Coordinate(EQUAL_DIST / 2, EQUAL_DIST / 2, EQUAL_DIST)},
              EQUAL_DIST);
    Crystal crystal(cell, 5, PGU_THICKNESS);

    const double first_energy = crystal.Energy();

    crystal.Model()[crystal.Model().size() / 4].Coor() += Coordinate(EQUAL_DIST / 4, EQUAL_DIST / 4, EQUAL_DIST / 4);
    crystal.Modeling(ITERATIONS_CNT);

    const double second_energy = crystal.Energy();

    std::cout << "time of modeling\t" << crystal.Time() << std::endl;
    std::cout << "first energy\t" << first_energy << std::endl;
    std::cout << "second_energy\t" << second_energy << std::endl;
    std::cout << "difference\t" << first_energy - second_energy << std::endl;

    std::ofstream fout("model.txt");

    for (size_t i = 0; i < crystal.Model().size() - 1; ++i) {
        fout << crystal.Model()[i].Coor().x << std::endl
             << crystal.Model()[i].Coor().y << std::endl
             << crystal.Model()[i].Coor().z << std::endl;
    }
    fout << crystal.Model()[crystal.Model().size() - 1].Coor().x << std::endl
         << crystal.Model()[crystal.Model().size() - 1].Coor().y << std::endl
         << crystal.Model()[crystal.Model().size() - 1].Coor().z;
    fout.close();

    fout.open("pgu.txt");
    for (size_t i = 0; i < crystal.Pgu().size() - 1; ++i) {
        fout << crystal.Pgu()[i].x << std::endl
             << crystal.Pgu()[i].y << std::endl
             << crystal.Pgu()[i].z << std::endl;
    }
    fout << crystal.Pgu()[crystal.Pgu().size() - 1].x << std::endl
         << crystal.Pgu()[crystal.Pgu().size() - 1].y << std::endl
         << crystal.Pgu()[crystal.Pgu().size() - 1].z;
    fout.close();

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);
    return 0;
}