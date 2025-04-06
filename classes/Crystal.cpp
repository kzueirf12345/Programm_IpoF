#include "headers/Crystal.h"

/////////////////////////////////////////////////////////
//// Construct
/////////////////////////////////////////////////////////

// Crystal::Crystal(const Cell &cell, long long crystalSizeX, long long crystalSizeY,
//                  long long crystalSizeZ, double boundaryThickness)
//     : cell(cell),
//       crystalSizeX(crystalSizeX),
//       crystalSizeY(crystalSizeY),
//       crystalSizeZ(crystalSizeZ),
//       boundaryThickness(boundaryThickness) {
//     CreateModel();
//     UpdateModelVerle();
// }

void Crystal::Create() {
    CreateModel();
    UpdateModelVerle();
}

void Crystal::CreateModel() {
    std::unordered_set<Coordinate> st;
    for (long long x = 0; x < crystalSizeX; ++x) {
        for (long long y = 0; y < crystalSizeY; ++y) {
            for (long long z = 0; z < crystalSizeZ; ++z) {
                for (const auto &coor : cell.CoordinatesVec()) {
                    const Coordinate temp_coor(coor.x + x * cell.XSize(), coor.y + y * cell.YSize(),
                                               coor.z + z * cell.ZSize());
                    if (st.find(temp_coor) == st.end()) {
                        model.push_back(Atom(temp_coor));
                        PguTranslate(temp_coor, st);
                        st.insert(temp_coor);
                    }
                }
            }
        }
    }
}

