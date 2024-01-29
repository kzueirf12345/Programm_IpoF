#include "headers/Crystal.h"

Crystal::Crystal(const Cell &cell, long long x_size, long long y_size, long long z_size,
                 double pgu_size)
    : cell(cell), x_size(x_size), y_size(y_size), z_size(z_size), pgu_size(pgu_size) {
    CreateModel();
    UpdateModelVerle();
}

void Crystal::CreateModel() {
    std::unordered_set<Coordinate> st;
    for (long long x = 0; x < x_size; ++x) {
        for (long long y = 0; y < y_size; ++y) {
            for (long long z = 0; z < z_size; ++z) {
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
    const double x_limit = XSize() * cell.XSize();
    const double y_limit = YSize() * cell.YSize();
    const double z_limit = ZSize() * cell.ZSize();
    // x
    Coordinate temp_coor(coor);
    if (coor.x <= pgu_size) {
        temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y, coor.z));
        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
        // y
        if (coor.y <= pgu_size) {
            temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y + y_limit, coor.z));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
            // z
            if (coor.z <= pgu_size) {
                temp_coor =
                    std::move(Coordinate(coor.x + x_limit, coor.y + y_limit, coor.z + z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
            if (z_limit - pgu_size <= coor.z) {
                temp_coor =
                    std::move(Coordinate(coor.x + x_limit, coor.y + y_limit, coor.z - z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
        }
        if (y_limit - pgu_size <= coor.y) {
            temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y - y_limit, coor.z));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
            // z
            if (coor.z <= pgu_size) {
                temp_coor =
                    std::move(Coordinate(coor.x + x_limit, coor.y - y_limit, coor.z + z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
            if (z_limit - pgu_size <= coor.z) {
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
        if (coor.z <= pgu_size) {
            temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y, coor.z + z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
        if (z_limit - pgu_size <= coor.z) {
            temp_coor = std::move(Coordinate(coor.x + x_limit, coor.y, coor.z - z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
    }
    if (x_limit - pgu_size <= coor.x) {
        temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y, coor.z));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }

        // y
        if (coor.y <= pgu_size) {
            temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y + y_limit, coor.z));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }

            // z
            if (coor.z <= pgu_size) {
                temp_coor =
                    std::move(Coordinate(coor.x - x_limit, coor.y + y_limit, coor.z + z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
            if (z_limit - pgu_size <= coor.z) {
                temp_coor =
                    std::move(Coordinate(coor.x - x_limit, coor.y + y_limit, coor.z - z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
        }
        if (y_limit - pgu_size <= coor.y) {
            temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y - y_limit, coor.z));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }

            // z
            if (coor.z <= pgu_size) {
                temp_coor =
                    std::move(Coordinate(coor.x - x_limit, coor.y - y_limit, coor.z + z_limit));

                if (st.find(temp_coor) == st.end()) {
                    pgu.push_back(temp_coor);
                    st.insert(temp_coor);
                }
            }
            if (z_limit - pgu_size <= coor.z) {
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
        if (coor.z <= pgu_size) {
            temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y, coor.z + z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
        if (z_limit - pgu_size <= coor.z) {
            temp_coor = std::move(Coordinate(coor.x - x_limit, coor.y, coor.z - z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
    }

    // y
    if (coor.y <= pgu_size) {
        temp_coor = std::move(Coordinate(coor.x, coor.y + y_limit, coor.z));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
        // z
        if (coor.z <= pgu_size) {
            temp_coor = std::move(Coordinate(coor.x, coor.y + y_limit, coor.z + z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
        if (z_limit - pgu_size <= coor.z) {
            temp_coor = std::move(Coordinate(coor.x, coor.y + y_limit, coor.z - z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
    }
    if (y_limit - pgu_size <= coor.y) {
        temp_coor = std::move(Coordinate(coor.x, coor.y - y_limit, coor.z));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
        // z
        if (coor.z <= pgu_size) {
            temp_coor = std::move(Coordinate(coor.x, coor.y - y_limit, coor.z + z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
        if (z_limit - pgu_size <= coor.z) {
            temp_coor = std::move(Coordinate(coor.x, coor.y - y_limit, coor.z - z_limit));

            if (st.find(temp_coor) == st.end()) {
                pgu.push_back(temp_coor);
                st.insert(temp_coor);
            }
        }
    }

    // z
    if (coor.z <= pgu_size) {
        temp_coor = std::move(Coordinate(coor.x, coor.y, coor.z + z_limit));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
    }
    if (z_limit - pgu_size <= coor.z) {
        temp_coor = std::move(Coordinate(coor.x, coor.y, coor.z - z_limit));

        if (st.find(temp_coor) == st.end()) {
            pgu.push_back(temp_coor);
            st.insert(temp_coor);
        }
    }
}

void Crystal::UpdateModelVerle() {
    for (unsigned i = 1; i <= CPU_CNT; ++i) {
        std::future<void> th =
            std::async(std::launch::async, &Crystal::UpdateModelVerleTh, this, i);
    }
}
void Crystal::UpdateModelVerleTh(unsigned num) {
    const size_t sz = model.size() / CPU_CNT;
    const size_t start = sz * (num - 1), end = (num == CPU_CNT ? model.size() : num * sz);
    for (size_t i = start; i < end; ++i) {
        model[i].Verle().clear();
        FillVerle(model[i]);
    }
}
void Crystal::FillVerle(Atom &atom) {
    const Coordinate coor = atom.Coor();
    for (size_t i = 0; i < model.size(); ++i) {
        if (Distance(coor, model[i].Coor()) < R_VERLE && coor != model[i].Coor()) {
            atom.Verle().push_back(model[i].Coor());
        }
    }
    for (size_t i = 0; i < pgu.size(); ++i) {
        if (Distance(coor, pgu[i]) < R_VERLE && coor != pgu[i]) {
            atom.Verle().push_back(pgu[i]);
        }
    }
}

/////////////////////////////////////////////////////////
//// Gradient
/////////////////////////////////////////////////////////

void Crystal::Modeling(size_t iterations_cnt) {
    std::vector<Atom> cur_model(model);
    long long freq = 5;  // simple number
    for (size_t i = 0; i < iterations_cnt; ++i) {
        std::vector<Atom> prev_model(std::move(cur_model));
        cur_model = model;
        for (size_t j = 0; j < cur_model.size(); ++j) {
            const Atom cur_position(cur_model[j]);
            const Atom prev_position(prev_model[j]);

            const Coordinate acceleration = cur_position.SumOfFlows() / MASS;
            model[j].Coor() =
                cur_position.Coor() * 2. - prev_position.Coor() + acceleration * TAU * TAU;
        }

        // update verle
        if (i % freq == 0) {
            UpdateModelVerle();
        }
        time += TAU;
    }
}

double Crystal::Energy() noexcept {
    return 0.5 * D *
           AtomSumOfPotential(model[model.size() / 2]);
}

double Crystal::AtomSumOfPotential(const Atom &atom) noexcept {
    double sum = 0;
    for (const Atom &other_atom : model) {
        sum += Potential(Distance(atom.Coor(), other_atom.Coor()));
    }
    for (const Coordinate &other_atom : pgu) {
        sum += Potential(Distance(atom.Coor(), other_atom));
    }
    return sum;
}