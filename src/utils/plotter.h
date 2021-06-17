//
// Created by jsier on 15/06/2021.
//

#ifndef CLUSTERING_PLOTTER_H
#define CLUSTERING_PLOTTER_H

#include <vector>
#include <optional>
#include "../math/vector.h"

class Plotter {
public:
    struct Range {
        double xmin = -1.0;
        double xmax = +1.0;
        double ymin = -1.0;
        double ymax = +1.0;
        [[nodiscard]] double xlen() const { return xmax - xmin; };
        [[nodiscard]] double ylen() const { return ymax - ymin; };
        [[nodiscard]] double fit_xrange(double x) const { return (x - xmin) / xlen(); }
        [[nodiscard]] double fit_yrange(double y) const { return (y - ymin) / ylen(); }
    };

    Plotter();
    Plotter(uint32_t width, uint32_t height);
    Plotter(uint32_t width, uint32_t height, Range range);
    ~Plotter() = default;
    void clean();
    void draw();

    template<class VectorType>
    void plot_vectors(const std::vector<VectorType>& vectors, std::optional<char> symbol = std::nullopt);

private:
    Range range{};
    uint32_t width = 79;
    uint32_t height = 15;
    char plot_symbol = 'a';
    std::vector<char> matrix;

    char get_next_symbol();
};

template<class VectorType>
void Plotter::plot_vectors(const std::vector<VectorType> &vectors, std::optional<char> symbol) {
    static_assert(("Only Vector2D is supported in the plotter for now", std::is_same<VectorType, Vector2D>::value));

    char ch_symbol = symbol.has_value() ? symbol.value() : get_next_symbol();
    for (const auto& vector : vectors) {
        int x = int(range.fit_xrange(vector[0]) * width);
        int y = int(range.fit_yrange(vector[1]) * height); // Invert height, top row is 0
        if (x < width && x >= 0 && y < height && y >= 0) {
            matrix[(height - y - 1) * width + x] = ch_symbol;  // Todo: visual indicator when two symbols at the same spot
        }
    }
}


#endif //CLUSTERING_PLOTTER_H