void Crystal::PguTranslate(const Coordinate &coor, std::unordered_set<Coordinate> &st) {
    const double x_limit = crystalSizeX * cell.XSize();
    const double y_limit = crystalSizeY * cell.YSize();
    const double z_limit = crystalSizeZ * cell.ZSize();
    // x
    Coordinate temp_coor(coor);
    if (coor.x <= boundaryThickness) {
        temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y, coor.z));
        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
        // y
        if (coor.y <= boundaryThickness) {
            temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y + y_limit, coor.z));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
            // z
            if (coor.z <= boundaryThickness) {
                temp_coor =
                    std::move(Coordinate(coor.x + x_limit, coor.y + y_limit, coor.z + z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
            if (z_limit - boundaryThickness <= coor.z) {
                temp_coor =
                    std::move(Coordinate(coor.x + x_limit, coor.y + y_limit, coor.z - z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
        }
        if (y_limit - boundaryThickness <= coor.y) {
            temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y - y_limit, coor.z));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
            // z
            if (coor.z <= boundaryThickness) {
                temp_coor =
                    std::move(Coordinate(coor.x + x_limit, coor.y - y_limit, coor.z + z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
            if (z_limit - boundaryThickness <= coor.z) {
                temp_coor =
                    std::move(Coordinate(coor.x + x_limit, coor.y - y_limit, coor.z - z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
        }

        temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y, coor.z));

        // z
        if (coor.z <= boundaryThickness) {
            temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y, coor.z + z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
        if (z_limit - boundaryThickness <= coor.z) {
            temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y, coor.z - z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
    }
    if (x_limit - boundaryThickness <= coor.x) {
        temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y, coor.z));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }

        // y
        if (coor.y <= boundaryThickness) {
            temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y + y_limit, coor.z));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }

            // z
            if (coor.z <= boundaryThickness) {
                temp_coor =
                    std::move(Coordinate(coor.x - x_limit, coor.y + y_limit, coor.z + z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
            if (z_limit - boundaryThickness <= coor.z) {
                temp_coor =
                    std::move(Coordinate(coor.x - x_limit, coor.y + y_limit, coor.z - z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
        }
        if (y_limit - boundaryThickness <= coor.y) {
            temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y - y_limit, coor.z));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }

            // z
            if (coor.z <= boundaryThickness) {
                temp_coor =
                    std::move(Coordinate(coor.x - x_limit, coor.y - y_limit, coor.z + z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
            if (z_limit - boundaryThickness <= coor.z) {
                temp_coor =
                    std::move(Coordinate(coor.x - x_limit, coor.y - y_limit, coor.z - z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
        }

        temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y, coor.z));

        // z
        if (coor.z <= boundaryThickness) {
            temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y, coor.z + z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
        if (z_limit - boundaryThickness <= coor.z) {
            temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y, coor.z - z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
    }

    // y
    if (coor.y <= boundaryThickness) {
        temp_coor = std::move(Coordinate(coor.x, coor.y + y_limit, coor.z));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
        // z
        if (coor.z <= boundaryThickness) {
            temp_coor = std::move(Coordinate(coor.x, coor.y + y_limit, coor.z + z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
        if (z_limit - boundaryThickness <= coor.z) {
            temp_coor = std::move(Coordinate(coor.x, coor.y + y_limit, coor.z - z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
    }
    if (y_limit - boundaryThickness <= coor.y) {
        temp_coor = std::move(Coordinate(coor.x, coor.y - y_limit, coor.z));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
        // z
        if (coor.z <= boundaryThickness) {
            temp_coor = std::move(Coordinate(coor.x, coor.y - y_limit, coor.z + z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
        if (z_limit - boundaryThickness <= coor.z) {
            temp_coor = std::move(Coordinate(coor.x, coor.y - y_limit, coor.z - z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
    }

    // z
    if (coor.z <= boundaryThickness) {
        temp_coor = std::move(Coordinate(coor.x, coor.y, coor.z + z_limit));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
    }
    if (z_limit - boundaryThickness <= coor.z) {
        temp_coor = std::move(Coordinate(coor.x, coor.y, coor.z - z_limit));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
    }
}

void Crystal::UpdateModelVerle() {
    for (unsigned i = 1; i <= numCores; ++i) {
        std::future<void> th =
            std::async(std::launch::async, &Crystal::UpdateModelVerleTh, this, i);
    }
}
void Crystal::UpdateModelVerleTh(unsigned num) {
    const size_t sz = model.size() / numCores;
    const size_t start = sz * (num - 1), end = (num == numCores ? model.size() : num * sz);
    for (size_t i = start; i < end; ++i) {
        model[i].Verle().clear();
        FillVerle(model[i]);
    }
}
void Crystal::FillVerle(Atom &atom) {
    const Coordinate coor = atom.Coor();
    for (size_t i = 0; i < model.size(); ++i) {
        if (Distance(coor, model[i].Coor()) < verleRadius && coor != model[i].Coor()) {
            atom.Verle().push_back(model[i].Coor());
        }
    }
    for (size_t i = 0; i < pgu.size(); ++i) {
        if (Distance(coor, pgu[i]) < verleRadius && coor != pgu[i]) {
            atom.Verle().push_back(pgu[i]);
        }
    }
}

/////////////////////////////////////////////////////////
//// Edit
/////////////////////////////////////////////////////////

void Crystal::Erase(size_t index) {
    if (std::is_sorted(model.begin(), model.end())) {
        model.erase(std::lower_bound(model.begin(), model.end(), model[index]));
    } else {
        model.erase(std::find(model.begin(), model.end(), model[index]));
    }
    UpdateModelVerle();
}
void Crystal::Insert(Coordinate coor)  // TODO check in set
{
    model.push_back(Atom(coor));
    UpdateModelVerle();
}
void Crystal::Offset(size_t index, Coordinate vector) {
    if (std::is_sorted(model.begin(), model.end())) {
        std::lower_bound(model.begin(), model.end(), model[index])->Coor() += vector;
    } else {
        std::find(model.begin(), model.end(), model[index])->Coor() += vector;
    }
    UpdateModelVerle();
}

/////////////////////////////////////////////////////////
//// Formuls
/////////////////////////////////////////////////////////

double Crystal::Potential(double distance) const noexcept {
    const double x = (1 - exp(-widthPotential * (distance - equilibriumDistance)));
    return depthPotential * (1 - x) * (1 - x);
}
double Crystal::Forse(double distance) const noexcept {
    return 2 * widthPotential * depthPotential *
           (exp(-2. * widthPotential * (distance - equilibriumDistance) -
                exp(-widthPotential * (distance - equilibriumDistance))));
}
double Crystal::Flow(double distance) const noexcept { return Forse(distance) / distance; }

double Crystal::SumOfPotential(const Atom &atom) noexcept {
    double sum = 0;
    for (const Atom &other_atom : model) {
        sum += Potential(Distance(atom.Coor(), other_atom.Coor()));
    }
    for (const Coordinate &other_atom : pgu) {
        sum += Potential(Distance(atom.Coor(), other_atom));
    }
    return sum;
}
Coordinate Crystal::SumOfFlows(const Atom &atom) const noexcept {
    Coordinate sum;
    for (const Coordinate &other_atom : atom.Verle()) {
        sum += (atom.Coor() - other_atom) * Flow(Distance(atom.Coor(), other_atom));
    }
    return sum;
}

/////////////////////////////////////////////////////////
//// Gradient
/////////////////////////////////////////////////////////

void Crystal::Modeling() {
    std::vector<Atom> cur_model(model);
    for (size_t i = 0; i < countIterations; ++i) {
        std::vector<Atom> prev_model(std::move(cur_model));
        cur_model = model;
        for (size_t j = 0; j < cur_model.size(); ++j) {
            const Atom cur_position(cur_model[j]);
            const Atom prev_position(prev_model[j]);

            const Coordinate acceleration = SumOfFlows(cur_position) / atomicMass;
            model[j].Coor() = cur_position.Coor() * 2. - prev_position.Coor() +
                              acceleration * timeStep * timeStep;
        }

        UpdateModelVerle();

        simulationTime += timeStep;
    }
}

double Crystal::Energy() noexcept {
    return 0.5 * depthPotential * SumOfPotential(model[model.size() / 2]);
}

/////////////////////////////////////////////////////////
//// Sets
/////////////////////////////////////////////////////////

void Crystal::setMaterialParameters(double depthPotential, double stiffness,
                                    double equilibriumDistance, double atomicMass) noexcept {
    this->depthPotential = depthPotential * EV_TO_G * G_TO_MY * 1e-3;
    this->stiffness = stiffness * KG_TO_AEM * 1e-4;
    this->equilibriumDistance = equilibriumDistance;
    this->atomicMass = atomicMass;
    this->widthPotential = std::sqrt(stiffness / (2 * depthPotential));
}

void Crystal::setElementaryCell(double cellSizeX, double cellSizeY, double cellSizeZ,
                                std::vector<Coordinate> atomicCoordinates) {
    this->cell = Cell(std::move(atomicCoordinates), cellSizeX, cellSizeY, cellSizeZ);
}

void Crystal::setCrystalSize(int crystalSizeX, int crystalSizeY, int crystalSizeZ) noexcept {
    this->crystalSizeX = crystalSizeX;
    this->crystalSizeY = crystalSizeY;
    this->crystalSizeZ = crystalSizeZ;
}

void Crystal::setSimulationParameters(double boundaryThickness, double verleRadius, double timeStep,
                                      double simulationTime, int numCores) noexcept {
    this->boundaryThickness = boundaryThickness;
    this->verleRadius = verleRadius;
    this->timeStep = timeStep;
    this->simulationTime = 0;
    this->numCores = numCores;
    this->countIterations = simulationTime / timeStep;
}

void Crystal::displayParameters(std::ostream &out) {
    out << "Параметры кристалла:" << std::endl;
    out << "Глубина потенциальной ямы: " << depthPotential / (EV_TO_G * G_TO_MY * 1e-3) << " эВ"
        << std::endl;
    out << "Жесткость связи: " << stiffness / (KG_TO_AEM * 1e-4) << " A^-1" << std::endl;
    out << "Равновесное расстояние: " << equilibriumDistance << " A" << std::endl;
    out << "Атомная масса: " << atomicMass << " эВ" << std::endl;
    out << "Размер кристалла по осям x, y, z: " << crystalSizeX << ", " << crystalSizeY << ", "
        << crystalSizeZ << std::endl;
    out << "Толщина граничного слоя: " << boundaryThickness << " A" << std::endl;
    out << "Радиус Верле: " << verleRadius << " A" << std::endl;
    out << "Временной шаг: " << timeStep << " фс" << std::endl;
    out << "Время симуляции: " << simulationTime << " фс" << std::endl;
    out << "Количество CPU ядер: " << numCores << std::endl;
}

void Crystal::displayModelAtoms(std::ostream &out) {
    for (size_t i = 0; i < model.size(); ++i) {
        out << model[i].Coor().x << " " << model[i].Coor().y << " " << model[i].Coor().z
            << std::endl;
    }
}

void Crystal::displayPguAtoms(std::ostream &out) {
    for (size_t i = 0; i < pgu.size(); ++i) {
        out << pgu[i].x << " " << pgu[i].y << " " << pgu[i].z << std::endl;
    }
}
