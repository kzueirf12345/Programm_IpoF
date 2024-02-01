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

    crystal.Offset(crystal.Model().size() / 4,
                   Coordinate(EQUAL_DIST / 4, EQUAL_DIST / 4, EQUAL_DIST / 4));

    std::ofstream fout("model.txt");
    for (size_t i = 0; i < crystal.Model().size(); ++i) {
        fout << crystal.Model()[i].Coor().x << " " << crystal.Model()[i].Coor().y << " "
             << crystal.Model()[i].Coor().z << std::endl;
    }
    fout.close();
    fout.open("pgu.txt");
    for (size_t i = 0; i < crystal.Pgu().size(); ++i) {
        fout << crystal.Pgu()[i].x << " " << crystal.Pgu()[i].y << " " << crystal.Pgu()[i].z
             << std::endl;
    }
    fout.close();
    
    crystal.Modeling(ITERATIONS_CNT);

    const double second_energy = crystal.Energy();

    std::cout << "time of modeling\t" << crystal.Time() << " фс" << std::endl;
    std::cout << "first energy\t" << first_energy << std::endl;
    std::cout << "second_energy\t" << second_energy << std::endl;
    std::cout << "difference\t" << first_energy - second_energy << std::endl;

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);
    return 0;
}