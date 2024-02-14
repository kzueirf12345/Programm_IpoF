#include <fstream>

#include "UserInterface.h"

int main() {
    std::cin.tie(0);
    std::cout.tie(0);
    clock_t start = clock();

    Crystal crystal;
    UserInterface ui(&crystal);

    ui.getMaterialParameters();
    ui.getElemetaryCell();
    ui.getCrystalSize();
    ui.getSimulationParameters();

    // ui.displayParameters();

    crystal.Create();

    const double first_energy = crystal.Energy();

    ui.EditCrystal();

    std::cout << "Моделирование началось" <<std::endl;
    crystal.Modeling();
    std::cout << "Моделирование закончилось" << std::endl;

    const double second_energy = crystal.Energy();

    ui.GetOutput();

    std::cout << "time of modeling\t" << crystal.getSimulationTime() << " фс" << std::endl;
    std::cout << "first energy\t" << first_energy << std::endl;
    std::cout << "second_energy\t" << second_energy << std::endl;
    std::cout << "difference\t" << first_energy - second_energy << std::endl;

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);
    return 0;
}