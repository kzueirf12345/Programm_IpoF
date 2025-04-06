#pragma once

#include <future>
#include <thread>
#include <unordered_set>

#include "Atom.h"
#include "Cell.h"

class Crystal {
   public:
    Crystal() = default;
    // Crystal(const Cell& cell, long long size, double pgu_size)
    //     : Crystal(cell, size, size, size, pgu_size) {}
    // Crystal(const Cell& cell, long long x_size, long long y_size, long long z_size,
    //         double pgu_size);

    void Create();

    void Erase(size_t index);
    void Insert(Coordinate coor);
    void Offset(size_t index, Coordinate vector);

    void Modeling();
    [[nodiscard]] double Energy() noexcept;

    void UpdateModelVerle();

    double Potential(double distance) const noexcept;
    double Flow(double distance) const noexcept;
    double Forse(double distance) const noexcept;

    void setMaterialParameters(double depthPotential, double stiffness, double equilibriumDistance,
                               double atomicMass) noexcept;
    void setElementaryCell(double cellSizeX, double cellSizeY, double cellSizeZ,
                           std::vector<Coordinate> atomicCoordinates);
    void setCrystalSize(int crystalSizeX, int crystalSizeY, int crystalSizeZ) noexcept;
    void setSimulationParameters(double boundaryThickness, double verleRadius, double timeStep,
                                 double simulationTime, int numCores) noexcept;
    void displayParameters(std::ostream& out);
    void displayModelAtoms(std::ostream &out);
    void displayPguAtoms(std::ostream& out);

    short getCrystalSizeX() const noexcept { return crystalSizeX; }
    short& getCrystalSizeX() noexcept { return crystalSizeX; }
    short getCrystalSizeY() const noexcept { return crystalSizeY; }
    short& getCrystalSizeY() noexcept { return crystalSizeY; }
    short getCrystalSizeZ() const noexcept { return crystalSizeZ; }
    short& getCrystalSizeZ() noexcept { return crystalSizeZ; }
    double getBoundaryThickness() const noexcept { return boundaryThickness; }
    double& getBoundaryThickness() noexcept { return boundaryThickness; }
    double getVerleRadius() const noexcept { return verleRadius; }
    double& getVerleRadius() noexcept { return verleRadius; }
    double getTimeStep() const noexcept { return timeStep; }
    double& getTimeStep() noexcept { return timeStep; }
    double getSimulationTime() const noexcept { return simulationTime; }
    double& getSimulationTime() noexcept { return simulationTime; }
    short getNumCores() const noexcept { return numCores; }
    short& getNumCores() noexcept { return numCores; }

    double getDepthPotential() const noexcept { return depthPotential; }
    double& getDepthPotential() noexcept { return depthPotential; }
    double getStiffness() const noexcept { return stiffness; }
    double& getStiffness() noexcept { return stiffness; }
    double getEquilibriumDistance() const noexcept { return equilibriumDistance; }
    double& getEquilibriumDistance() noexcept { return equilibriumDistance; }
    double getAtomicMass() const noexcept { return atomicMass; }
    double& getAtomicMass() noexcept { return atomicMass; }
    double getWidthPotential() const noexcept { return widthPotential; }

    [[nodiscard]] const Cell& ElementaryCell() const noexcept { return cell; }
    [[nodiscard]] Cell& ElementaryCell() noexcept { return cell; }
    [[nodiscard]] const std::vector<Atom>& Model() const noexcept { return model; }
    [[nodiscard]] std::vector<Atom>& Model() noexcept { return model; }
    [[nodiscard]] const std::vector<Coordinate>& Pgu() const noexcept { return pgu; }
    [[nodiscard]] std::vector<Coordinate>& Pgu() noexcept { return pgu; }

   private:
    short crystalSizeX;
    short crystalSizeY;
    short crystalSizeZ;
    double boundaryThickness;  // 3 * EQUAL_DIST // angstream
    double verleRadius;        // 2 * EQUAL_DIST // angstream
    double timeStep;           // 0.1 // fs
    double simulationTime;     // 100 // fs
    short numCores;            // 8
    long long countIterations;

    double depthPotential;       // 5. * EV_TO_G * G_TO_MY * 1e-3 // aem * angstream^2 / fs^2
    double stiffness;            // 7.7 * KG_TO_AEM * 1e-4 // aem * angstream^2 / fs^2
    double equilibriumDistance;  // 3.615 // angstream
    double atomicMass;           // 63.546 // aem
    double widthPotential;       // std::sqrt(k / (2 * D))

    Cell cell;

    std::vector<Atom> model;
    std::vector<Coordinate> pgu;

    void PguTranslate(const Coordinate& coor, std::unordered_set<Coordinate>& st);

    inline void CreateModel();

    void UpdateModelVerleTh(unsigned num);
    inline void FillVerle(Atom& coor);

    inline double SumOfPotential(const Atom& coor) noexcept;
    Coordinate SumOfFlows(const Atom& atom) const noexcept;
};