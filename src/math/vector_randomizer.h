//
// Created by jsier on 15/06/2021.
//

#ifndef CLUSTERING_VECTOR_RANDOMIZER_H
#define CLUSTERING_VECTOR_RANDOMIZER_H

#include <random>
#include <vector>
#include "vector.h"

class VectorRandomizer {
public:
    VectorRandomizer() = default;
    ~VectorRandomizer() = default;
    explicit VectorRandomizer(uint64_t seed): random_engine(seed) {}
    template<class VectorType, class Distribution>
    void randomizeVectors(std::vector<VectorType>& vectors, const std::vector<size_t>& coords, Distribution&& dist);
    template<class VectorType, class Distribution>
    void randomizeVectors(std::vector<VectorType>& vectors, const std::vector<size_t>& coords, Distribution& dist);

private:
    std::random_device random_dev{};
    std::default_random_engine random_engine{random_dev()};
};

template<class VectorType, class Distribution>
void VectorRandomizer::randomizeVectors(
        std::vector<VectorType> &vectors,
        const std::vector<size_t> &coords,
        Distribution &&dist)
{
    Distribution static_dist = std::move(dist);
    randomizeVectors(vectors, coords, static_dist);
}

template<class VectorType, class Distribution>
void VectorRandomizer::randomizeVectors(
        std::vector<VectorType> &vectors,
        const std::vector<size_t> &coords,
        Distribution &dist)
{
    for (auto& vector : vectors) {
        for (auto& coord : coords) {
            vector[coord] = dist(random_engine);
        }
    }
}

#endif //CLUSTERING_VECTOR_RANDOMIZER_H
