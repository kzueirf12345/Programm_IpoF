#include "headers/UserInterface.h"

void UserInterface::getMaterialParameters() {
    double depth, stiffness, equilibriumDistance, atomicMass;
    std::cout << "Введите глубину потенциальной ямы (эВ): ";
    std::cin >> depth;
    std::cout << "Введите жесткость связи (A^-1): ";
    std::cin >> stiffness;
    std::cout << "Введите равновесное расстояние (A): ";
    std::cin >> equilibriumDistance;
    std::cout << "Введите атомную массу(aem): ";
    std::cin >> atomicMass;

    crystal->setMaterialParameters(depth, stiffness, equilibriumDistance, atomicMass);
}

void UserInterface::getElemetaryCell() {
    double cellSizeX, cellSizeY, cellSizeZ;
    std::cout << "Введите размеры элементарной ячейки по осям x, y и z (A):	";
    std::cin >> cellSizeX >> cellSizeY >> cellSizeZ;
    long long numAtoms;
    std::cout << "Введите количество атомов в элементарной ячейке: ";
    std::cin >> numAtoms;
    std::vector<Coordinate> atomicCoordinates;
    for (int i = 0; i < numAtoms; i++) {
        double x, y, z;
        std::cout << "Введите координаты атома (A) " << i + 1 << ": ";
        std::cin >> x >> y >> z;
        atomicCoordinates.push_back(Coordinate(x, y, z));
    }

    crystal->setElementaryCell(cellSizeX, cellSizeY, cellSizeZ, atomicCoordinates);
}

void UserInterface::getCrystalSize() {
    short crystalSizeX, crystalSizeY, crystalSizeZ;
    std::cout << "Введите размер кристалла по осям x, y и z (количество дублирований элементарной "
                 "ячейки): ";
    std::cin >> crystalSizeX >> crystalSizeY >> crystalSizeZ;
    crystal->setCrystalSize(crystalSizeX, crystalSizeY, crystalSizeZ);
}

void UserInterface::getSimulationParameters() {
    double boundaryThickness, verletRadius, timeStep, simulationTime;
    short numCores;

    do {
        std::cout << "Введите толщину граничного слоя (A): ";
        std::cin >> boundaryThickness;
    } while (boundaryThickness < 2 * crystal->getEquilibriumDistance());

    do {
        std::cout << "Введите радиус Верле (A): ";
        std::cin >> verletRadius;
    } while (verletRadius < 2 * crystal->getEquilibriumDistance());

    std::cout << "Введите временной шаг (фс): ";
    std::cin >> timeStep;
    std::cout << "Введите время симуляции (фс): ";
    std::cin >> simulationTime;
    std::cout << "Введите количество CPU ядер для использования: ";
    std::cin >> numCores;

    crystal->setSimulationParameters(boundaryThickness, verletRadius, timeStep, simulationTime,
                                     numCores);
}

void UserInterface::EditCrystal() {
    std::cout << "Редактирование кристалла:" << std::endl;
    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Удалить атом" << std::endl;
        std::cout << "2. Добавить атом" << std::endl;
        std::cout << "3. Сдвинуть атом" << std::endl;
        std::cout << "4. Выйти" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            size_t index;
            std::cout << "Введите индекс атома для удаления: ";
            std::cin >> index;
            crystal->Erase(index);
        } else if (choice == 2) {
            Coordinate coor;
            std::cout << "Введите координаты атома для добавления (A): ";
            std::cin >> coor.x >> coor.y >> coor.z;
            crystal->Insert(coor);
        } else if (choice == 3) {
            size_t index;
            Coordinate vector;
            std::cout << "Введите индекс атома и вектор смещения (A): ";
            std::cin >> index >> vector.x >> vector.y >> vector.z;
            crystal->Offset(index, vector);
        } else if (choice == 4) {
            std::cout << "Выход из режима редактирования" << std::endl;
            break;
        } else {
            std::cout << "Неверный выбор, попробуйте снова" << std::endl;
        }
    }
}

void UserInterface::GetOutput() {
    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Вывести данные о crystal в консоль" << std::endl;
        std::cout << "2. Вывести данные о crystal в файл" << std::endl;
        std::cout << "3. Вывести координаты атомов в консоль" << std::endl;
        std::cout << "4. Вывести координаты атомов в файл" << std::endl;
        std::cout << "5. Выйти" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            crystal->displayParameters(std::cout);
        } else if (choice == 2) {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;

            std::ofstream file(filename);
            if (file.is_open()) {
                crystal->displayParameters(file);  // Вывод данных о crystal в файл
                file.close();
            } else {
                std::cout << "Ошибка открытия файла" << std::endl;
            }
        } else if (choice == 3) {
            std::cout << "Выберите опцию вывода координат атомов:" << std::endl;
            std::cout << "1. Координаты моделируемой области" << std::endl;
            std::cout << "2. Координаты переодических граничных условий" << std::endl;
            std::cout << "3. Координаты моделируемой области и переодических граничных условий"
                      << std::endl;

            int atomsChoice;
            std::cin >> atomsChoice;

            if (atomsChoice == 1) {
                crystal->displayModelAtoms(std::cout);
            } else if (atomsChoice == 2) {
                crystal->displayPguAtoms(std::cout);
            } else if (atomsChoice == 3) {
                crystal->displayModelAtoms(std::cout);
                std::cout << std::endl;
                crystal->displayPguAtoms(std::cout);
            } else {
                std::cout << "Неверная опция вывода координат атомов" << std::endl;
            }
        } else if (choice == 4) {
            std::cout << "Выберите опцию вывода координат атомов:" << std::endl;
            std::cout << "1. Координаты моделируемой области" << std::endl;
            std::cout << "2. Координаты переодических граничных условий" << std::endl;
            std::cout << "3. Координаты моделируемой области и переодических граничных условий"
                      << std::endl;

            int atomsChoice;
            std::cin >> atomsChoice;

            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;

            std::ofstream fout(filename);
            if (fout.is_open()) {
                if (atomsChoice == 1) {
                    crystal->displayModelAtoms(fout);
                } else if (atomsChoice == 2) {
                    crystal->displayPguAtoms(fout);
                } else if (atomsChoice == 3) {
                    crystal->displayModelAtoms(fout);
                    crystal->displayPguAtoms(fout);
                } else {
                    std::cout << "Неверная опция вывода координат атомов" << std::endl;
                }
                fout.close();
            } else {
                std::cout << "Ошибка открытия файла" << std::endl;
            }
        } else if (choice == 5) {
            std::cout << "Выход из режима вывода" << std::endl;
            break;
        } else {
            std::cout << "Неверный выбор" << std::endl;
        }
    }
}