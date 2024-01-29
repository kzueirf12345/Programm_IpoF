#pragma once

#include <future>
#include <thread>
#include <unordered_set>

#include "Atom.h"
#include "Cell.h"

class Crystal {
   public:
    Crystal() = default;
    Crystal(const Cell& cell, long long size, double pgu_size)
        : Crystal(cell, size, size, size, pgu_size) {}
    Crystal(const Cell& cell, long long x_size, long long y_size, long long z_size,
            double pgu_size);

    [[nodiscard]] const Cell& ElementaryCell() const { return cell; }
    [[nodiscard]] Cell& ElementaryCell() { return cell; }
    [[nodiscard]] long long XSize() const noexcept { return x_size; }
    [[nodiscard]] long long YSize() const noexcept { return y_size; }
    [[nodiscard]] long long ZSize() const noexcept { return z_size; }
    [[nodiscard]] double Time() const noexcept { return time; }
    [[nodiscard]] const std::vector<Atom>& Model() const noexcept { return model; }
    [[nodiscard]] std::vector<Atom>& Model() noexcept { return model; }
    [[nodiscard]] const std::vector<Coordinate>& Pgu() const noexcept { return pgu; }
    [[nodiscard]] std::vector<Coordinate>& Pgu() noexcept { return pgu; }

    void Modeling(size_t iterations_cnt);
    double Energy() noexcept;

   private:
    long long x_size, y_size, z_size;
    Cell cell;

    std::vector<Atom> model;
    std::vector<Coordinate> pgu;

    double pgu_size;
    void PguTranslate(const Coordinate& coor, std::unordered_set<Coordinate>& st);

    double time = 0;
    inline void CreateModel();

    void UpdateModelVerle();
    void UpdateModelVerleTh(unsigned num);
    inline void FillVerle(Atom& coor);

    inline double AtomSumOfPotential(const Atom& coor) noexcept;
};