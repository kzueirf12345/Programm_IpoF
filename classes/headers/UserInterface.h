#pragma once
#include <fstream>

#include "Coordinate.h"
#include "Crystal.h"

class UserInterface {
   public:
    Crystal* crystal;

    UserInterface(Crystal* crystal) : crystal(crystal) {}

    void getMaterialParameters();
    void getElemetaryCell();
    void getCrystalSize();
    void getSimulationParameters();

    void EditCrystal();

    void GetOutput();
};
