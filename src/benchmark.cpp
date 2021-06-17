#include <iostream>
#include <random>
#include "../3rd_party/benchmark/include/benchmark/benchmark.h"
#include "math/vector.h"
#include "clustering/clustering_kmeans.h"
#include "math/vector_randomizer.h"

static void BM_ClusteringKMeans(benchmark::State& state) {
    using normal_dist = std::normal_distribution<double>;
    using uniform_dist = std::uniform_real_distribution<double>;
    ClusteringKMeans<Vector2D> clustering;
    VectorRandomizer randomizer{};

    for (auto _ : state) {
        state.PauseTiming();
        std::vector<Vector2D> vectors0(state.range(0) / 3);
        std::vector<Vector2D> vectors1(state.range(0) / 3);
        std::vector<Vector2D> vectors2(state.range(0) / 3);
        std::vector<Vector2D> all_vectors;
        randomizer.randomizeVectors(vectors0, {0, 1}, normal_dist(0, 0.2));
        randomizer.randomizeVectors(vectors1, {0}, normal_dist(0.6, 0.1));
        randomizer.randomizeVectors(vectors1, {1}, normal_dist(-0.6, 0.1));
        randomizer.randomizeVectors(vectors2, {0}, uniform_dist(0, 1));
        randomizer.randomizeVectors(vectors2, {1}, uniform_dist(0.8, 1.0));
        all_vectors.reserve(vectors0.size() + vectors1.size() + vectors2.size());
        std::copy(vectors0.begin(), vectors0.end(), std::back_inserter(all_vectors));
        std::copy(vectors1.begin(), vectors1.end(), std::back_inserter(all_vectors));
        std::copy(vectors2.begin(), vectors2.end(), std::back_inserter(all_vectors));
        state.ResumeTiming();
        clustering.cluster(all_vectors, 3);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_ClusteringKMeans)
    ->Arg(10000)
    ->Arg(100000)
    ->Arg(1000000)
    ->Arg(10000000)
    ->Complexity()
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();