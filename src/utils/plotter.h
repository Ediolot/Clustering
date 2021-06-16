//
// Created by jsier on 15/06/2021.
//

#ifndef CLUSTERING_PLOTTER_H
#define CLUSTERING_PLOTTER_H

#include <numeric>
#include <array>
#include <vector>
#include <tuple>
#include "../math/vector.h"

template<uint32_t width=79, uint32_t height=20>
class Plotter {
public:
    Plotter() = default;
    ~Plotter() = default;

    static const char AUTOMATIC_SYMBOL = '\0';

    template<class VectorType>
    void plot_vectors(const std::vector<VectorType>& vectors, double min, double max, char symbol=AUTOMATIC_SYMBOL) {
        static_assert(("Only Vector2D is supported in the plotter for now", std::is_same<VectorType, Vector2D>::value));

        symbol = get_next_symbol(symbol);
        for (const auto& vector : vectors) {
            int x = int((vector[0] - min) * width / (max - min));
            int y = height - int((vector[1] - min) * height / (max - min));  // Invert height, top row is 0
            if (x < width && x >= 0 && y < height && y >= 0) {
                matrix[y][x] = symbol;  // Todo: visual indicator when symbol was already there
            }
        }
    }

    void clean() {
        matrix = {};
    }

    void draw() {
        int last_row = matrix.size();
        for (int i = 0; i < matrix.size() + 1; ++i) {
            for (int j = 0; j < matrix[0].size() + 1; ++j) {
                if (i == last_row)
                    printf("-");
                else if (j == 0)
                    printf("|");
                else
                    printf("%c", matrix[i][j - 1]);
            }
            printf("\n");
        }
    }

private:
    char plot_symbol = 'a';
    std::array<std::array<char, width>, height> matrix = {};

    char get_next_symbol(char symbol) {
        if (symbol == AUTOMATIC_SYMBOL) {
            symbol = plot_symbol;
            if (++plot_symbol == 'z') {
                plot_symbol = 'a';
            }
        }
        return symbol;
    }
};


#endif //CLUSTERING_PLOTTER_H
