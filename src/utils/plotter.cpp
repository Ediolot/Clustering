//
// Created by jsier on 15/06/2021.
//

#include "plotter.h"
#include <string>
#include <iostream>

Plotter::Plotter() {
    matrix = std::vector<char>(width * height);  // Initialize after making sure width and height are initialized
}

Plotter::Plotter(uint32_t width, uint32_t height)
    : width(width)
    , height(height)
    , matrix(width * height)
{}

Plotter::Plotter(uint32_t width, uint32_t height, Plotter::Range range)
    : range(range)
    , width(width)
    , height(height)
    , matrix(width * height)
{}

void Plotter::clean() {
    std::fill(matrix.begin(), matrix.end(), 0);
}

void Plotter::draw() {
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (i % width == 0)
            std::cout << "\n|";
        std::cout << matrix[i];
    }
    std::cout << "\n" << std::string(width + 1, '-');
}

char Plotter::get_next_symbol() {
    if (++plot_symbol == 'z') {
        plot_symbol = 'a';
    }
    return plot_symbol - 1;
}
