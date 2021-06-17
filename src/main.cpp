#include <iostream>
#include <random>
#include <format>
#include <vector>
#include "math/vector.h"
#include "math/vector_randomizer.h"
#include "utils/plotter.h"

using normal_dist = std::normal_distribution<double>;
using uniform_dist = std::uniform_real_distribution<double>;

int main() {
    Plotter plotter{};
    VectorRandomizer randomizer{};

    // Generate each cluster
    std::vector<Vector2D> vectors0(100);
    std::vector<Vector2D> vectors1(100);
    std::vector<Vector2D> vectors2(100);

    randomizer.randomizeVectors(vectors0, {0, 1}, normal_dist(0, 0.2));
    randomizer.randomizeVectors(vectors1, {0}, normal_dist(0.6, 0.1));
    randomizer.randomizeVectors(vectors1, {1}, normal_dist(-0.6, 0.1));
    randomizer.randomizeVectors(vectors2, {0}, uniform_dist(0, 1));
    randomizer.randomizeVectors(vectors2, {1}, uniform_dist(0.8, 1.0));

    plotter.plot_vectors(vectors0);
    plotter.plot_vectors(vectors1);
    plotter.plot_vectors(vectors2);
    plotter.draw();

    return 0;
}
